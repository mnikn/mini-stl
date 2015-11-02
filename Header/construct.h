#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>
#include "Header/iterator.h"
#include "Header/type_traits.h"
using mstd::value_type;
using mstd::__false_type;
using mstd::__true_type;
using mstd::__type_traits;

/**
 * 定义了构造函数和析构函数以供其他文件使用
 */
namespace mstd {

    template <class T1,class T2>
    inline void __construct(T1 *p,const T2 &value)
    {
        new(p) T1(value);
    }

    template <class T>
    inline void __destory(T *p)
    {
        p->~T();
    }

    template <class ForwardIterator,class T>
    inline void ___destory(ForwardIterator first,ForwardIterator last,T*)
    {
        typedef typename __type_traits<T>::has_trivial_destructor             trivial_destructor;
        __destory_aux(first,last,trivial_destructor());
    }

    template <class ForwardIterator>
    inline void __destory(ForwardIterator first,ForwardIterator last)
    {
        ___destory(first,last,value_type(first));
    }



    template <class ForwardIterator>
    inline void __destory_aux(ForwardIterator first,ForwardIterator last,__false_type)
    {
        while(first!=last){
            __destory(&*first);
            ++first;
        }
    }

    template <class ForwardIterator>
    inline void __destory_aux(ForwardIterator first,ForwardIterator last,__true_type)
    {
        if(first&&last) return;
    }


}

#endif // CONSTRUCT_H
