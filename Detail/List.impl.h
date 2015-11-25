#ifndef LIST_IMPL_H
#define LIST_IMPL_H


namespace mstd{

    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T, Alloc>::allocate_node()
    {
        return allocator_type::allocate(static_cast<size_type>(sizeof(link_type)));
    }

    template <class T,class Alloc>
    void list<T, Alloc>::allocate_some_node(size_type n)
    {
        empty_initialize();
        while(n--){
            push_back(T());
        }
    }

    template <class T,class Alloc>
    void list<T,Alloc>::deallocate_node(link_type p)
    {
        allocator_type::deallocate(p);
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T,Alloc>::create_node(const_reference e)
    {
        link_type x = allocate_node();
        construct(x,e);
        return x;
    }

    template <class T,class Alloc>
    void list<T,Alloc>::destory_node(link_type p)
    {
        deallocate_node(p);
        destory(p);
    }

    template <class T,class Alloc>
    void list<T,Alloc>::empty_initialize()
    {
        _size = 0;
        header = allocate_node();
        trailer = allocate_node();
        header->next = trailer;
        trailer->prev = header;
    }

    template <class T,class Alloc>
    void list<T,Alloc>::clear()
    {
        size_type n = size();
        while(n--) pop_back();
    }

    template <class T,class Alloc>
    void list<T,Alloc>::push_front(const_reference e)
    {
        insert(begin(),e);
    }

    template <class T,class Alloc>
    void list<T,Alloc>::push_back(const_reference e)
    {
        insert(end(),e);
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::value_type list<T,Alloc>::pop_front()
    {
        return erase(begin());
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::value_type list<T,Alloc>::pop_back()
    {
        return erase(end()-1);
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::iterator list<T,Alloc>::insert(iterator pos,const_reference e)
    {
        link_type tmp = create_node(e);
        tmp->next = pos.node;
        tmp->prev = pos->prev;
        pos->prev->next = tmp;
        pos->prev = tmp;
        ++_size;
        return iterator(tmp);
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::value_type list<T,Alloc>::erase(iterator pos)
    {
        value_type tmp = *pos;
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        destory_node(pos.node);
        --_size;
        return tmp;
    }

    template <class T,class Alloc>
    bool list<T,Alloc>::operator==(list<T,Alloc> &l)
    {
        if(size() != l.size() ) return false;
        iterator tmp_a = begin();
        iterator tmp_b = l.begin();
        while(tmp_a!=end()){
            if(*tmp_a != *tmp_b) return false;
            ++tmp_a;
            ++tmp_b;
        }
        return true;
    }

    template <class T,class Alloc>
    bool list<T,Alloc>::operator!=(list<T,Alloc> &l)
    {
        if(size() != l.size() ) return true;
        iterator tmp_a = begin();
        iterator tmp_b = l.begin();
        while(tmp_a!=end()){
            if(*tmp_a != *tmp_b) return true;
            ++tmp_a;
            ++tmp_b;
        }
        return false;
    }



}

#endif // LIST_IMPL_H
