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
    void vector<T,Alloc>::resize(size_type n)
    {
        if(n > size() ){
            size_type difference = n - size();
            while(difference--) push_back(T());
        }
        finish = start+ n ;
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


            value_type tmp[size()];
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
    typename vector<T,Alloc>::value_type vector<T,Alloc>::pop_back()
    {
        const_reference tmp = back(),n = size();
        destory(finish);
        finish = start + n - 1;
        return tmp;
    }

    template <class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator pos)
    {
        return erase(pos,pos+1);
    }

    template <class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator first,iterator last)
    {
        if(last!=end()){
            copy(last,finish,first);
        }
        size_type n = static_cast<size_type>(last - first);
        finish -= n;
        destory(first,last);
        return last;
    }

    template <class T,class Alloc>
    void vector<T,Alloc>::clear()
    {
        destory(start,finish);
        finish = start;
    }

    template <class T,class Alloc>
    bool vector<T,Alloc>::operator==(const vector<T,Alloc> &v) const
    {
        if(size() != v.size()) return false;
        for(size_type i = 0;i < size();++i) if((*this)[i] != v[i]) return false;
        return true;
    }

    template <class T,class Alloc>
    bool vector<T,Alloc>::operator!=(const vector<T,Alloc> &v) const
    {
        if(size() != v.size()) return true;
        for(size_type i = 0;i < size();++i) if(*this[i] != v[i]) return true;
        return false;
    }

}

#endif // VECTOR_IMPL_H
