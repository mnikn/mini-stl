#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H


/**
 * 对于各种类型的特性进行设定，以供内存管理器使用
 */
namespace mstd{

    struct __true_type {};
    struct __false_type {};

    template <class T>
    struct __type_traits{
        typedef __true_type                         member_first;
        typedef __false_type                        has_trivial_default_constructor;
        typedef __false_type                        has_trivial_copy_constructor;
        typedef __false_type                        has_trivial_assignment_operator;
        typedef __false_type                        has_trivial_destructor;
        typedef __false_type                        is_POD_type;
    };

    template <class T>
    struct __type_traits<T*>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<int>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<unsigned int>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<char>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<bool>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<long>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<unsigned long>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<float>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<double>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<short>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };

    template <>
    struct __type_traits<unsigned short>{
        typedef __true_type                        has_trivial_default_constructor;
        typedef __true_type                        has_trivial_copy_constructor;
        typedef __true_type                        has_trivial_assignment_operator;
        typedef __true_type                        has_trivial_destructor;
        typedef __true_type                        is_POD_type;
    };
}

#endif // TYPE_TRAITS_H
