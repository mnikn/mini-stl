#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include "Header/Alloc.h"
#include "Header/Uninitialize_funtion.h"
using std::initializer_list;

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
    typedef simple_alloc<value_type,Alloc>           data_allocator;
    iterator start;                         //目前使用空间的首
    iterator finish;                        //目前使用空间的尾
    iterator end_of_storage;         //目前可用空间的尾





//辅助函数
protected:
    iterator allocate_and_fill(size_type n,const_reference e)
    {
        iterator result = data_allocator::allocate(n);
        uninitialize_fill_n(result,n,e);
        return result;
    }
    void fill_initialize(size_type n,const_reference e)
    {
        start = allocate_and_fill(n,e);
        finish = start + n;
        end_of_storage = finish;
    }
    void deallocate()
    {
        if(start){
            data_allocator::deallocate(start,end_of_storage-start);
        }
    }
    void insert_aux(iterator pos,const_reference e)
    {
        //当还有可用空间时
        if(finish!=end_of_storage){
            construct(finish,*(finish-1));
            ++finish;
            value_type e_copy = e;
            copy_backward(pos,finish-2,finish-1);
            *pos = e_copy;
        }
        else{
            const size_type old_size = size();
            const size_type len = (old_size!=0?2*old_size:1);
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;


            new_finish = uninitialize_copy(start,pos,new_start);//复制前段
            construct(new_finish++,e);
            new_finish = uninitialize_copy(pos,finish,new_finish);//复制后段

            destory(begin(),end());
            deallocate();

            start = new_start;
            finish = new_finish;
            end_of_storage = start+len;
        }
    }


//构造函数与析构函数
public:
    vector() :start(nullptr),finish(nullptr),end_of_storage(nullptr) {}
    explicit vector(size_type n)                                { fill_initialize(n,value_type()); }
    vector(size_type n,const_reference e)                { fill_initialize(n,e); }
    vector(const vector<T,Alloc> &v)                     { uninitialize_copy(v.begin(),v.end(),start); }
    template <size_type N>
    vector(const value_type (&array)[N] )               { uninitialize_copy(array,array+N,start); }
    vector(const initializer_list<T> &i)                    { uninitialize_copy(i.begin(),i.end(),start); }
    ~vector()                                                         { destory(start,finish);deallocate(); }






//接口的声明
public:
    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;
    reference front() const;
    reference back() const;
    size_type size() const;
    size_type capacity() const;
    void push_back(const_reference e);





public:
    reference operator[](size_type index)
    {
        return *(start+index);
    }
};





/*******************************************/
/***************接口的实现****************/
/*******************************************/

template <class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::begin() const
{
    return start;
}

template <class T,class Alloc>
typename vector<T,Alloc>::const_iterator vector<T,Alloc>::cbegin() const
{
    return start;
}

template <class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::end() const
{
    return finish;
}

template <class T,class Alloc>
typename vector<T,Alloc>::const_iterator vector<T,Alloc>::cend() const
{
    return finish;
}

template <class T,class Alloc>
typename vector<T,Alloc>::reference vector<T,Alloc>::front() const
{
    return *start;
}

template <class T,class Alloc>
typename vector<T,Alloc>::reference vector<T,Alloc>::back() const
{
    return *finish;
}

template <class T,class Alloc>
typename vector<T,Alloc>::size_type vector<T,Alloc>::size() const
{
    return size_type(finish-start);
}

template <class T,class Alloc>
typename vector<T,Alloc>::size_type vector<T,Alloc>::capacity() const
{
    return size_type(end_of_storage-start);
}

template <class T,class Alloc>
void vector<T,Alloc>::push_back(const_reference e)
{
    if(finish!=end_of_storage){
        construct(finish++,e);
    }
    else{
        insert_aux(finish,e);
    }
}

}

#endif // VECTOR_H
