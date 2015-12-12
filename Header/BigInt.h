#ifndef BIGINT_H
#define BIGINT_H

#include <deque>
#include <iostream>
using std::ostream;
using std::deque;

/**
 * 大整数
 */
namespace mstd{

    class bigInt{
        friend ostream& operator<<(ostream &os,bigInt b)
        {
            for(auto it = b._digits.end() - 1; it >= b._digits.begin(); --it)  os<<(*it);
            return os;
        }

    public:
        typedef int                                      value_type;
        typedef int&                                   reference;
        typedef const int&                          const_reference;
        typedef size_t                                  size_type;


    public:
        deque<int> _digits;

    public:
        bigInt() = default;
        bigInt(const deque<int> &digits):_digits(digits)                   { }
        bigInt(long long int num)                                                   { while(num) { _digits.push_back(num%10); num /= 10; } }



    public:
        size_type len() const                                                           { return _digits.size(); }
        void clear()                                                                         { _digits.clear(); }
        void push_back(value_type digit)                                        { _digits.push_back(digit); }
        void push_front(value_type digit)                                        { _digits.push_front(digit); }
        void pop_back()                                                                  {  _digits.pop_back(); }
        void pop_front()                                                                 {  _digits.pop_front(); }



    public:
        bigInt& operator+=(bigInt &otr);
        bigInt& operator-=(bigInt &otr);
        bigInt& operator*=(bigInt &otr);
        bigInt& operator/=(bigInt &otr);
    };


}

#endif // BIGINT_H
