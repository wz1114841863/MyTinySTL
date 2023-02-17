#ifndef TINYSTL_LIST_H
#define TINYSTL_LIST_H


// 这个头文件包含一个模板类
// list

#include <initializer_list>

#include "../iterator/iterator.h"
#include "../utils/util.h"

// 未完成文件
#include "memory.h"
#include "functional.h"
#include "exceptdef.h"

namespace mystl {
    template <class T> struct list_node_base;
    template <class T> struct list_node;

    template <class T>
    struct node_traits {
        typedef typename node_traits<T>::base_ptr base_ptr;
        typedef typename node_traits<T>::node_ptr node_ptr;

        base_ptr prev;  // prev node
        base_ptr next;  // next node

        list_node_base() = default;

        void unlink() {
            prev = next = self;
        }
    };
}
#endif //TINYSTL_LIST_H
