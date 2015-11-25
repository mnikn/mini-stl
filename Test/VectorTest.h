#ifndef VECTORTEST_H
#define VECTORTEST_H

#include "Header/Vector.h"
#include <cassert>
using mstd::vector;

void test_case1()
{
    vector<int> a(2,6);
    vector<int> b = {1,2,3};
    vector<int> c = b;
    assert(a[0] == 6 && a[1] == 6);
    assert(b[0] == 1 && b[1] == 2 && b[2] == 3);
    assert(c == b);
}

void test_case2()
{
    vector<int> a;
    a.push_back(5);
    a.push_back(8);
    a.push_back(4);
    assert(a[0]==5 && a[1]==8 && a[2]==4);

    a.pop_back();
    assert(a[1]==8 && a.size()==2);

    a.pop_back();
    a.pop_back();
    assert(a.empty());
}

void test_case3()
{
    vector<int> a;
    a.insert(a.begin(),4);
    a.insert(a.begin()+1,6);
    assert(a[0]==4&&a[1]==6);

}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
}

#endif // VECTORTEST_H
