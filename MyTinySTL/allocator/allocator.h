#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

// allocator: 管理内存的分配、释放，对象的构造、析构
#include "./construct.h"
#include "../utils/util.h"

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

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr, T&& value);

        template <typename... Args>
        static void construct(T *ptr, Args&& ...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T* last);
    };

    template <typename T>
    T *allocator<T>::allocate() {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <typename T>
    T *allocator<T>::allocate(size_type n) {
        if (n == 0) return nullptr;
        return static_cast<T *>(::operator new(n *sizeof(T)));
    }

    template <typename T>
    void allocator<T>::deallocate(T *ptr) {
        if (ptr == nullptr) return;
        ::operator delete(ptr);
    }

    template <typename T>
    void allocator<T>::deallocate(T *ptr, size_type) {
        if (ptr == nullptr) return;
        ::operator delete(ptr);
    }

    template <typename T>
    void allocator<T>::construct(T *ptr) {
        mystl::construct(ptr);
    }

    template <typename T>
    void allocator<T>::construct(T *ptr, const T &value) {
        mystl::construct(ptr, value);
    }

    template <typename T>
    void allocator<T>::construct(T *ptr, T &&value) {
        mystl::construct(ptr, mystl::move(value));
    }

    template <typename T>
    template <typename... Args>
    void allocator<T>::construct(T *ptr, Args&& ...args) {
        mystl::construct(ptr, mystl::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T *ptr) {
        mystl::destroy(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T *first, T* last) {
        mystl::destroy(first, last);
    }
} // namespace mystl
#endif //TINYSTL_ALLOCATOR_H
