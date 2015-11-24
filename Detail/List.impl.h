#ifndef LIST_IMPL_H
#define LIST_IMPL_H


namespace mstd{

    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T, Alloc>::allocate_node()
    {
        return allocator_type::allocate(static_cast<size_type>(sizeof(link_type)));
    }

    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T, Alloc>::allocate_some_node(size_type n)
    {
        link_type tmp = begin().node;
        while(n--){
            tmp = allocator_type::allocate(static_cast<size_type>(sizeof(link_type)));
            tmp = tmp->next;
        }
        return begin().node;
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


}

#endif // LIST_IMPL_H
