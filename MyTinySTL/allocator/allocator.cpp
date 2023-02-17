#include "allocator.h"

namespace mystl {
    // 申请空间
    template <typename T>
    T *allocator<T>::allocate() {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <typename T>
    T *allocator<T>::allocate(size_type n) {
        if (n == 0) return nullptr;
        return static_cast<T*>(::operator new(n *sizeof(T)));
    }

    // 释放空间
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

    // 构造
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
}  // namespce mystl