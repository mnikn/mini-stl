#include "Header/BigInt.h"
using mstd::bigInt;



bigInt& bigInt::operator+=(bigInt &otr)
{
    bool add_one = false;

    long long int i = 0;
    while(i < len() && i <otr.len() ){
        if(add_one){
            _digits.back()++;
            add_one = false;
        }
        if(_digits[i] + otr._digits[i] >= 10 ){
            add_one = true;
            _digits[i] += otr._digits[i] - 10;
        }
        else{
            _digits[i] += otr._digits[i];
        }
        ++i;
    }
    if(add_one){
        _digits.back()++;
    }
    while(i < otr.len())  push_back(otr._digits[i++]);

    return *this;
}

//bigInt bigInt::operator-=(bigInt &otr)
//{

//}

//bigInt bigInt::operator*=(bigInt &otr)
//{

//}

//bigInt bigInt::operator/=(bigInt &otr)
//{

//}
