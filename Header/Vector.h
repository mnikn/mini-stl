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
    void allocate(size_type n);
    void allocate_and_fill(size_type n,const_reference e);
    template <class InputIterator>
    void allocate_and_copy(size_type n,InputIterator first,InputIterator last);
    void deallocate_and_destory_all();
    void insert_aux(iterator pos,const_reference e);




//构造函数与析构函数
public:
    vector() :start(nullptr),finish(nullptr),end_of_storage(nullptr) {}
    explicit vector(size_type n)                                { allocate_and_fill(n,value_type()); }
    vector(size_type n,const_reference e)                { allocate_and_fill(n,e); }
    vector(const vector<T,Alloc> &v)                     { allocate_and_copy(v.size(),v.begin(),v.end()); }
    template <size_type N>
    vector(const value_type (&array)[N] )               { allocate_and_copy(N,array,array+N); }
    vector(const initializer_list<T> &i)                    { allocate_and_copy(i.size(),i.begin(),i.end()); }
    ~vector()                                                         { deallocate_and_destory_all(); }






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
    void insert(iterator pos,const_reference e);
    T pop_back();
    T erase(iterator pos);
    void clear();





public:
    reference operator[](size_type index)
    {
        return *(start + index);
    }
    const_reference operator[](size_type index) const
    {
        return *(start + index);
    }
    vector<T,Alloc>& operator=(const vector<T,Alloc> &v)
    {
        allocate_and_copy(v.size(),v.begin(),v.end());
        return *this;
    }
    template <size_type N>
    vector<T,Alloc>& operator=(const value_type (&array)[N])
    {
        allocate_and_copy(N,array,array+N);
        return *this;
    }
    vector<T,Alloc>& operator=(const initializer_list<T> &i)
    {
        allocate_and_copy(i.size(),i.begin(),i.end());
        return *this;
    }
    bool operator==(const vector<T,Alloc> &v)
    {
        if(size() != v.size()) return false;
        for(size_type i = 0;i < size();++i) if(*this[i] != v[i]) return false;
        return true;
    }
    bool operator!=(const vector<T,Alloc> &v)
    {
        if(size() != v.size()) return true;
        for(size_type i = 0;i < size();++i) if(*this[i] != v[i]) return true;
        return false;
    }
};





/*******************************************/
/***************接口的实现****************/
/*******************************************/

template <class T,class Alloc>
void vector<T,Alloc>::allocate(size_type n)
{
    start = data_allocator::allocate(n);
    finish = start + n;
    end_of_storage = finish;
}

template <class T,class Alloc>
void vector<T,Alloc>::allocate_and_fill(size_type n,const_reference e)
{
    allocate(n);
    uninitialize_fill_n(start,n,e);
}

template <class T,class Alloc>
template <class InputIterator>
void vector<T,Alloc>::allocate_and_copy(size_type n,InputIterator first,InputIterator last)
{
    allocate(n);
    uninitialize_copy(first,last,start);
}

template <class T,class Alloc>
void vector<T,Alloc>::deallocate_and_destory_all()
{
    if(start){
        data_allocator::deallocate(start,capacity());
        destory(start,end_of_storage);
    }
}

template <class T,class Alloc>
void vector<T,Alloc>::insert_aux(iterator pos,const_reference e)
{
    //当还有可用空间时
    if(finish!=end_of_storage){
        construct(finish,*(finish - 1));
        ++finish;
        value_type e_copy = e;
        copy_backward(pos,finish - 2,finish - 1);
        *pos = e_copy;
    }
    else{
        const size_type old_size = size();
        const size_type len = (old_size !=0 ? old_size*2 : 1);

        T tmp[size()];
        difference_type size_a = pos - start,size_b = finish - pos;
        copy(start,finish,tmp);

        finish = copy_n(tmp,size_a,start);//复制前段
        construct(finish++,e);
        finish = copy_n(tmp + size_a,size_b,finish);//复制后段

        end_of_storage = start + len;

    }
}

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
    if(finish != end_of_storage){
        construct(finish++,e);
    }
    else{
        insert_aux(finish,e);
    }
}

template <class T,class Alloc>
void vector<T,Alloc>::insert(iterator pos,const_reference e)
{
    insert_aux(pos,e);
}

template <class T,class Alloc>
T vector<T,Alloc>::pop_back()
{
    const_reference tmp = back(),n = size();
    destory(finish);
    finish = start + n - 1;
    return tmp;
}

template <class T,class Alloc>
T vector<T,Alloc>::erase(iterator pos)
{
    T tmp = *pos;
    if(pos+1 != end()){
        copy(pos+1,finish,pos);
    }
    --finish;
    destory(finish);
    return tmp;
}

template <class T,class Alloc>
void vector<T,Alloc>::clear()
{
    destory(start,finish);
    finish = start;
}

}

#endif // VECTOR_H
