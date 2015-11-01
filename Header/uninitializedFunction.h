#ifndef UNINITIALIZED_COPY_H
#define UNINITIALIZED_COPY_H

namespace mstd {
    template <class InputIterator,class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result);

    template <class ForwardIterator,class T>
    ForwardIterator uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& e);

    template <class ForwardIterator,class Size,class T>
    ForwardIterator uninitialized_fill_n(ForwardIterator first,Size n,const T& e);
}


#endif // UNINITIALIZED_COPY_H
