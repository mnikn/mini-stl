#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>

/**
 * 算法库，提供各种算法给容器
 */
namespace mstd{


    /**
     * @brief max               返回a和b的最大值
     * @param a                 元素a
     * @param b                 元素b
     * @return                    a和b之间的最大值
     */
    template <class T>
    inline T max(const T &a,const T &b)
    {
        return (a > b? a : b);
    }



    /**
     * @brief swap                  交换a和b的值
     * @param a                     元素a
     * @param b                     元素b
     */
    template <class T>
    inline void swap(T &a,T &b)
    {
        T tmp = a;
        a  = b;
        b = tmp;
    }



    /**
     * @brief fill                          在[first,last)区间填满值value
     * @param first                     起始位置
     * @param last                      终止位置
     * @param value                   要填充的值
     */
    template <class ForwardIterator,class T>
    inline void fill(ForwardIterator first,ForwardIterator last,const T &value)
    {
        while(first!=last){
            *first++ = value;
        }
    }




    /**
     * @brief fill_n                                在[first,first+n)区间填满值value
     * @param first                               起始位置
     * @param n                                   数目
     * @param value                             要填充的值
     * @return                                      结束位置
     */
    template <class ForwardIterator,class T>
    inline ForwardIterator fill_n(ForwardIterator first,size_t n,const T &value)
    {
        while(n--){
            *first++ = value;
        }
        return first;
    }




    /**
     * @brief copy                              复制区间[first,last)的值到result及以后的位置
     * @param first                             起始位置
     * @param last                              结束位置
     * @param result                           赋值的起始位置
     * @return                                     赋值的结束位置
     */
    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator copy(InputIterator first,InputIterator last,ForwardIterator result)
    {
        while(first!=last){
            *result++ = *first++;
        }
        return result;
    }




    /**
     * @brief copy_n                                复制区间[first,first+n)的值到result及以后的位置
     * @param first                                  起始位置
     * @param n                                      数目
     * @param result                                赋值的起始位置
     * @return                                          赋值的结束位置
     */
    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator copy_n(InputIterator first,size_t n,ForwardIterator result)
    {
        while(n--){
            *result++ = *first++;
        }
        return result;
    }




    /**
     * @brief copy_backward                                  复制区间[first,last)的值到result及以前的位置
     * @param first                                                 起始位置
     * @param last                                                  结束位置
     * @param result                                               赋值的起始位置
     * @return                                                         赋值的结束位置
     */
    template <class BidDirectionIterator1,class BidDirectionIterator2>
    inline BidDirectionIterator2 copy_backward(BidDirectionIterator1 first,BidDirectionIterator1 last,BidDirectionIterator2 result)
    {
        while(first!=last){
            *result-- = *first++;
        }
        return result;
    }




    /**
     * @brief reverse                           让里面的元素逆序
     * @param first                             起始位置
     * @param last                              结束位置
     */
    template <class InputIterator>
    inline void reverse(InputIterator first,InputIterator last)
    {
        while(first != --last)  swap(*first++,*last);
    }



}

#endif // ALGORITHM_H
