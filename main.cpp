#include <iostream>
#include "Header/BigInt.h"
using std::cout;
using std::ends;
using std::endl;
using namespace mstd;


int main()
{
    bigInt a = 344;
    bigInt b = 266;
    a += b;
    cout<<a;
    return 0;
}

