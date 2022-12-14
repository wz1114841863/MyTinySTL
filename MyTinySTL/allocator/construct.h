#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

// 这个头文件包含两个函数 construct， destroy
// construct: 负责构造对象
// destroy: 负责析构对象

#include "../utils/type_traits.h"
#include "../utils/util.h"
#include "../iterator/iterator.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER

namespace mystl {
    // construct
    template <typename Ty>
    void construct(Ty *ptr) {
        ::new ((void *)ptr) Ty();  // placement new
    }

    template <typename Ty1, typename Ty2>
    void construct(Ty1 *ptr, const Ty2& value) {
        ::new ((void *)ptr) Ty1(value);
    }

    template <typename Ty, typename ... Args>  // 可变长参数列表
    void construct(Ty *ptr, Args&& ... args) {
        ::new ((void *)ptr) Ty(mystl::forward<Args>(args)...);  // 完美转发
    }

    // destroy
    template <typename Ty>
    void destroy_one(Ty *, std::true_type) {}

    template <typename Ty>
    void destroy_one(Ty *pointer, std::false_type) {
        if (pointer != nullptr) {
            pointer->~Ty();
        }
    }

    template <typename ForwardIter>
    void destroy_cat(ForwardIter , ForwardIter , std::true_type) {}

    template <typename ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for (; first != last; ++first)
            destroy(& *first);
    }

    template <class Ty>
    void destroy(Ty *pointer) {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template <class ForwardIter>
    void destroy(ForwardIter first, ForwardIter last) {
        destroy_cat(first, last, std::is_trivially_destructible<
                typename iterator_traits<ForwardIter>::value_type>{});
    }
}  // namespace mystl

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif //TINYSTL_CONSTRUCT_H
