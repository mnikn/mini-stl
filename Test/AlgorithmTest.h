#ifndef ALGORITHMTEST_H
#define ALGORITHMTEST_H

#include "Header/Algorithm.h"
#include <cassert>
using namespace mstd;

void test_case1()
{
    int a[] = {1,2,3,4};
    reverse(a,a+4);
    assert(a[0]==4&&a[1]==3&&a[2]==2&&a[3]==1);
}

void test_case2()
{
    int a = 2,b = 4;

    assert(max(a,b)==4);
    assert(min(a,b)==2);

    swap(a,b);
    assert(a==4&&b==2);
}

void test_case3()
{
    int a[] = {1,2,4,3};
    assert(is_in(a,a+4,3));
    assert(find(a,a+4,2)==(a+1));
}

void test_all()
{
    test_case1();
    test_case2();
    test_case3();
}

#endif // ALGORITHMTEST_H
