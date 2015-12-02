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
    friend string operator+(string &s1,string &s2);





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




    //接口的声明
    public:
        void append(const string &s);
        void append(const char *s);




    //运算符的重载
    public:
        string& operator=(const string &s)                                  {  *this = string(s); return *this; }
        template <size_type N>
        string& operator=(const char (&array)[N])                       { *this = string(array); return *this; }
        string& operator=(const initializer_list<char> &i)            { *this = string(i); return*this; }
        string& operator=(const char *s)
        { clear(); char tmp = *s; size_type i = 1; while(tmp != '\0') { push_back(tmp);tmp = *(s+i); ++i; } return *this; }
        string& operator+=(const string &s)                               { append(s); return *this; }
        string& operator+=(const char *s)                                  { append(s); return *this; }
        string& operator*=(size_type n)                                      { string tmp = *this; while(--n) append(tmp); return *this; }
        string operator*(size_type n)                                           { string tmp = *this; tmp *=n; return tmp; }
    };




    ostream& operator<<(ostream &os,const string &s)
    {
        for(size_t i = 0;i<s.size();++i){
            os<<s[i];
        }
        return os;
    }
    string operator+(string &s1,string &s2)
    {
        s1 += s2;
        return s1;
    }

}

#include "Detail/String.impl.h"
#endif // STRING_H
