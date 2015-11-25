#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>

/**
 * 算法库，提供各种算法给容器
 */
namespace mstd{

    template <class T>
    inline void swap(T &a,T &b)
    {
        T tmp = a;
        a  = b;
        b = tmp;
    }

    template <class ForwardIterator,class T>
    inline void fill(ForwardIterator first,ForwardIterator last,const T &value)
    {
        while(first!=last){
            *first++ = value;
        }
    }

    template <class ForwardIterator,class T>
    inline ForwardIterator fill_n(ForwardIterator first,size_t n,const T &value)
    {
        while(n--){
            *first++ = value;
        }
        return first;
    }

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator copy(InputIterator first,InputIterator last,ForwardIterator result)
    {
        while(first!=last){
            *result++ = *first++;
        }
        return result;
    }

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator copy_n(InputIterator first,size_t n,ForwardIterator result)
    {
        while(n--){
            *result++ = *first++;
        }
        return result;
    }

    template <class BidDirectionIterator1,class BidDirectionIterator2>
    inline BidDirectionIterator2 copy_backward(BidDirectionIterator1 first,BidDirectionIterator1 last,BidDirectionIterator2 result)
    {
        while(first!=last){
            *result-- = *first++;
        }
        return result;
    }

    template <class InputIterator>
    inline void reverse(InputIterator first,InputIterator last)
    {
        while(first != --last)  swap(*first++,*last);
    }

}

#endif // ALGORITHM_H
