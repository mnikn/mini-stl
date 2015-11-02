#ifndef UNINITIALIZED_COPY_H
#define UNINITIALIZED_COPY_H

#include <algorithm>
#include "Header/type_traits.h"
#include "Header/construct.h"
using std::copy;
using std::fill;
using std::fill_n;
using mstd::__construct;
using mstd::__false_type;
using mstd::__type_traits;

namespace mstd {

    template <class InputIterator,class ForwardIterator>
    ForwardIterator __uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result)
    {
        typedef typename __type_traits<ForwardIterator>::is_POD_type              is_POD_type;
        return __uninitialized_copy_aux(first,last,result,is_POD_type());
    }

    template <class ForwardIterator,class T>
    ForwardIterator __uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& e)
    {
        typedef typename __type_traits<T>::is_POD_type               is_POD_type;
        return __uninitialized_fill_aux(first,last,e,is_POD_type());
    }

    template <class ForwardIterator,class Size,class T>
    ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T& e)
    {
        typedef typename __type_traits<T>::is_POD_type             is_POD_type;
        return __uninitialized_fill_n_aux(first,n,e,is_POD_type());
    }

    template <class InputIterator,class ForwardIterator>
    ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__false_type)
    {
        ForwardIterator cur = result;
        while(first!=last){
            __construct(cur,*first);
            ++first;
            ++cur;
        }
        return cur;
    }

    template <class InputIterator,class ForwardIterator>
    ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__true_type)
    {
        return copy(first,last,result);
    }

    template <class ForwardIterator,class T>
    void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& e,__false_type)
    {
        ForwardIterator cur = first;
        while(cur!=last){
            __construct(cur,e);
            ++cur;
        }
    }

    template <class ForwardIterator,class T>
    void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& e,__true_type)
    {
        fill(first,last,e);
    }

    template <class ForwardIterator,class Size,class T>
    ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& e,__false_type)
    {
        ForwardIterator cur = first;
        while(n>0){
            __construct(cur,e);
            --n;
            ++cur;
        }
        return cur;
    }

    template <class ForwardIterator,class Size,class T>
    ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& e,__true_type)
    {
        return fill_n(first,n,e);
    }

}


#endif // UNINITIALIZED_COPY_H
