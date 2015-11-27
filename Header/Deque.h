#ifndef DEQUE_H
#define DEQUE_H

#include "Alloc.h"
#include "Iterator.h"

namespace mstd{

    inline size_t __deque_buf_size(size_t n,size_t size)
    {
        return n!=0?n:(size<512?static_cast<size_t>(512/size):static_cast<size_t>(1));
    }

    template <class T,class Ref,class Ptr,size_t BufSize>
    struct __deque_iterator{
        typedef __deque_iterator                                                          self;
        typedef __deque_iterator<T,T&,T*,BufSize>                              iterator;
        typedef __deque_iterator<T,const T&,const T*,BufSize>            const_iterator;
        typedef random_access_iterator_tag                                          iterator_category;
        typedef T                                                                                  value_type;
        typedef Ptr                                                                               pointer;
        typedef Ref                                                                               reference;
        typedef T**                                                                               map_pointer;
        typedef size_t                                                                           size_type;
        typedef ptrdiff_t                                                                       difference_type;


        pointer cur;
        pointer first;
        pointer last;
        map_pointer node;


        static size_type buffer_size() { return __deque_buf_size(BufSize,sizeof(T)); }
        void set_node(map_pointer new_node)
        {
            node = new_node;
            first = *new_node;
            last = first + static_cast<difference_type>(buffer_size());
        }

        reference operator*() const                                             { return *cur; }
        pointer operator->() const                                              { return cur; }
        reference operator[](difference_type n) const                  { return *(*this+n); }
        bool operator==(const self &x) const                             { return cur == x.cur; }
        bool operator!=(const self &x) const                              { return !(*this==x); }
        bool operator>(const self &x) const                               { return (node==x.node)?(cur<x.cur):(node<x.node); }
        difference_type operator-(const self &x) const
        { return static_cast<difference_type>(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last- x.cur); }
        self& operator++()
        {
            ++cur;
            if(cur == last){
                set_node(node+1);
                cur = first;
            }
            return *this;
        }
        self operator++(int)
        {
            self tmp = *this;
            ++*this;
            return tmp;
        }
        self& operator--()
        {
            --cur;
            if(cur == first){
                set_node(node-1);
                cur = last;
                --cur;
            }
            return *this;
        }
        self operator--(int)
        {
            self tmp = *this;
            --*this;
            return tmp;
        }
        self& operator +=(difference_type n)
        {
            difference_type offset = n + (cur - first);
            if(offset >= 0 && offset < static_cast<difference_type>(buffer_size())){
                cur += n;
            }
            else{
                difference_type node_offset = offset>0?
                            offset/static_cast<difference_type>(buffer_size()):
                            -static_cast<difference_type>((offset-1)/buffer_size())-1;
                set_node(node + node_offset);
                cur = first (offset - node_offset * static_cast<difference_type>(buffer_size()));
            }
            return *this;
        }
        self operator+(difference_type n) const
        {
            self tmp = *this;
            return tmp+=n;
        }
        self& operator-=(difference_type n)
        {
            return *this += -n;
        }
        self operator-(difference_type n) const
        {
            self tmp = *this;
            return tmp -= n;
        }

    };







    template <class T,class Alloc = alloc,size_t BufSize = 0>
    class deque{
    public:
        typedef T                                                                                  value_type;
        typedef T*                                                                                pointer;
        typedef const T*                                                                       const_pointer;
        typedef T&                                                                               reference;
        typedef const T&                                                                      const_reference;
        typedef size_t                                                                            size_type;
        typedef ptrdiff_t                                                                        difference_type;
        typedef __deque_iterator<T,T&,T*,BufSize>                               iterator;
        typedef __deque_iterator<T,const T&,const T*,BufSize>            const_iterator;


    protected:
        typedef pointer*                                                                        map_pointer;
        typedef simple_alloc<value_type,Alloc>                                     data_allocator;
        typedef simple_alloc<pointer,Alloc>                                          map_allocator;


    protected:
        void create_map_and_node(size_type num_elements);


    //成员变量
    protected:
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;


    //构造函数和析构函数
    public:
        deque()                                                            {}

    //接口的声明
    public:

        //迭代器相关
        iterator begin()                                                  { return start; }
        const_iterator cbeign() const                              { return static_cast<const_iterator>(begin()); }
        iterator end()                                                     { return finish; }
        const_iterator cend() const                                 { return static_cast<const_iterator>(end()); }

        //访问元素相关
        reference front()                                                 { return *start; }
        reference back()                                                 { return *(finish - 1); }

        //容量相关
        size_type size() const                                          { return finish - start; }
        bool empty() const                                             { return size()==0; }





    //运算符的重载
    public:
        reference operator[](size_type i)                          { return *(start+i); }
        const_reference operator[](size_type i) const       { return static_cast<const_reference>(*this[i]); }

    };
}

#include "Detail/Deque.impl.h"
#endif // DEQUE_H
