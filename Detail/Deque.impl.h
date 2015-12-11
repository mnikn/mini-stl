#ifndef DEQUE_IMPL_H
#define DEQUE_IMPL_H

namespace mstd{


    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::pointer deque<T,Alloc,BufSize>::allocate_node()
    {
        return data_allocator::allocate();
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::deallocate_node(pointer ptr)
    {
        data_allocator::deallocate(ptr);
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
    typename deque<T,Alloc,BufSize>::value_type deque<T,Alloc,BufSize>::pop_back_aux()
    {
        value_type tmp = back();
        deallocate_node(finish.first);
        finish.set_node(finish.node-1);
        finish.cur = finish.last - 1;
        destory(finish.cur);
        return tmp;
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::value_type deque<T,Alloc,BufSize>::pop_front_aux()
    {
        value_type tmp = front();
        destory(start.cur);
        deallocate_node(start.first);
        start.set_node(start.node+1);
        start.cur = start.first;
        return tmp;
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::iterator deque<T,Alloc,BufSize>::insert_aux(iterator pos,const_reference e)
    {
        difference_type index = pos - start;
        value_type e_copy = e;
        if(index < size() / 2){
            push_front(front());
            iterator front_a = start;
            ++front_a;
            iterator front_b = front_a;
            ++front_b;
            pos = start + index;
            iterator pos1 = pos;
            ++pos;
            copy(front_b,pos1,front_a);
        }
        else{
            push_back(back());
            iterator back1 = finish;
            --back1;
            iterator back2 = back1;
            --back2;
            pos = start+index;
            copy_backward(pos,back2,back1);
        }
        *pos = e_copy;
        return pos;
    }

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::clear()
    {
        for(map_pointer node = start.node+1;node < finish.node; ++node){
            destory(*node,*node+iterator::buffer_size());
            data_allocator::deallocate(*node,iterator::buffer_size());
        }
        if(start.node != finish.node){
            destory(start.cur,start.last);
            destory(finish.cur,finish.cur);
            data_allocator::deallocate(finish.first,iterator::buffer_size());
        }
        else{
            destory(start.cur , finish.cur);
        }
        finish = start;
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

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::value_type deque<T,Alloc,BufSize>::pop_back()
    {
        if(finish.cur != finish.first){
            value_type tmp = back();
            --finish.cur;
            destory(finish.cur);
            return tmp;
        }
        else{
            return pop_back_aux();
        }
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::value_type deque<T,Alloc,BufSize>::pop_front()
    {
        if(start.cur != start.last - 1){
            value_type tmp = front();
            destory(finish.cur);
            ++start.cur;
            return tmp;
        }
        else{
            return pop_front_aux();
        }
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::iterator deque<T,Alloc,BufSize>::insert(iterator pos,const_reference e)
    {
        if(pos.cur == start.cur){
            push_front(e);
            return start;
        }
        else if(pos.cur == finish.cur){
            push_back(e);
            iterator tmp = finish;
            return --tmp;
        }
        else{
            return insert_aux(pos,e);
        }
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::value_type deque<T,Alloc,BufSize>::erase(iterator pos)
    {
        value_type tmp = *pos;
        iterator next = pos;
        difference_type index = pos - start;
        if(index < (size() >> 1)){
            copy_backward(start,pos,next);
            pop_front();
        }
        else{
            copy(next,finish,pos);
            pop_back();
        }
        return tmp;
    }

    template <class T,class Alloc,size_t BufSize>
    typename deque<T,Alloc,BufSize>::iterator deque<T,Alloc,BufSize>::erase(iterator first,iterator last)
    {
        if(first == start && last == finish){
            clear();
            return finish;
        }
        else{
            difference_type n = last - first , elems_before = first - start;
            if(elems_before < (size() - n) / 2 ){
                copy_backward(start,first,last);
                iterator new_start = start + n;
                destory(start , new_start);
                for(map_pointer cur = start.node;cur<new_start.node;++cur){
                    data_allocator::deallocate(*cur,iterator::buffer_size());
                }
                start = new_start;
            }
            else{
                copy(last, finish, first);
                iterator new_finish = finish - n;
                destory(new_finish , finish);
                for(map_pointer cur = new_finish.node+1 ; cur <= finish.node ; ++cur){
                    data_allocator::deallocate(*cur , iterator::buffer_size() );
                }
                finish = new_finish;
            }
            return start + elems_before;
        }
    }

}

#endif // DEQUE_IMPL_H
