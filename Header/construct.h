#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>

/**
 * 各容器构造函数和析构函数的原型
 */
namespace mstd{

    template<class T1,class T2>
    inline void construct(T1 *ptr,const T2 &value)
    {
        new(ptr) T1(value);
    }

    template<class T>
    inline void destory(T *ptr)
    {
        ptr->~T();
    }


}

#endif // CONSTRUCT_H
