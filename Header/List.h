#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "Iterator.h"
#include "Alloc.h"
#include "Construct.h"
#include "Uninitialize_funtion.h"
using std::initializer_list;

/**
 * 列表，线性容器，读取和写入数据复杂度为O(n)，插入和删除复杂度为O(1)
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

        __list_iterator(link_type x):node(x){}
        __list_iterator() = default;
        __list_iterator(const iterator &i):node(i.node){}

        bool operator==(const iterator &i)                      { return node == i.node; }
        bool operator!=(const iterator &i)                       { return node != i.node; }
        reference operator*()                                          { return node->data; }
        pointer operator->()                                           { return node;}
        iterator& operator++()                                       { node = node->next; return *this; }
        iterator operator++(int)                                      { iterator tmp = *this; node = node->next; return tmp; }
        iterator& operator--()                                         { node = node->prev; return *this; }
        iterator operator--(int)                                        { iterator tmp = *this; node = node->prev; return tmp; }
        iterator& operator+=(difference_type n)             { while(n--) node = node->next; return *this;}
        iterator& operator-=(difference_type n)              { while(n--) node = node->prev; return *this;}

        friend iterator operator+(iterator &i,difference_type n)
        {
            while(n--)  i.node = i.node->next;
            return i;
        }
        friend iterator operator-(iterator &i,difference_type n)
        {
            while(n--)  i.node = i.node->prev;
            return i;
        }


    };



    template <class T,class Alloc = alloc>
    class list{
    protected:
        typedef __list_node<T>                                          list_node;
        typedef list_node*                                                  link_type;
        typedef simple_alloc<list_node,Alloc>                    allocator_type;
        typedef T                                                               value_type;
        typedef __list_iterator<T>                                       iterator;
        typedef const __list_iterator<T>                              const_iterator;
        typedef T&                                                             reference;
        typedef const T&                                                    const_reference;
        typedef size_t                                                          size_type;
        typedef ptrdiff_t                                                      difference_type;


    //成员变量
    protected:
        link_type header; //首哨兵
        link_type trailer;   //尾哨兵
        size_type _size;


    //辅助函数
    protected:
        link_type allocate_node();
        link_type allocate_some_node(size_type n);
        void deallocate_node(link_type p);
        link_type create_node(const_reference e);
        void destory_node(link_type p);
        void destory_all_node();
        void empty_initialize();


    //构造函数和析构函数
    public:
        list()                                                  { empty_initialize(); }
        list(const initializer_list<T> &i)
        {
            empty_initialize();
            allocate_some_node(i.size());
            //uninitialize_copy(i.begin(),i.end(),begin());
            //_size = i.size();
        }
        ~list() { }


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
        iterator insert(iterator pos,const_reference e);
        iterator erase(iterator pos,const_reference e);


    //运算符的重载
    public:
        reference operator[](size_type i)
        { iterator tmp = begin(); while(i--) ++tmp; return *tmp; }
        const_reference operator[](size_type i) const
        { return static_cast<const_reference>(*this[i]); }

    };


}

#include "Detail/List.impl.h"
#endif // LIST_H
