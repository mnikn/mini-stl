#ifndef QUEUETEST_H
#define QUEUETEST_H

#include "Header/Queue.h"
#include <assert.h>
using mstd::queue;

void test_case1()
{
    queue<int> a;
    a.push(6);
    a.push(2);
    assert(a.size()==2&&a.front()==6&&a.back()==2);
    a.pop();
    assert(a.front()==6&&a.size()==1);
    a.pop();
    assert(a.empty());
}

void test_all()
{
    test_case1();
}

#endif // QUEUETEST_H
