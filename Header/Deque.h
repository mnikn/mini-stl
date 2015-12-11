#ifndef DEQUE_H
#define DEQUE_H

#include "Alloc.h"
#include "Uninitialize_funtion.h"
#include "Iterator.h"
#include <iostream>
using std::ostream;


/**
 * 双头队列，元素的空间位置连续，空间由map来控制，
 * 一个map里面有一段连续的内存空间，空间大小用BufSize表示
 */
namespace mstd{

    // 若n不为0，传回n，表示buffer size由用户定义
    // n为0，表示buffer size使用默认值
    // 若元素大小size小于512，传回512/size
    // 若size不小于512，传回1
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


        __deque_iterator() = default;

        static size_type buffer_size() { return __deque_buf_size(BufSize,sizeof(T)); }
        void set_node(map_pointer new_node)
        {
            node = new_node;
            first = *new_node;
            last = first + static_cast<difference_type>(buffer_size());
        }

        reference operator*() const                                             { return *cur; }
        pointer operator->() const                                              { return &(operator*()); }
        reference operator[](difference_type n) const                  { return *(*this+n); }
        bool operator==(const self &x) const                             { return cur == x.cur; }
        bool operator!=(const self &x) const                              { return *this!=x; }
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
            if(cur == first){
                set_node(node-1);
                cur = last;
                --cur;
            }
            --cur;
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
                cur = first + (offset - node_offset * static_cast<difference_type>(buffer_size()));
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
        friend ostream& operator<<(ostream& os,self s)
        {
            os<<s.cur;
            return os;
        }

    };







    template <class T,class Alloc = alloc,size_t BufSize = 20>
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


    //辅助函数
    protected:
        pointer allocate_node();
        void deallocate_node(pointer ptr);
        void reserve_at_back(size_type nodes_to_add = 1);
        void reserve_at_front(size_type nodes_to_add = 1);
        void reallocate_map(size_type nodes_to_add,bool add_at_front);
        void create_map_and_node(size_type num_elements);
        void fill_initialize(size_type n,const_reference value);
        void push_back_aux(const_reference e);
        void push_front_aux(const_reference e);
        value_type pop_back_aux();
        value_type pop_front_aux();
        iterator insert_aux(iterator pos,const_reference e);



    //成员变量
    protected:
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;


    //构造函数和析构函数
    public:
        deque():map(0),map_size(0)                                                                { fill_initialize(0,value_type()); }
        deque(size_type n):map(0),map_size(0)                                               { fill_initialize(n,value_type()); }
        explicit deque(size_type n,const_reference value):map(0),map_size(0)  { fill_initialize(n,value); }


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


        //修改容器相关
        void clear();
        void push_back(const_reference e);
        void push_front(const_reference e);
        value_type pop_back();
        value_type pop_front();
        iterator insert(iterator pos,const_reference e);
        value_type erase(iterator pos);
        iterator erase(iterator first,iterator last);


    //运算符的重载
    public:
        reference operator[](size_type n)                          { return start[static_cast<difference_type>(n)]; }
        const_reference operator[](size_type i) const       { return static_cast<const_reference>(*this[i]); }

    };
}

#include "Detail/Deque.impl.h"
#endif // DEQUE_H
