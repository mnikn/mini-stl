#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "Alloc.h"
#include "Construct.h"
#include "Uninitialize_funtion.h"
#include "Type_traits.h"


/**
 * shared_ptr，可以记录同一地址的指针个数，并回收空间
 */
namespace mstd{

    template <class T,class Alloc = alloc>
    class shared_ptr{
    public:
        typedef T                                                     element_type;
        typedef T*                                                   pointer;
        typedef const T*                                          const_pointer;
        typedef T&                                                  reference;
        typedef const T&                                         const_reference;
        typedef size_t                                               size_type;
        typedef ptrdiff_t                                           difference_type;




    protected:
        pointer ptr;
        static size_type count;




    public:
        shared_ptr(pointer _ptr = nullptr): ptr(_ptr)                                                    { count = 1; }
        shared_ptr(const shared_ptr &s)                                                                    { ptr = s.ptr; ++count; }
        ~shared_ptr()                                                                                                { delete ptr; }



    //接口
    public:
        bool unique() const                                                                             { return count==0; }
        static size_type user_count()                                                                { return count; }
        pointer release() const                                                                        { return ptr; }
        pointer get() const                                                                             { return ptr; }




    //运算符的重载
    public:
        element_type& operator*() const                                                        { return *ptr; }
        pointer operator->() const                                                                  { return ptr; }
        pointer operator++()                                                                          { return ++ptr; }
        pointer operator++(int)                                                                      { return ptr++; }
        pointer operator--()                                                                            { return --ptr; }
        pointer operator--(int)                                                                        { return ptr--; }
    };

    template<class T,class Alloc>
    size_t shared_ptr<T,Alloc>::count = 0;

    template <class T,class Alloc = alloc>
    inline shared_ptr<T,Alloc> make_shared()
    {
        T* tmp;
        tmp = new T();
        return shared_ptr<T,Alloc>(tmp);
    }

}

#endif // SHARED_PTR_H
