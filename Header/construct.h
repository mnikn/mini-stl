#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>
#include "Header/Iterator.h"
#include "Header/Type_traits.h"

/**
 * 各容器构造函数和析构函数的原型
 */
namespace mstd{

    template<class T1,class T2>
    inline void construct(T1 *ptr,const T2 &value)
    {
        new(ptr) T1(value);
    }

    template <class ForwardIterator>
    inline void __destory_aux(ForwardIterator first,ForwardIterator last,__false_type)
    {
        while(first!=last){
            destory(first++);
        }
    }

    template <class ForwardIterator>
    inline void __destory_aux(ForwardIterator first,ForwardIterator last,__true_type)
    {
        /*什么都不做，因为其迭代器的析构函数作用不大，
         * 因此不调用析构函数，减少性能的损耗。
         */
        first = first;
        last = last;
    }

    template <class ForwardIterator,class T>
    inline void __destory(ForwardIterator first,ForwardIterator last,T*)
    {
        typedef typename __type_traits<ForwardIterator>::has_trivial_destructor has_trivial_destructor;
        __destory_aux(first,last,has_trivial_destructor());
    }


    template<class T>
    inline void destory(T *ptr)
    {
        ptr->~T();
    }

    template <class ForwardIterator>
    inline void destory(ForwardIterator first,ForwardIterator last)
    {
        __destory(first,last,value_type(first));
    }



}

#endif // CONSTRUCT_H
