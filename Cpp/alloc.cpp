#include "Header/alloc.h"

using mstd::__malloc_alloc_template;
using mstd::malloc_alloc;
using mstd::__default_malloc_template;

/***第一级内存配置器***/

template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;//初始化指向分配内存地址的函数指针

template <int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (*my_alloc_handler)();
    void *addr;

    //不断尝试释放、配置、释放...
    while (true) {
        my_alloc_handler = __malloc_alloc_oom_handler;
        if(__malloc_alloc_oom_handler==0) __THROW_BAD_ALLOC;
        (*my_alloc_handler)();//调用处理例程，企图释放内存
        addr = malloc(n);
        if(addr) return addr;
    }
}

template <int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (*my_realloc_handler)();
    void *addr;

    while(true){
        my_realloc_handler = __malloc_alloc_oom_handler;
        if(my_realloc_handler==0) __THROW_BAD_ALLOC;
        addr = realloc(p,n);
        if(addr) return (addr);
    }
}

template <int inst>
void* __malloc_alloc_template<inst>::allocate(size_t n)
{
    void *addr = malloc(n);
    if(addr==0) addr = oom_malloc(n);//当内存不足时调用相应的函数
    return addr;
}

template <int inst>
void __malloc_alloc_template<inst>::deallocate(void *p, size_t)
{
    free(p);
}

template <int inst>
void* __malloc_alloc_template<inst>::reallocate(void *p, size_t new_size)
{
    void *addr = realloc(p,new_size);
    if(addr==0) addr = oom_realloc(p,new_size);
    return addr;
}

template <int inst>
void (*__malloc_alloc_template<inst>::set_malloc_handler(void (*f)()))()
{
    void(*old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return old;
}



/***第二级内存配置器***/

template <bool threads,int inst>
char *__default_malloc_template<threads,inst>::start_free = 0;

template <bool threads,int inst>
char *__default_malloc_template<threads,inst>::end_free = 0;

template <bool threads,int inst>
size_t __default_malloc_template<threads,inst>::heap_size = 0;

template <bool threads,int inst>
typename __default_malloc_template<threads,inst>::obj* volatile
__default_malloc_template<threads,inst>::free_list[__NFREELISTS] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template <bool threads,int inst>
size_t __default_malloc_template<threads,inst>::ROUND_UP(size_t bytes)
{
    return (bytes+__ALIGN-1) &  ~(__ALIGN-1);
}

template <bool threads,int inst>
size_t __default_malloc_template<threads,inst>::FREELIST_INDEX(size_t bytes)
{
    return (bytes+__ALIGN-1)/__ALIGN-1;
}

template <bool threads,int inst>
void* __default_malloc_template<threads,inst>::refill(size_t n)
{
    size_t nobjs  = 20;
    char *chunk = chunk_alloc(n,nobjs);
    char* volatile* my_free_list;
    obj *addr;
    obj *current_obj,*next_obj;

    if(nobjs==1) return chunk;
    my_free_list= free_list + FREELIST_INDEX(n);

    addr = (obj*) chunk;
    *my_free_list = next_obj = (obj*)(chunk+n);

    for(int i=1;;++i){
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj+n);
        if(nobjs-1==i){
            current_obj->free_list_link = 0;
            break;
        }
        else{
            current_obj->free_list_link = next_obj;
        }
    }
    return addr;
}

template <bool threads,int inst>
char* __default_malloc_template<threads,inst>::chunk_alloc(size_t size, int &nobjs)
{
    char *result;
    size_t total_bytes = size*nobjs;
    size_t bytes_left = end_free - start_free;

    if(bytes_left>=total_bytes){
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else if(bytes_left>=size){
        nobjs = bytes_left/size;
        total_bytes = size*nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else{
        size_t bytes_to_get = 2*total_bytes+ROUND_UP(heap_size>>4);
        if(bytes_left>0){
            obj* volatile* my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj*)start_free;
        }
        start_free = (char*)malloc(bytes_to_get);
        if(start_free==0){
            obj* volatile *my_free_list,*p;
            for(int i=0;i<=__MAX_BYTES;i+=__ALIGN){
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if(p!=0){
                    *my_free_list = p->free_list_link;
                    start_free = (char*)p;
                    end_free = start_free + i;
                    return chunk_alloc(size,nobjs);
                }
            }
            end_free = 0;
            start_free = (char*)malloc_alloc::allocate(bytes_to_get);
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size,nobjs);
    }
}

template <bool threads,int inst>
void* __default_malloc_template<threads,inst>::allocate(size_t n)
{
    obj* volatile* my_free_list;
    obj *addr;

    if(n>(size_t)__MAX_BYTES) return malloc_alloc::allocate(n);

    my_free_list = free_list + FREELIST_INDEX(n);
    addr = *my_free_list;

    if(addr==0){
        void *r = refill(ROUND_UP(n));
        return r;
    }

    *my_free_list = addr->free_list_link;
    return addr;
}

template <bool threads,int inst>
void __default_malloc_template<threads,inst>::deallocate(void *p, size_t n)
{
    obj *q = (obj*)p;
    obj* volatile* my_free_list;

    if(n>(size_t)__MAX_BYTES) {malloc_alloc::deallocate(p,n);return;}

    my_free_list = free_list + FREELIST_INDEX(n);
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

template <bool threads,int inst>
void* __default_malloc_template<threads,inst>::reallocate(void *p, size_t old_size, size_t new_size)
{
    obj* volatile* my_free_list;
    obj *addr;

    if(new_size>(size_t)__MAX_BYTES) return malloc_alloc::reallocate(p,new_size);

    my_free_list = free_list + FREELIST_INDEX(new_size);
    addr = *my_free_list;

    if(addr==0){
        void *r = refill(ROUND_UP(new_size));
        return r;
    }

    *my_free_list = addr->free_list_link;
    return addr;
}

