#ifndef ALLOC_H
#define ALLOC_H

#include <new>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <climits>
using std::cout;
using std::ends;
using std::endl;
using std::cerr;

/**
 * alloc版本的空间配置器，有第一级空间配置器和第二级空间配置器
 */
namespace mstd{

    /**
     * 第一级的空间配置器，处理分配的内存大于128bytes的情况
     */
    template <int inst>
    class __malloc_alloc_template{
    private:
        static void* oom_malloc(size_t size)
        {
            void (* my_malloc_handler)();
            void * result;

            while(true){
                my_malloc_handler = __malloc_oom_handler;
                if(my_malloc_handler == 0){
                    cerr<<"Out of memory!";
                    exit(1);
                }
                (*my_malloc_handler)();
                result = malloc(size);
                if(result)  return result;
            }
        }
        static void* oom_realloc(void *ptr,size_t size)
        {
            void (*my_malloc_handler)();
            void *result;

            while(true){
                my_malloc_handler = __malloc_oom_handler;
                if(my_malloc_handler == 0){
                    cerr<<"Out of memory";
                    exit(1);
                }
                (*my_malloc_handler)();
                result = realloc(ptr,size);
                if(result)  return result;
            }
        }

        static void (*__malloc_oom_handler)();

    public:
        static void* allocate(size_t size)
        {
            void *result = malloc(size);
            if(result==0)  result = oom_malloc(size);
            return result;
        }
        static void deallocate(void *ptr)
        {
            free(ptr);
        }
        static void* reallocate(void *ptr,size_t new_sz)
        {
            void *result = realloc(ptr,new_sz);
            if(result==0)  result = oom_realloc(ptr,new_sz);
            return result;
        }


        static void (*set_malloc_handler(void(*f)()))()
        {
            void (* old)() = __malloc_oom_handler;
            __malloc_oom_handler = f;
            return old;
        }
    };

    template <int inst>
    void (* __malloc_alloc_template<inst>::__malloc_oom_handler)() = 0;

    typedef __malloc_alloc_template<0>         malloc_alloc;
    typedef malloc_alloc                                 alloc;




    /**
     * 一个简单的空间配置器接口,以供容器使用
     */
    template <class T,class Alloc>
    class simple_alloc{
    public:
        typedef T                       value_type;
        typedef T*                      pointer;
        typedef const T*             const_pointer;
        typedef T&                     reference;
        typedef const T&            const_reference;

    public:
        static T* allocate(size_t n)                     { return static_cast<T*>(Alloc::allocate(n*sizeof(T))); }
        static T* allocate(void)                          { }
        static void deallocate(T *ptr)                 { Alloc::deallocate(ptr); }
        static void deallocate(T *ptr,size_t n)     { while(n--)  Alloc::deallocate(ptr++); }
};

}

#endif // ALLOC_H
