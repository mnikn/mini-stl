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
    assert(a[0] == 2 && a[1] == 6);
    assert(b[0] == 1 && b[2] == 2 && b[3] == 3);
    assert(c == b;)
}

void test_all()
{

}

#endif // VECTORTEST_H
