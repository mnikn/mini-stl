#ifndef UNINITIALIZE_FUNTION_H
#define UNINITIALIZE_FUNTION_H

#include "Header/Construct.h"
#include "Header/Algorithm.h"
#include "Header/Type_traits.h"

namespace mstd{

    /********************************************************************/
    /****uninitialize_fill算法，函数名前有双下划线的均为辅助函数*****/
    /*******************************************************************/

    template <class ForwardIterator,class T>
    inline void __uninitialize_fill_aux(ForwardIterator first,ForwardIterator last,const T &value,__false_type)
    {
        while(first!=last){
            construct(first++,value);
        }
    }

    template <class ForwardIterator,class T>
    inline void __uninitialize_fill_aux(ForwardIterator first,ForwardIterator last,const T &value,__true_type)
    {
        mstd::fill(first,last,value);
    }

    template <class ForwardIterator,class T,class T2>
    inline void __uninitialize_fill(ForwardIterator first,ForwardIterator last,const T &value,T2*)
    {
        typedef typename __type_traits<T2>::is_POD_type is_POD_type;
        __uninitialize_fill_aux(first,last,value,is_POD_type());
    }

    //实际调用的uninitialize_fill
    template <class ForwardIterator,class T>
    inline void uninitialize_fill(ForwardIterator first,ForwardIterator last,const T &value)
    {
        __uninitialize_fill(first,last,value,value_type(first));
    }






    /********************************************************************/
    /***uninitialize_fill_n算法，函数名前有双下划线的均为辅助函数***/
    /*******************************************************************/

    template <class ForwardIterator,class T>
    inline ForwardIterator __uninitialize_fill_n_aux(ForwardIterator first,size_t n,const T &value,__false_type)
    {
        while(n--){
            construct(first++,value);
        }
        return first;
    }

    template <class ForwardIterator,class T>
    inline ForwardIterator __uninitialize_fill_n_aux(ForwardIterator first,size_t n,const T &value,__true_type)
    {
        return fill_n(first,n,value);
    }

    template <class ForwardIterator,class T,class T2>
    inline ForwardIterator __uninitialize_fill_n(ForwardIterator first,size_t n,const T &value,T2*)
    {
        typedef typename __type_traits<T2>::is_POD_type is_POD_type;
        return __uninitialize_fill_n_aux(first,n,value,is_POD_type());
    }

    //实际调用的uninitialize_fill_n
    template <class ForwardIterator,class T>
    inline ForwardIterator uninitialize_fill_n(ForwardIterator first,size_t n,const T &value)
    {
        return __uninitialize_fill_n(first,n,value,value_type(first));
    }








    /********************************************************************/
    /***uninitialize_copy算法，函数名前有双下划线的均为辅助函数***/
    /*******************************************************************/

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator __uninitialize_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__false_type)
    {
        while(first!=last){
            construct(result++,*first++);
        }
        return result;
    }

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator __uninitialize_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__true_type)
    {
        return copy(first,last,result);
    }

    template <class InputIterator,class ForwardIterator,class T>
    inline ForwardIterator __uninitialize_copy(InputIterator first,InputIterator last,ForwardIterator result,T*)
    {
        typedef typename __type_traits<T>::is_POD_type is_POD_type;
        return __uninitialize_copy_aux(first,last,result,is_POD_type());
    }

    //实际调用的uninitialize_copy
    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator uninitialize_copy(InputIterator first,InputIterator last,ForwardIterator result)
    {
        return __uninitialize_copy(first,last,result,value_type(first));
    }







    /********************************************************************/
    /***uninitialize_copy_n算法，函数名前有双下划线的均为辅助函数***/
    /*******************************************************************/

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator __uninitialize_copy_n_aux(InputIterator first,size_t n,ForwardIterator result,__false_type)
    {
        while(n--){
            construct(result++,*first++);
        }
        return result;
    }

    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator __uninitialize_copy_n_aux(InputIterator first,size_t n,ForwardIterator result,__true_type)
    {
        return copy_n(first,n,result);
    }

    template <class InputIterator,class ForwardIterator,class T>
    inline ForwardIterator __uninitialize_copy_n(InputIterator first,size_t n,ForwardIterator result,T)
    {
        typedef typename __type_traits<T>::is_POD_type is_POD_type;
        return __uninitialize_copy_n_aux(first,n,result,is_POD_type());
    }

    //实际调用的uninitialize_copy
    template <class InputIterator,class ForwardIterator>
    inline ForwardIterator uninitialize_copy_n(InputIterator first,size_t n,ForwardIterator result)
    {
        return __uninitialize_copy_n(first,n,result,value_type(first));
    }



}

#endif // UNINITIALIZE_FUNTION_H
