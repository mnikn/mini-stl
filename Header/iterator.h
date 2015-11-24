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
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

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
        typedef random_access_iterator_tag                   iterator_category;
        typedef T                                                          value_type;
        typedef ptrdiff_t                                               difference_type;
        typedef T*                                                        pointer;
        typedef T&                                                       reference;
    };

    template <class T>
    struct iterator_traits<const T*>{
        typedef random_access_iterator_tag                           iterator_category;
        typedef T                                                                  value_type;
        typedef ptrdiff_t                                                        difference_type;
        typedef const T*                                                        pointer;
        typedef const T&                                                       reference;
    };

    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
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







    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    __distance(InputIterator first,InputIterator last,input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while(first != last){
            ++first;
            ++n;
        }
        return n;
    }

    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    __distance(RandomAccessIterator first,RandomAccessIterator last,random_access_iterator_tag)
    {
        return last - first;
    }

    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first,InputIterator last)
    {
        typename iterator_traits<InputIterator>::iterator_category       iterator_category;
        return __distance(first,last,iterator_category());
    }









    template<class InputIterator>
    inline void __advance(InputIterator &i,ptrdiff_t n,input_iterator_tag)
    {
        while(n--) ++i;
    }

    template<class BidirectionaIterator>
    inline void __advance(BidirectionaIterator &i,ptrdiff_t n,bidirectional_iterator_tag)
    {
        if(n>0) while(n--) ++i;
        else while(n--) --i;
    }

    template<class RandomAccessIterator>
    inline void __advance(RandomAccessIterator &i,ptrdiff_t n,random_access_iterator_tag)
    {
        i += n;
    }

    template<class InputIterator>
    inline void advance(InputIterator &i,ptrdiff_t n)
    {
        __advance(i,n,iterator_category(i));
    }

}

#endif // ITERATOR_H
