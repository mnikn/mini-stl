#ifndef LIST_IMPL_H
#define LIST_IMPL_H


namespace mstd{


    /**
     * 给节点分配空间
     * 返回节点的地址
     */
    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T, Alloc>::allocate_node()
    {
        return allocator_type::allocate(static_cast<size_type>(sizeof(link_type)));
    }



    /**
     * 给一定数量的节点分配空间
     * 返回初始节点的地址
     */
    template <class T,class Alloc>
    void list<T, Alloc>::allocate_some_node(size_type n)
    {
        empty_initialize();
        while(n--){
            push_back(T());
        }
    }



    /**
     * 从节点上回收空间
     */
    template <class T,class Alloc>
    void list<T,Alloc>::deallocate_node(link_type p)
    {
        allocator_type::deallocate(p);
    }



    /**
     * 分配空间的同时还构造给节点
     * 返回节点的地址
     */
    template <class T,class Alloc>
    typename list<T,Alloc>::link_type list<T,Alloc>::create_node(const_reference e)
    {
        link_type x = allocate_node();
        construct(x,e);
        return x;
    }




    /**
     * 回收节点的空间并析构节点
     */
    template <class T,class Alloc>
    void list<T,Alloc>::destory_node(link_type p)
    {
        deallocate_node(p);
        destory(p);
    }




    /**
     * 初始化，使头哨兵和尾哨兵指向正确的地方
     */
    template <class T,class Alloc>
    void list<T,Alloc>::empty_initialize()
    {
        _size = 0;
        header = allocate_node();
        trailer = allocate_node();
        header->next = trailer;
        trailer->prev = header;
    }




    /**
     * 把[first,last)转移到pos上
     */
    template <class T,class Alloc>
    void list<T,Alloc>::transfer(iterator pos,iterator first,iterator last)
    {
        if(pos!=last){
            last->prev->next = pos.node;
            first->prev->next = last.node;
            pos->prev->next = first;

            link_type tmp = pos->prev;
            pos->prev = last->prev;
            last->prev = first->prev;
            first->prev = tmp;
        }
    }




    /**
     * 清空列表
     */
    template <class T,class Alloc>
    void list<T,Alloc>::clear()
    {
        size_type n = size();
        while(n--) pop_back();
    }




    /**
     * 向队首添加元素
     */
    template <class T,class Alloc>
    void list<T,Alloc>::push_front(const_reference e)
    {
        insert(begin(),e);
    }




    /**
     * 向队末添加元素
     */
    template <class T,class Alloc>
    void list<T,Alloc>::push_back(const_reference e)
    {
        insert(end(),e);
    }





    /**
     * 删除队首元素
     * 返回原队首元素的值
     */
    template <class T,class Alloc>
    typename list<T,Alloc>::value_type list<T,Alloc>::pop_front()
    {
        return erase(begin());
    }





    /**
     * 删除队末元素
     * 返回队末元素的值
     */
    template <class T,class Alloc>
    typename list<T,Alloc>::value_type list<T,Alloc>::pop_back()
    {
        return erase(end()-1);
    }




    /**
     * 向pos的前方插入元素，值为e
     * 返回 插入元素的地址
     */
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
