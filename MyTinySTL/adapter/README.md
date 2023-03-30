stack:  
为什么底层不用vector而用deque?  
随着容器的增长，向量的重新分配需要将所有元素复制到新的内存块中。增长一个deque会分配一个新的块，并将其链接到块列表中——不需要副本。
如果知道栈不会增长太多，或者您需要频繁地访问栈顶附近的元素，那么vector可能是一个更好的选择。  
栈没有迭代器
``` 
    template <typename T, typename Container = mystl::deque<T>>
    class stack;
    模板类，可指定底层容器，默认为deque
    
    私有成员：
    container_type c_;  // 用底层容器表现stack
    
    // 构造函数
    调用对应底容器的构造函数
    stack() = default;
    stack(size_type n)
    stack(size_type n, const value_type &value)
    stack(IITer first, IIter last)
    stack(const Container &c)
    stack(Container &&c)
    
    // 赋值操作符重载
    调用对应底容器的赋值操作符
    stack &operator=(const stack &rhs)
    stack &operator=(stack &&rhs)
    stack &operator=(std::initializer_list<T> ilist)
    
    // 栈的对应方法
    top()   // 获得栈顶元素
    push()  // 从栈顶压入
    pop()   // 从栈顶弹出
    
    // 容量操作
    empty()
    size()
    emplace()
    clear()
    
    swap()
    
    // 重载比较操作符
    // 一般使用友元friend的形式，友元可以访问任何权限的成员变量
    // 如果使用成员函数的形式，则只带一个参数，还有一个为本身，友元带2个参数
    // c_为私有属性，所以才要使用friend来重载==
    // 使用友元可以使比较操作符成为全局函数，而不是成员函数。这样可以使比较操作符接受两个参数，而不是一个隐式的this参数和一个显式的参数
    // 使用友元可以使比较操作符访问栈的私有成员，例如底层容器的元素。如果不使用友元，就需要提供公有的接口来访问这些成员
    // 使用友元可以使比较操作符支持隐式类型转换，例如将一个整数转换为一个栈对象，然后进行比较
    friend bool operator==(const stack &lhs, const stack &rhs) { return lhs.c_ == rhs.c_; }
    friend bool operator< (const stack &lhs, const stack &rhs) { return lhs.c_ <  rhs.c_; } 
```
queue.h:  
队列，与stack相似，默认以deque为底层容器, 无迭代器
``` 
与stack基本一致, 除以下访问元素的位置:
    front()
    back()
    push()
    emplace()
    
```
priority_queue.h

```  

```