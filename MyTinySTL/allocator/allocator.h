#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

// allocator: 管理内存的分配、释放，对象的构造、析构
#include "construct.h"
#include "util.h"

namespace mystl {
    // allocator
    template <class T>
    class allocator {
    public:
        typedef T            value_type;
        typedef T*           pointer;
        typedef const T*     const_pointer;
        typedef T&           reference;
        typedef const T&     const_reference;
        typedef size_t       size_type;
        typedef ptrdiff_t    difference_type;

    public:
        static T *allocate();
        static T *allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T &value);
        static void construct(T *ptr, T &&value);

        template <typename... Args>
        static void construct(T *ptr, Args&& ...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };
} // namespace mystl
#endif //TINYSTL_ALLOCATOR_H
