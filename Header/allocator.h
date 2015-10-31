#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <new>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cstddef>
using std::cerr;
using std::endl;

/**
 * 这是一个内存配置器，功能并不完善，建议使用alloc版本的内存配置器
 */

namespace mstd{

    template <class T>
    inline T* _allocate(ptrdiff_t size,T*)
    {
        T *p = (T*)(::operator new((size_t)(size*sizeof(T))));
        if(p==0){
            cerr<<"Out of memory!"<<endl;
            exit(1);
        }
        return p;
    }

    template <class T>
    inline void _deallocate(T *p)
    {
        ::operator delete(p);
    }

    template <class T1,class T2>
    inline void _construct(T1 *p,const T2 &value)
    {
        new(p) T1(value);
    }

    template <class T>
    inline void _destory(T *p)
    {
        p->~T();
    }

    template <class T>
    class Allocator{
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
            typedef Allocator<U> other;
        };

    public:
        pointer allocate(size_type n,const void* hint = 0)
        {
            return _allocate( (differenc_type)n,(pointer)hint);
        }
        void deallocate(pointer p,size_type n)
        {
            _deallocate(p);
        }
        void construct(pointer p,const_reference value)
        {
            _construct(p,value);
        }
        void destory(pointer p)
        {
            _destory(p);
        }

        pointer address(reference x)
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
