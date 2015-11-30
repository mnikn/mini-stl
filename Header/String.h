#ifndef STRING_H
#define STRING_H

#include "Vector.h"
#include <iostream>
using std::ostream;

/**
 * string，由vector<char>派生而来
 */
namespace mstd{


    class string : public vector<char>{
    //友元运算符的重载
    friend ostream& operator<<(ostream &os,const string &s);


    //构造函数和析构函数
    public:
        string():vector<char>()                                                                                 { }
        string(const string &s):vector<char>(s)                                                        { }
        template <size_type N>
        string(const char (&array)[N]):vector<char>(array)                                       { }
        string(iterator first,iterator last):vector<char>(first,last)                                 { }
        string(const initializer_list<char> &i):vector<char>(i)                                    { }
        string(const char *s)
        { vector<char>();  char tmp = *s; size_type i = 1; while(tmp != '\0') { push_back(tmp);tmp = *(s+i); ++i; } }



    //运算符的重载
    public:
//        string& operator=(const string &s)                                  {  }
//        template <size_type N>
//        string& operator=(const char (&array)[N])                       { return vector<char>::operator =(array); }
//        string& operator=(const initializer_list<char> &i)            { return vector<char>::operator =(i); }
        string& operator=(const char *s)
        { clear(); char tmp = *s; size_type i = 1; while(tmp != '\0') { push_back(tmp);tmp = *(s+i); ++i; } return *this; }
    };

    ostream& operator<<(ostream &os,const string &s)
    {
        for(size_t i = 0;i<s.size();++i){
            os<<s[i];
        }
        return os;
    }
}


#endif // STRING_H
