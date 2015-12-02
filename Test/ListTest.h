#ifndef LISTTEST_H
#define LISTTEST_H

#include "Header/List.h"
#include <cassert>
using namespace mstd;

void test_case1()
{
    list<int> a = {1,2,3};
    assert(a[0]==1&&a[1]==2&&a[2]==3);

    list<int> b(a);
    assert(a==b);

    list<int> c;
    c = b;
    assert(c==b);

    c.push_back(6);
    assert(c!=b);
}

void test_case2()
{
    list<int> a;
    a.push_back(5);
    a.push_back(8);
    a.push_front(4);
    assert(a[0]==4&&a[1]==5&&a[2]==8);

    a.pop_back();
    assert(a.size()==2);

    a.pop_back();
    a.pop_front();
    assert(a.empty());
}

void test_case3()
{
    list<int> a= {3,4,63,7};
    a.erase(a.begin());
    assert(a[0]==4 && a.size()==3);
}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
}

#endif // LISTTEST_H
