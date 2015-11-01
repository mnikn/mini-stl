#include <iostream>
#include <vector>
#include "Header/type_traits.h"
#include "Header/iterator.h"
#include "Header/alloc.h"
#include "Header/auto_ptr.h"
using namespace mstd;
using namespace std;

int main()
{
    auto_ptr<string> s(new string("SS"));
    return 0;
}

