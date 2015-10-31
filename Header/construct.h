#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <new>

/**
 * 定义了构造函数和析构函数以供其他文件使用
 */
namespace mstd {

    template <class T1,class T2>
    inline void construct(T1 *p,const T2 &value)
    {
        new(p) T1(value);
    }

    template <class T>
    inline void destory(T *p)
    {
        p->~T();
    }
}

#endif // CONSTRUCT_H
