#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>

/**
 * 迭代器和迭代器特性器的设定
 */
namespace mstd{

struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_acess_iterator_tag : public bidirectional_iterator_tag{};

template <class Category,class T,class Distance = ptrdiff_t,class Pointer = T*,class Reference = T&>
struct iterator{
    typedef Category                            iterator_category;
    typedef T                                        value_type;
    typedef Distance                             difference_type;
    typedef Pointer                               pointer;
    typedef Reference                           reference;
};

template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category                iterator_category;
    typedef typename Iterator::value_type                          value_type;
    typedef typename Iterator::difference_type                  difference_type;
    typedef typename Iterator::pointer                               pointer;
    typedef typename Iterator::reference                            reference;
};

template <class T>
struct iterator_traits<T*>{
    typedef random_acess_iterator_tag                   iterator_category;
    typedef T                                                          value_type;
    typedef ptrdiff_t                                               difference_type;
    typedef T*                                                        pointer;
    typedef T&                                                       reference;
};

template <class T>
struct iterator_traits<const T*>{
    typedef random_acess_iterator_tag                           iterator_category;
    typedef T                                                                  value_type;
    typedef ptrdiff_t                                                        difference_type;
    typedef const T*                                                        pointer;
    typedef const T&                                                       reference;
};

template <class Iterator>
inline typename Iterator::value_type value_type(Iterator)
{
    typedef typename iterator_traits<Iterator>::value_type value_type;
    return value_type();
}

template <class Iterator>
inline typename Iterator::iterator_category iterator_category()
{
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    return iterator_category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type difference_type()
{
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    return difference_type();
}

}

#endif // ITERATOR_H
