#ifndef DEQUETEST_H
#define DEQUETEST_H

#include "Header/Deque.h"
#include <cassert>
using mstd::deque;

void test_case1()
{
    deque<int> a(5,3);
    assert(a[0]==3&&a[4]==3&&a.size()==5);

    deque<int> b(3);
    assert(b.size()==3);

    deque<int> c;
    assert(c.size()==0);
}

void test_case2()
{
    deque<int> a;
    a.push_back(4);
    a.push_back(7);
    a.push_front(3);
    assert(a[0]==3&&a[1]==4&&a[2]==7);
}

void test_all()
{
    test_case1();
    test_case2();
}

#endif // DEQUETEST_H
