#include "Header/vector.h"

using mstd::allocator;
using mstd::vector;

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
bool vector<T,Alloc>::empty() const
{
    return size()==0;
}

template <class T,class Alloc>
typename vector<T,Alloc>::size_type vector<T,Alloc>::size() const
{
    return size_type(finish - start);
}

template <class T,class Alloc>
typename vector<T,Alloc>::size_type vector<T,Alloc>::capacity() const
{
    return size_type(end_of_storage - start);
}

template <class T,class Alloc>
void vector<T,Alloc>::push_back(const_reference x)
{
    if(finish!=end_of_storage){
        Alloc::construct(finish,x);
        ++finish;
    }
}

template <class T,class Alloc>
typename vector<T,Alloc>::value_type vector<T,Alloc>::pop_back()
{
    --finish;
    Alloc::destory(finish);
}
