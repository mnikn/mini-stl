#ifndef ALLOC_H
#define ALLOC_H

#include <new>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <climits>
using std::set_new_handler;
using std::cerr;

/**
 * alloc版本的空间配置器，有第一级空间配置器和第二级空间配置器
 */
namespace mstd{

/**
 * 第一级的空间配置器，处理分配的内存大于128bytes的情况
 */
template <int inst>
class __new_alloc_template{
public:
    static void* allocate(ptrdiff_t size)
    {
        set_new_handler(0);
        void *result = (void*)(size_t(::operator new(size)));
        if(result==0){
            cerr<<"Out of memory!";
            exit(1);
        }
        return result;
    }
    static void deallocate(void *ptr)
    {
        ::operator delete(ptr);
    }
    static void* reallocate(void *ptr,size_t new_sz)
    {
        void *result = realloc(ptr,new_sz);
        if(result==0){
            cerr<<"Out of memory";
            exit(1);
        }
        return result;
    }
};

typedef __new_alloc_template<0>         new_alloc;
typedef new_alloc                                 alloc;

template <class T,class Alloc>
class simple_alloc{
public:
    static T* allocate(size_t);
    static T* allocate(void);
    static void deallocate(T*);
    static void deallocate(T*,size_t);
};

}

#endif // ALLOC_H
