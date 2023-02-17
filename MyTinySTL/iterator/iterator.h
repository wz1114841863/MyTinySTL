#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H

// 迭代器设计：
#include <cstddef>
#include "../utils/type_traits.h"

namespace mystl {
    // 五种迭代器类型
    struct input_iterator_tag {};  // 只读
    struct output_iterator_tag {};  // 只写
    struct forward_iterator_tag : public input_iterator_tag {};  // 允许读写，但只能做前向移动
    struct bidirectional_iterator_tag : public forward_iterator_tag {};  // 允许读写，可以做双向移动
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};  // 允许读写，可以任意移动

    // iterator 模板
    template <typename Category, typename T, typename Distance = ptrdiff_t,
            typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Category        iterator_category;
        typedef T               value_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
        typedef Distance        difference_type;
    };

    // iterator traits
    template<typename T>
    struct has_iterator_cat {
    private:
        struct two {
            char a;
            char b;
        };

        template<typename U>
        static two test(...);

        template<typename U>
        static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    template <typename Iterator, bool>
    struct iterator_traits_impl {};

    template <typename Iterator>
    struct iterator_traits_impl<Iterator, true> {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::difference_type   difference_type;
    };

    template <typename Iterator, bool>
    struct iterator_traits_helper {};

    template <typename Iterator>
    struct iterator_traits_helper<Iterator, true>
        : public iterator_traits_impl<Iterator,
        std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value> {};

    // 萃取迭代器的特性
    template <typename Iterator>
    struct iterator_traits
    : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

    // 针对原生指针的偏特化版本
    template <typename T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    template <typename T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef ptrdiff_t                   difference_type;
    };

    template <typename T, typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
    : public m_bool_constant<std::is_convertible<
    typename iterator_traits<T>::iterator_category, U>::value> {};

    // 萃取某种迭代器
    template <typename T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};

    template <typename Iterator>
    struct is_input_iterator : public has_iterator_cat_of<Iterator, output_iterator_tag> {};

    template <typename Iterator>
    struct is_forward_iterator : public has_iterator_cat_of<Iterator, forward_iterator_tag> {};

    template <typename Iterator>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iterator, bidirectional_iterator_tag> {};

    // template <typename Iterator>
    // struct is_iterator :
    //         public m_bool_constant<is_input_iterator<Iterator>::value ||
    //         is_output_iterqtor<Iterator>::value> {};

    // 萃取某个迭代器的 category
    template <typename Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&) {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }


    //
} // namespace mystl

#endif //TINYSTL_ITERATOR_H
