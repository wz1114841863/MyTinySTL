#ifndef TINYSTL_ALLOC_H
#define TINYSTL_ALLOC_H

// 包含类：alloc, 用于分配和回收内存，以内存池的方式实现
#include <new>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace mystl {
    // union: FreeList
    // 采用链表的形式管理内存碎片，分配与回收小内存区块
    union FreeList {
        union FreeList *next;
        char data[1];
    };

    // 不同内存范围的上调大小
    enum {
        EAlign128 = 8,
        EAlign256 = 16,
        EAlign512 = 32,
        EAlign1024 = 64,
        EAlign2048 = 128,
        EAlign4096 = 256
    };

    // 小对象的内存大小
    enum {ESmallObjectBytes = 4096};
    // free lists 个数
    enum {EFreeListsNumber = 56};

    // 空间配置类：alloc
    // 如果内存过大，超过4096 bytes, 直接调用 std::malloc, std::free
    // 当内存较小时，以内存池管理，每次配置一大块内存，并维护对应的自由链表
    class alloc {
    private:
        static char *start_free;  // 内存池起始位置
        static char *end_free;    // 内存池结束位置
        static size_t heap_size;  // 申请heap空间附加值大小

        static FreeList *free_list[EFreeListsNumber];  // 自由链表

    public:
        static void *allocate(size_t n);
        static void deallocate(void *p, size_t n);
        static void *reallocate(void *p, size_t old_size, size_t new_size);

    private:
        static size_t M_align(size_t bytes);
        static size_t M_round_up(size_t bytes);
        static size_t M_freelist_index(size_t bytes);
        static void *M_refill(size_t n);
        static char *M_chunk_alloc(size_t size, size_t &nobj);
    };

    char*  alloc::start_free = nullptr;
    char*  alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;

    FreeList* alloc::free_list[EFreeListsNumber] = {
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr
    };

    // 分配大小为n的空间， n > 0
    inline void *alloc::allocate(size_t n) {
        FreeList *my_free_list;
        FreeList *result;
        if (n > static_cast<size_t>(ESmallObjectBytes))  // 大于4096个字节直接使用malloc
            return std::malloc(n);

        my_free_list = free_list[M_freelist_index(n)];
        result = my_free_list;
        if (result == nullptr) {  // 为空，从内存池申请空间。
            void *r = M_refill(M_round_up(n));
            return r;
        }
        my_free_list = result->next;
        return result;
    }

    // 释放 p 指向的大小为n的空间，p 不能为 0
    inline void alloc::deallocate(void *p, size_t n) {
        if (n > static_cast<size_t>(ESmallObjectBytes)) {  // 大于4096个字节直接使用free
            std::free(p);
            return ;
        }
        auto *q = reinterpret_cast<FreeList*>(p);
        FreeList *my_free_list;
        my_free_list = free_list[M_freelist_index(n)];
        q->next = my_free_list;
        my_free_list = q;
    }

    // 重新分配空间，参数一为指向新空间的指针，参数二为原来空间的大小，参数三为申请空间的大小
    inline void *alloc::reallocate(void *p, size_t old_size, size_t new_size) {
        deallocate(p, old_size);
        p = allocate(new_size);
        return p;
    }

    // bytes 对应上调大小
    inline size_t alloc::M_align(size_t bytes) {
        if (bytes <= 512) {
            return bytes <= 256
                   ? bytes <= 128 ? EAlign128 : EAlign256
                   : EAlign512;
        }
        return bytes <= 2048
               ? bytes <= 1024 ? EAlign1024 : EAlign2048
               : EAlign4096;
    }

    // 讲 bytes 上调至对应区间大小
    inline size_t alloc::M_round_up(size_t bytes) {
        return ((bytes + M_align(bytes) - 1) & ~(M_align(bytes) - 1));
    }

    // 根据区块大小，选择第n个free lists
    inline size_t alloc::M_freelist_index(size_t bytes) {
        if (bytes <= 512) {
            return bytes <= 256
                   ? bytes <= 128
                     ? ((bytes + EAlign128 - 1) / EAlign128 - 1)
                     : (15 + (bytes + EAlign256 - 129) / EAlign256)
                   : (23 + (bytes + EAlign512 - 257) / EAlign512);
        }
        return bytes <= 2048
               ? bytes <= 1024
                 ? (31 + (bytes + EAlign1024 - 513) / EAlign1024)
                 : (39 + (bytes + EAlign2048 - 1025) / EAlign2048)
               : (47 + (bytes + EAlign4096 - 2049) / EAlign4096);
    }

    // 重新填充 free list
    void *alloc::M_refill(size_t n) {  // 这里的n已经是上调过的
        size_t nblock = 10;
        char *c = M_chunk_alloc(n, nblock);  // 引用方式传入
        FreeList *result, *cur, *next;
        // 如果只有一个区块，就把这个区块返回给调用者，free list 没有增加新节点
        if (nblock == 1) {
            return c;
        }
        // 否则把第一个区块返回，其余区块纳入到freelist中作为新节点
        auto my_free_list = free_list[M_freelist_index(n)];
        result = (FreeList *)c;
        my_free_list = next = (FreeList *)(c + n);  //第0个数据块给调用者，地址访问即 chunk~chunk + n - 1
        for (size_t i = 1; ; ++i) {
            cur = next;
            next = (FreeList *)((char *)next + n);
            if (nblock - 1 == i) {
                cur->next = nullptr;
                break;
            }else {
                cur->next = next;
            }
        }
        return result;
    }

    // 从内存池中分配空间给freelist，条件不允许时，会调整nobj，内存不足时，调用其余处理
    char *alloc::M_chunk_alloc(size_t size, size_t &nobj) {
        char *result;
        size_t need_bytes = size * nobj;
        size_t pool_bytes = end_free - start_free;  // 计算内存池剩余空间

        // 如果内存池空间满足需求，返回
        if (pool_bytes >= size) {
            result = start_free;
            start_free += need_bytes;
            return result;
        }else if (pool_bytes >= size) {
            //如果内存池剩余大小不能完全满足需求量，但至少可以分配一个或一个以上的区块，就返回它, 调整nblock
            nobj = pool_bytes / size;
            need_bytes = size * nobj;
            result = start_free;
            start_free += need_bytes;
            return result;

        }else {  // 如果内存池剩余大小连一个区块都无法满足
            if (pool_bytes > 0) {  // 如果内存池还有剩余，将剩余空间加到freelist中
                FreeList *my_free_list = free_list[M_freelist_index(pool_bytes)];
                ((FreeList *)start_free)->next = my_free_list;
                my_free_list = (FreeList *)start_free;
            }
            // 为内存池申请空间
            size_t bytes_to_get = (need_bytes << 1) + M_round_up(heap_size >> 4);
            start_free = (char *)std::malloc(bytes_to_get);
            if (!start_free) {
                // 系统内存不足
                FreeList *my_free_list, *p;
                for (size_t i = size; i <= ESmallObjectBytes; i += M_align(i)) {
                    my_free_list = free_list[M_freelist_index(i)];
                    p = my_free_list;
                    if (p) {
                        my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        return M_chunk_alloc(size, nobj);
                    }
                }
                std::cout << "out of memory" << std::endl;
                end_free = nullptr;
                throw std::bad_alloc();  // 直接抛出异常
            }
            end_free = start_free + bytes_to_get;
            heap_size += bytes_to_get;
            return M_chunk_alloc(size, nobj);  // 递归调用
        }
    }
}  // namespace mystl
#endif //TINYSTL_ALLOC_H
