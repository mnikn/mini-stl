#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "Iterator.h"
#include "Alloc.h"
#include "Construct.h"
#include "Uninitialize_funtion.h"
using std::initializer_list;
using std::ostream;

/**
 * 列表，线性容器，元素分配位置零散，
 * 读取和写入数据复杂度为O(n)，插入和删除复杂度为O(1)
 */

namespace mstd{

    /**
     * 列表的节点
     */
    template <class T>
    struct __list_node{
        T data;
        __list_node<T> *prev;
        __list_node<T> *next;
        __list_node(const T &e,__list_node<T> *_prev =nullptr,__list_node<T> *_next = nullptr):
            data(e),
            prev(_prev),
            next(_next){}
    };


    /**
     * 列表的迭代器
     */
    template <class T>
    struct __list_iterator{


        typedef __list_iterator<T>                                       iterator;
        typedef __list_node<T>*                                         link_type;
        typedef bidirectional_iterator_tag                           iterator_category;
        typedef T                                                               value_type;
        typedef link_type                                                    pointer;
        typedef T&                                                             reference;
        typedef ptrdiff_t                                                     difference_type;


        link_type node;

        __list_iterator(link_type x):node(x)                         { }
        __list_iterator() = default;
        __list_iterator(const iterator &i):node(i.node)        { }


        bool operator==(const iterator &i)                      { return node == i.node; }
        bool operator!=(const iterator &i)                       { return node != i.node; }
        reference operator*()                                          { return node->data; }
        pointer operator->()                                           { return node; }
        iterator& operator++()                                       { node = node->next; return *this; }
        iterator operator++(int)                                      { iterator tmp = *this; ++*this; return tmp; }
        iterator& operator--()                                         { node = node->prev; return *this; }
        iterator operator--(int)                                        { iterator tmp = *this; --*this; return tmp; }
        iterator& operator+=(difference_type n)             { while(n--) { node = node->next; } return *this; }
        iterator& operator-=(difference_type n)              { while(n--) { node = node->prev; } return *this; }
        iterator operator+(difference_type n)                  { iterator tmp = *this; return tmp += n; }
        iterator operator-(difference_type n)                   { iterator tmp = *this; return tmp -= n; }
        friend ostream& operator<<(ostream &os,iterator i)
        { os<<i.node; return os; }

    };



    template <class T,class Alloc = alloc>
    class list{
    public:
        typedef T                                                               value_type;
        typedef __list_iterator<T>                                       iterator;
        typedef const __list_iterator<T>                              const_iterator;
        typedef T&                                                             reference;
        typedef const T&                                                    const_reference;
        typedef size_t                                                          size_type;
        typedef ptrdiff_t                                                      difference_type;


    protected:
        typedef __list_node<T>                                           list_node;
        typedef list_node*                                                   link_type;
        typedef simple_alloc<list_node,Alloc>                     allocator_type;



    //成员变量
    protected:
        link_type header; //首哨兵
        link_type trailer;   //尾哨兵
        size_type _size;


    //辅助函数
    protected:
        link_type allocate_node();
        void allocate_some_node(size_type n);
        void deallocate_node(link_type p);
        link_type create_node(const_reference e);
        void destory_node(link_type p);
        void empty_initialize();
        void transfer(iterator pos,iterator first,iterator last);

    //构造函数和析构函数
    public:
        list()
        { empty_initialize(); }
        list(size_type n)
        { allocate_some_node(n); }
        list(iterator first,iterator last)
        { allocate_some_node(static_cast<size_type>(last-first)); copy(first,last,begin()); }
        list(const initializer_list<T> &i)
        { allocate_some_node(i.size()); copy( i.begin() , i.end() , begin() ); }
        list(list<T,Alloc> &l)
        { allocate_some_node(l.size()); copy( l.begin() , l.end() , begin() ); }
        ~list()
        { clear(); destory_node(header); destory_node(trailer); }


    //接口的声明
    public:

        //迭代器相关
        iterator begin()                                { return iterator(header->next); }
        const_iterator cbegin() const           { return const_iterator(header->next); }
        iterator end()                                  { return iterator(trailer); }
        const_iterator cend() const              { return const_iterator(trailer); }

        //访问元素相关
        reference front()                             { return *begin(); }
        reference back()                             { return *(end()-1); }

        //容量相关
        size_type size() const                      { return _size; }
        bool empty() const                         { return size()==0;}

        //修改容器相关
        void clear();
        void push_front(const_reference  e);
        void push_back(const_reference e);
        value_type pop_front();
        value_type pop_back();
        iterator insert(iterator pos,const_reference e);
        value_type erase(iterator pos);


    //运算符的重载
    public:
        reference operator[](size_type i)
        { iterator tmp = begin(); while(i--) ++tmp; return *tmp; }
        const_reference operator[](size_type i) const
        { return static_cast<const_reference>(*this[i]); }
        list<T,Alloc>& operator=(initializer_list<T> &i)
        { allocate_some_node(i.size()); copy( i.begin() , i.end() , begin() ); return *this; }
        list<T,Alloc>& operator=(list<T,Alloc> &l)
        { allocate_some_node(l.size()); copy( l.begin() , l.end() , begin() ); return *this; }
        bool operator==(list<T,Alloc> &l);
        bool operator!=(list<T,Alloc> &l);

    };


}

#include "Detail/List.impl.h"
#endif // LIST_H
