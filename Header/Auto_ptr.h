#ifndef AUTO_PTR_H
#define AUTO_PTR_H

#include "Alloc.h"
#include "Construct.h"
#include "Type_traits.h"

/**
 * 智能指针，可自动回收空间
 */
namespace mstd{

    template <class T,class Alloc = alloc>
    class auto_ptr{
    public:
        typedef T                                                     element_type;
        typedef T*                                                   pointer;
        typedef const T*                                          const_pointer;
        typedef T&                                                  reference;
        typedef const T&                                         const_reference;
        typedef size_t                                               size_type;
        typedef ptrdiff_t                                           difference_type;





    //成员变量
    protected:
        pointer ptr;





    //构造函数和析构函数
    public:
        auto_ptr(pointer _ptr = nullptr):ptr( _ptr )                                            { }
        auto_ptr(const auto_ptr &p)                                                               { ptr = p.ptr; }
        ~auto_ptr()                                                                                        { delete ptr; }




    //接口
    public:
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

}

#endif // AUTO_PTR_H
