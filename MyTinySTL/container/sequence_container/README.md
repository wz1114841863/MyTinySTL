包含常见的顺序容器  
    vector、 list、deque  
```
vector:
    // 空间配置器：
        mystl::allocator<T>
        
    // 迭代器, 是普通指针：
    // 问题：算法是基于迭代器的，但vector的迭代器是普通指针，如何调用函数。
       value_type*  
       
    // 使用三个迭代器标识容器的位置
    begin_、end_、cap_
    
    // 构造函数 
    vector();           // 默认构造函数，调用try_init()
    explicit vector(n); // 有参构造函数, 申请n个value_type()
    vector(n, value);   // 有参构造函数, 使用n个value
    // 辅助函数
    try_init();             // 默认申请16个大小的元素，失败的话，所有迭代器赋为nullptr
    init_space(size, cap);  // 申请cap个大小的元素，失败的话，所有迭代器赋为nullptr
    fill_init(n, value);    // 
```