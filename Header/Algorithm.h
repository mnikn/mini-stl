#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstddef>
#include "Iterator.h"

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
     * @brief min               返回a和b的最小值
     * @param a                 元素a
     * @param b                 元素b
     * @return                    a和b之间的最小值
     */
    template <class T>
    inline T min(const T &a,const T &b)
    {
        return (a < b? a : b);
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
     * @brief for_each                                                  访问区间中的元素
     * @param first                                                       开始位置
     * @param last                                                        结束位置
     * @param visit                                                       访问函数
     */
    template <class InputIterator,class FunctionType>
    inline void for_each(InputIterator first,InputIterator last,FunctionType &visit)
    {
        while(first != last)  visit(*first++);
    }




    /**
     * @brief for_each                                                  访问容器中的每个元素
     * @param container                                              容器
     * @param visit                                                       访问函数
     */
    template <class ContainerType,class FunctionType>
    inline void for_each(ContainerType &container,FunctionType &visit)
    {
        for_each(container.begin(),container.end(),visit);
    }


    /**
     * @brief reverse                           让里面的元素逆序
     * @param first                             起始位置
     * @param last                              结束位置
     */
    template <class ForwardIterator>
    inline void reverse(ForwardIterator first,ForwardIterator last)
    {
        if(first == last) return;
        --last;
        while(first < last)  swap(*(first++),*(last--));
    }



    /**
     * @brief find                          查找值为e的迭代器
     * @param first                        开始位置
     * @param last                         结束位置
     * @param e                            查找的值
     * @return                               值为e的迭代器，若找不到，则返回last
     */
    template <class InputIterator,class T>
    inline InputIterator find(InputIterator first,InputIterator last,const T &e)
    {
        while(first != last){
            if(*first == e) return first;
            ++first;
        }
        return last;
    }


    /**
     * @brief find                                      查找值为e的迭代器
     * @param container                           容器
     * @param e                                       查找的值
     * @return                                           值为e的迭代器，若找不到，则返回end
     */
    template <class ContainerType,class InputIterator,class T>
    inline InputIterator find(ContainerType &container,const T &e)
    {
        return find(container.begin(),container.end(),e);
    }

    /**
     * @brief find_if                       查找值为e的迭代器，仅当条件为visit(*iterator)时
     * @param first                        开始位置
     * @param last                         结束位置
     * @param e                            查找的值
     * @return                               值为e的迭代器，若找不到，则返回last
     */
    template <class InputIterator,class FunctionType>
    inline InputIterator find_if(InputIterator first,InputIterator last,FunctionType &visit)
    {
        while(first != last){
            if(visit(*first)) return first;
            ++first;
        }
        return last;
    }



    /**
     * @brief find_if                                   查找值为e的迭代器，仅当条件为visit(*iterator)时
     * @param container                           容器
     * @param e                                       查找的值
     * @return                                           值为e的迭代器，若找不到，则返回end
     */
    template <class ContainerType,class InputIterator,class FunctionType>
    inline InputIterator find_if(ContainerType &container,FunctionType &visit)
    {
        return find(container.begin(),container.end(),visit);
    }






    /**
     * @brief find                          查找值为e的迭代器
     * @param first                        开始位置
     * @param last                         结束位置
     * @param e                            查找的值
     * @return                               值为e的迭代器是否在此区间
     */
    template <class InputIterator,class T>
    inline bool is_in(InputIterator first,InputIterator last,const T &e)
    {
        while(first != last){
            if(*first == e) return true;
            ++first;
        }
        return false;
    }



    /**
     * @brief is_in                                       查找值为e的迭代器
     * @param container                            容器
     * @param e                                        查找的值
     * @return                                           值为e的迭代器是否在此区间
     */
    template <class ContainerType,class InputIterator,class T>
    inline InputIterator is_in(ContainerType &container,const T &e)
    {
        return is_in(container.begin(),container.end(),e);
    }

    /******************************************************************************
    ********************************Heap算法************************************
    ******************************************************************************/

    template <class RandomAccessIterator>
    inline void push_heap(RandomAccessIterator first,RandomAccessIterator last)
    {
        __push_heap_aux(first,last,difference_type(first),value_type(first));
    }

    template <class RandomAccessIterator,class Distance,class T>
    inline void __push_heap_aux(RandomAccessIterator first,RandomAccessIterator last,Distance*,T*)
    {
        __push_heap(first,Distance( (last - first) - 1) , Distance(0) , T(*(last - 1)));
    }

    template <class RandomAccessIterator,class Distance,class T>
    inline void __push_heap(RandomAccessIterator first,RandomAccessIterator last,
                            Distance holeIndex,Distance topIndex,T value)
    {
        Distance parent = (holeIndex - 1)/2;
        while(holeIndex > topIndex && *(first + parent) < value){
            *(first + holeIndex) = *(first + topIndex);
            holeIndex = parent;
            parent = (holeIndex - 1)/2;
        }
        *(first + holeIndex) = value;
    }

}

#endif // ALGORITHM_H
