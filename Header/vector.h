#ifndef VECTOR_H
#define VECTOR_H

#include "Header/uninitializedFunction.h"
#include "Header/allocator.h"
using mstd::allocator;

namespace mstd{

    template <class T,class Alloc = allocator<T> >
    class vector{
    public:
        typedef T                        value_type;
        typedef T*                       iterator;
        typedef const T*             const_iterator;
        typedef T&                     reference;
        typedef const T&            const_reference;
        typedef size_t                  size_type;
        typedef ptrdiff_t              difference_type;

    protected:
        iterator start;
        iterator finish;
        iterator end_of_storage;

    public:
        vector():start(0),finish(0),end_of_storage(0){}
        explicit vector(size_type n)
        {
            fill_initialize(n,T());
        }
        vector(size_type n,const_reference e)
        {
            fill_initialize(n,e);
        }
        ~vector()
        {
            Alloc::destory(start,finish);
            deallocate();
        }

    protected:
        iterator allocate_and_fill(size_type n,const_reference e)
        {
            iterator result = Alloc::allocate(n);
            return __uninitialized_fill_n(result,n,e);
        }
        void fill_initialize(size_type n,const_reference e)
        {
            start = allocate_and_fill(n,e);
            finish = start+n;
            end_of_storage += n;
        }
        void deallocate()
        {
            Alloc::deallocate(start,capacity());
        }

    public:
        iterator begin() const;
        const_iterator cbegin() const;
        iterator end() const;
        const_iterator cend() const;
        bool empty() const;
        size_type size() const;
        size_type capacity() const;
        void push_back(const_reference x);
        value_type pop_back();

    public:
        reference operator[](size_type i)
        {
            return *(start+i);
        }
    };
}


#endif // VECTOR_H
