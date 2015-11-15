#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <new>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <climits>
using std::set_new_handler;
using std::cerr;

/**
 * 一个简单的空间配置器，功能不完善，建议使用alloc版本
 */
namespace mstd{

template <class T>
class allocator{
public:
    typedef T                       value_type;
    typedef T*                      pointer;
    typedef const T*             const_pointer;
    typedef T&                     reference;
    typedef const T&            const_reference;

public:
    template <class U>
    struct rebind{
        typedef allocator<U> other;
    };

    static T* allocate(ptrdiff_t size)
    {
        set_new_handler(0);
        T *result = (T*)(::operator new((size_t)(size*sizeof(T))));
        if(result ==0){
            cerr<<"Out of memory!";
            exit(1);
        }
        return result;
    }
    static void deallocate(T* ptr,size_t)
    {
        ::operator delete(ptr);
    }
    static void construct(T *ptr,const T &value)
    {
        new(ptr) T(value);
    }
    static void destory(T *ptr)
    {
        ptr->~T();
    }
    T* address(T &ptr) const
    {
        return (T*)(&ptr);
    }
    const T* const_address(const T &ptr) const
    {
        return (const T*)(&ptr);
    }
    size_t max_size() const
    {
        return UINT_MAX/sizeof(T);
    }
};

}

#endif // ALLOCATOR_H
