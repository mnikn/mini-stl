#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <new>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cstddef>
#include "Cpp/alloc.cpp"
#include "Header/construct.h"
using std::cerr;
using std::endl;

/**
 * 这是一个空间配置器,使用alloc版本的内存配置器
 */

namespace mstd{

    template <class T>
    class allocator{
    public:
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef const T*         const_pointer;
        typedef T&                 reference;
        typedef const T&        const_reference;
        typedef size_t              size_type;
        typedef ptrdiff_t          differenc_type;

    public:
        template <class U>
        struct rebind{
            typedef allocator<U> other;
        };

    public:
        static pointer allocate(size_type n,const void* hint = 0)
        {
            return (pointer)alloc::allocate(n);
        }
        static void deallocate(pointer p,size_type n)
        {
            alloc::deallocate(p,n);
        }
        static void construct(pointer p,const_reference value)
        {
            __construct(p,value);
        }
        static void destory(pointer p)
        {
            __destory(p);
        }
        template <class ForwardIterator>
        static void destory(ForwardIterator first,ForwardIterator last)
        {
            __destory(first,last);
        }

        static pointer address(reference x)
        {
            return (pointer)&x;
        }
        const_pointer const_address(const_reference x) const
        {
            return (const_pointer)&x;
        }

        size_type max_size() const
        {
            return size_type(UINT_MAX/sizeof(T));
        }
    };
}

#endif // ALLOCATOR_H
