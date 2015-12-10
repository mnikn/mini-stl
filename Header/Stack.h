#ifndef STACK_H
#define STACK_H

#include "Deque.h"
using mstd::deque;

namespace mstd{

    template <class T,class Sequence = deque<T>>
    class stack{
        friend bool operator==(const stack<T,Sequence> &a,const stack<T,Sequence> &b)
        { return a.top()==b.top(); }
        friend bool operator!=(const stack<T,Sequence> &a,const stack<T,Sequence> &b)
        { return !(a==b); }
        friend bool operator>(const stack<T,Sequence> &a,const stack<T,Sequence> &b)
        { return a.top()>b.top(); }
        friend bool operator<(const stack<T,Sequence> &a,const stack<T,Sequence> &b)
        { return !(a>b || a ==b); }

    public:
        typedef typename deque<T>::value_type                  value_type;
        typedef typename deque<T>::pointer                        pointer;
        typedef typename deque<T>::reference                    reference;
        typedef typename deque<T>::const_reference           const_reference;
        typedef typename deque<T>::size_type                     size_type;



    protected:
        Sequence _container;


    //接口的声明
    public:

        //容量相关
        bool empty() const                                                  { return _container.empty(); }
        size_type size() const                                               { return _container.size(); }

        //访问元素相关
        reference top()                                                        { return _container.back(); }
        const_reference top() const                                     { return static_cast<const_reference>(top()); }

        //修改容器相关
        void push(const_reference e)                                   { _container.push_back(e); }
        value_type pop()                                                      { return _container.pop_back(); }
    };

}

#endif // STACK_H
