#ifndef VECTOR_IMPL_H
#define VECTOR_IMPL_H

namespace mstd{



template <class T,class Alloc>
void vector<T,Alloc>::allocate(size_type n)
{
    start = allocator_type::allocate(n);
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
        allocator_type::deallocate(start,capacity());
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

        deallocate_and_destory_all();
        start = allocator_type::allocate(len);

        finish = uninitialize_copy_n(tmp,size_a,start);//复制前段
        construct(finish++,e);
        finish = uninitialize_copy_n(tmp + size_a,size_b,finish);//复制后段

        end_of_storage = start + len;

    }
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
template <class InputIterator>
void vector<T,Alloc>::insert(iterator pos,InputIterator first,InputIterator last)
{
    while(first!=last) insert_aux(pos++,*first++);
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
typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator pos)
{
    iterator tmp = pos;
    if(pos+1 != end()){
        copy(pos+1,finish,pos);
    }
    --finish;
    destory(finish);
    return tmp;
}

template <class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator first,iterator last)
{
    while(first!=last) erase(first++);
    return last;
}

template <class T,class Alloc>
void vector<T,Alloc>::clear()
{
    destory(start,finish);
    finish = start;
}


}

#endif // VECTOR_IMPL_H
