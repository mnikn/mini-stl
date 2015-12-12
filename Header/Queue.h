#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"
using mstd::deque;


/**
 * 队列，元素的空间位置连续，由双头队列配接而成
 */
namespace mstd{

    template <class T,class Sequence = deque<T>>
    class queue{
        friend bool operator==(const queue<T,Sequence> &a,const queue<T,Sequence> &b)
        { return (a.front==b.front() && a.back() == b.back()); }
        friend bool operator!=(const queue<T,Sequence> &a,const queue<T,Sequence> &b)
        { return !(a==b); }
        friend bool operator>(const queue<T,Sequence> &a,const queue<T,Sequence> &b)
        { return (a.front > b.front() && a.back() > b.back()); }
        friend bool operator<(const queue<T,Sequence> &a,const queue<T,Sequence> &b)
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
        bool empty() const                                                     { return _container.empty(); }
        size_type size() const                                                  { return _container.size(); }

        //访问元素相关
        reference back()                                                        { return _container.back(); }
        const_reference back() const                                     { return static_cast<const_reference>(back()); }
        reference front()                                                        { return _container.front(); }
        const_reference front() const                                     { return static_cast<const_reference>(front()); }

        //修改容器相关
        void clear()                                                                { _container.clear(); }
        void push(const_reference e)                                     { _container.push_back(e); }
        value_type pop()                                                        { return _container.pop_back(); }
    };
}

#endif // QUEUE_H
