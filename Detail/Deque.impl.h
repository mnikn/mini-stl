#ifndef DEQUE_IMPL_H
#define DEQUE_IMPL_H

namespace mstd{


    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::pointer deque<T,Alloc,BufSize>::allocate_node()
    {
        return data_allocator::allocate();
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::reserve_at_back(size_type nodes_to_add)
    {
        if(nodes_to_add + 1 > map_size - (finish.node - map)){
            reallocate_map(nodes_to_add,false);
        }
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::reserve_at_front(size_type nodes_to_add)
    {
        if(nodes_to_add > (start.node - map)){
            reallocate_map(nodes_to_add,true);
        }
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::reallocate_map(size_type nodes_to_add,bool add_at_front)
    {
        size_type old_num_nodes = finish.node - start.node + 1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;

        map_pointer new_nstart;
        if(map_size > 2 *new_num_nodes){
            new_nstart = map + (map_size - new_num_nodes) /2 + (add_at_front ? nodes_to_add : 0);
            if(new_nstart < start.node){
                copy(start.node,finish.node + 1,new_nstart);
            }
            else{
                copy_backward(start.node,finish.node+1,new_nstart+old_num_nodes);
            }
        }
        else{
            size_type new_map_size = map_size + max(map_size,nodes_to_add);
            map_pointer new_map = map_allocator::allocate(new_map_size);
            new_nstart = new_map + (new_map_size - new_num_nodes) /2 +(add_at_front?nodes_to_add:0);
            copy(start.node,finish.node+1,new_nstart);
            map_allocator::deallocate(map,map_size);
            map = new_map;
            map_size = new_map_size;
        }
        start.set_node(new_nstart);
        finish.set_node(new_nstart + old_num_nodes - 1);
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::create_map_and_node(size_type num_elements)
    {
        size_type num_nodes = num_elements / iterator::buffer_size() + 1;
        map_size = max(static_cast<size_type>(8),num_nodes + 2);
        map = map_allocator::allocate(map_size);

        map_pointer nstart = map + (map_size - num_nodes) / 2;
        map_pointer nfinish = nstart + num_nodes - 1;
        map_pointer cur;

        for(cur = nstart;cur<=nfinish;++cur) *cur = allocate_node();

        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % iterator::buffer_size();
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::fill_initialize(size_type n,const_reference value)
    {
        create_map_and_node(n);
        map_pointer cur;
        for(cur = start.node;cur != finish.node;++cur){
            uninitialize_fill(*cur,*cur + iterator::buffer_size(),value);
        }
        uninitialize_fill(finish.first,finish.cur,value);
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::copy_initialize(iterator first,iterator last)
    {
        create_map_and_node(static_cast<size_type>(last - first));
        map_pointer cur = start.node;
        uninitialize_copy(first,last,*cur);
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::push_back_aux(const_reference e)
    {
        value_type e_copy = e;
        reserve_at_back();
        *(finish.node + 1) = allocate_node();
        construct(finish.cur,e_copy);
        finish.set_node(finish.node+1);
        finish.cur = finish.first;
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::push_front_aux(const_reference e)
    {
        value_type e_copy = e;
        reserve_at_front();
        *(start.node - 1) = allocate_node();
        start.set_node(start.node - 1);
        start.cur = start.last - 1;
        construct(start.cur,e_copy);
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::push_back(const_reference e)
    {
        if(finish.cur != finish.last - 1){
            construct(finish.cur,e);
            ++finish.cur;
        }
        else{
            push_back_aux(e);
        }
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::push_front(const_reference e)
    {
        if(start.cur != start.first){
            construct(start.cur - 1,e);
            --start.cur;
        }
        else{
            push_front_aux(e);
        }
    }
}

#endif // DEQUE_IMPL_H
