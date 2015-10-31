#ifndef ALLOC_H
#define ALLOC_H

#if 0
#include <new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include <iostream>
using std::cerr;using std::endl;
#define __THROW_BAD_ALLOC cerr<<"Out of memory"<<endl;exit(1);
#endif

/**
 *      内存配置器，其中分为第一级内存配置器和第二级内存配置器，
 * 为其他文件提供内存分配的方法。
 */
namespace mstd{

    /**
     *  第一级内存配置器，当要求分配的内存块大于128bytes时
     *使用该配置器，速度较第二级内存配置器慢。
     */

    template <int inst>
    class __malloc_alloc_template{
    private:
        //当内存不足时的函数
        //oom : out of memory
        static void* oom_malloc(size_t n);
        static void* oom_realloc(void*p, size_t n);
        static void (*__malloc_alloc_oom_handler)();//函数指针，用来指定内存的位置

   public:
        static void* allocate(size_t n);
        static void deallocate(void *p,size_t);
        static void* reallocate(void *p, size_t new_size);
        static void (*set_malloc_handler(void (*f)()))();
    };

    typedef __malloc_alloc_template<0> malloc_alloc;

    /**
     *  第二级内存配置器，当要求分配的内存块小于128bytes时
     *使用该配置器，因为使用内存池来分配内存，因而速度较第
     * 一级内存配置器快。
     */

    template <bool threads,int inst>
    class __default_malloc_template{
    private:
        enum {__ALIGN = 8};//小型内存块的上调边界
        enum {__MAX_BYTES = 128};//小型内存块的上限
        enum {__NFREELISTS = __MAX_BYTES/__ALIGN};//free-lists的个数

    private:
        //将bytes上调至8的倍数
        static size_t ROUND_UP(size_t bytes);

    private:
        union obj{
            union obj *free_list_link;
            char client_data[1];
        };

    private:
        static char *start_free;
        static char *end_free;
        static size_t heap_size;
        static obj* volatile free_list[__NFREELISTS];

        static size_t FREELIST_INDEX(size_t bytes);//根据区块大小来决定用第几号free_list
        static void* refill(size_t n);
        static char* chunk_alloc(size_t size,int &nobjs);

    public:
        static void* allocate(size_t n);
        static void deallocate(void *p,size_t n);
        static void* reallocate(void *p,size_t old_size,size_t new_size);

    };
}

#endif // ALLOC_H
