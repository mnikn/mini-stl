#ifndef DEQUE_IMPL_H
#define DEQUE_IMPL_H

namespace mstd{

    template <class T,class Alloc,size_t BufSize>
    void deque<T,Alloc,BufSize>::create_map_and_node(size_type num_elements)
    {
        size_type num_nodes = num_elements / iterator::buffer_size() + 1;
        map_size = max(static_cast<size_type>(8),num_nodes + 2);
        map = map_allocator::allocate(map_size);

        map_pointer nstart = map + (map_size - num_nodes) / 2;
        map_pointer nfinish = nstart + num_nodes - 1;
        map_pointer cur;

        //for(cur = nstart;cur<=finish;++cur) *cur = allocate_node();

        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % iterator::buffer_size();
    }
}

#endif // DEQUE_IMPL_H
