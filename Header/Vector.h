#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include "Header/Alloc.h"
#include "Header/Uninitialize_funtion.h"
using std::initializer_list;

/**
 * 向量，线性容器，读取和写入数据复杂度为O(1)，插入和删除复杂度为O(n)
 */

namespace mstd{

    template <class T,class Alloc = alloc>
    class vector{

    public:
        typedef T                           value_type;
        typedef T*                          iterator;
        typedef const T*                 const_iterator;
        typedef T&                         reference;
        typedef const T&                const_reference;
        typedef size_t                      size_type;
        typedef ptrdiff_t                  difference_type;


    protected:
        typedef simple_alloc<value_type,Alloc>           allocator_type;
        iterator start;                         //目前使用空间的首
        iterator finish;                        //目前使用空间的尾
        iterator end_of_storage;         //目前可用空间的尾


    //辅助函数
    protected:
        void allocate(size_type n);
        void allocate_and_fill(size_type n,const_reference e);
        template <class InputIterator>
        void allocate_and_copy(size_type n,InputIterator first,InputIterator last);
        void deallocate_and_destory_all();
        void insert_aux(iterator pos,const_reference e);


    //构造函数与析构函数
    public:
        vector():start(nullptr),finish(nullptr),end_of_storage(nullptr) {}
        explicit vector(size_type n)                                { allocate_and_fill(n,value_type()); }
        vector(size_type n,const_reference e)                { allocate_and_fill(n,e); }
        vector(const vector<T,Alloc> &v)                     { allocate_and_copy(v.size(),v.begin(),v.end()); }
        template <size_type N>
        vector(const value_type (&array)[N] )               { allocate_and_copy(N,array,array+N); }
        vector(const initializer_list<T> &i)                    { allocate_and_copy(i.size(),i.begin(),i.end()); }
        ~vector()                                                         { deallocate_and_destory_all(); }


    //接口的声明
    public:

        //迭代器相关
        iterator begin() const                  { return start; }
        const_iterator cbegin() const       { return start; }
        iterator end() const                     { return finish; }
        const_iterator cend() const          { return finish; }

        //访问元素相关
        reference at(size_type i) const     { return *(start+i); }
        reference front() const                { return *start; }
        reference back() const                { return *(finish-1); }

        //容量相关
        size_type size() const                  { return static_cast<size_type>(finish - start); }
        bool empty() const                     { return size()==0; }
        size_type capacity() const           { return end_of_storage - start; }

        //修改容器相关
        void clear();
        void push_back(const_reference e);
        T pop_back();
        template <class InputIterator> void insert(iterator pos,InputIterator first,InputIterator last);
        void insert(iterator pos,const_reference e);
        iterator erase(iterator pos);
        iterator erase(iterator first,iterator last);


    //运算符的重载
    public:
        reference operator[](size_type index)                       { return *(start + index); }
        const_reference operator[](size_type index) const    { return *(start + index); }

        vector<T,Alloc>& operator=(const vector<T,Alloc> &v)
        { allocate_and_copy( v.size() , v.begin() , v.end() ); return *this; }

        template <size_type N>
        vector<T,Alloc>& operator=(const value_type (&array)[N])
        { allocate_and_copy( N , array , array + N ); return *this; }

        vector<T,Alloc>& operator=(const initializer_list<T> &i)
        { allocate_and_copy( i.size() , i.begin() , i.end() ); return *this; }

        bool operator==(const vector<T,Alloc> &v)
        {
            if(size() != v.size()) return false;
            for(size_type i = 0;i < size();++i) if((*this)[i] != v[i]) return false;
            return true;
        }
        bool operator!=(const vector<T,Alloc> &v)
        {
            if(size() != v.size()) return true;
            for(size_type i = 0;i < size();++i) if(*this[i] != v[i]) return true;
            return false;
        }
    };

}

#include "Detail/Vector.impl.h"
#endif // VECTOR_H
