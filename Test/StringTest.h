#ifndef STRINGTEST_H
#define STRINGTEST_H

#include "Header/String.h"
#include <cassert>
using mstd::string;

void test_case1()
{
    string s = "DSAd";
    string a(s);
    assert(s == a);
}

void test_case2()
{
    string s;
    s.append(string("DSFSD"));
    assert(s.size()==5);
}

void test_all()
{
    test_case1();
    test_case2();
}

#endif // STRINGTEST_H
