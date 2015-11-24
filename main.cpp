#include <iostream>
#include "Header/List.h"
#include "Test/VectorTest.h"
using std::cout;
using std::ends;
using std::endl;
//using std::list;
using namespace mstd;


int main()
{
    list<int> a = {1,2,3};
    cout<<a.begin().node->next;
    return 0;
}

