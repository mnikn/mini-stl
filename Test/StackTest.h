#ifndef STACKTEST_H
#define STACKTEST_H

#include "Header/Stack.h"
#include <cassert>
using mstd::stack;

void test_case1()
{
    stack<int> s;
    s.push(4);
    s.push(1);
    s.push(8);
    assert(s.pop()==8&&s.size()==2&&s.top()==1);
    s.pop();
    s.pop();
    assert(s.size()==0);
}

void test_all()
{
    test_case1();
}

#endif // STACKTEST_H
