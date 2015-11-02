#ifndef AUTO_PTR_H
#define AUTO_PTR_H

/**
 * 智能指针auto_ptr
 */

namespace mstd {

    template <class T>
    class auto_ptr{
    public:
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef const T*         const_pointer;
        typedef T&                 reference;
        typedef const T&        const_reference;

    private:
        T *pointee;

    public:
        explicit auto_ptr(pointer p=0):pointee(p){}
        template<class U>
        auto_ptr(auto_ptr<U> &rhs):pointee(rhs.release()){}
        ~auto_ptr() {delete pointee;}

    public:
        void reset(const_pointer p)
        {
            pointee = p;
        }
        pointer get() const
        {
            return pointee;
        }
        pointer release() const
        {
            return get();
        }

    public:
        template<class U>
        auto_ptr<T>& operator=(auto_ptr<U> &rhs)
        {
            if(this!=&rhs) reset(rhs.release());
            return *this;
        }
        reference operator*() const
        {
            return *pointee;
        }
        pointer operator->() const
        {
            return pointee;
        }
    };
}

#endif // AUTO_PTR_H
