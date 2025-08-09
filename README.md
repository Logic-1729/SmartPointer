# Project 2: $\mathrm{Smart Pointer}$

> SJTU CS1958-01 2025Fall 第二次大作业

请先阅读[智能指针那些事儿](https://notes.sjtu.edu.cn/feladvRRTXSjGqzARi9Kxg?both),:)
    
# `Unique_ptr`
    
你需要构造的 `unique_ptr` 模版类的要求包括：
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 `_p` 置为 `nullptr` 的默认构造函数
    
     ``` 
    UniquePtr<int> ptr;
    ```
    
- 要求实现能够支持将普通指针转换成 `unique_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
    UniquePtr<int> ptr{new int{10}};
    ```
    
- 要求实现 `unique_ptr` 间的移动构造函数，并禁止拷贝构造函数的存在
    
     ```
     UniquePtr<int> ptr2{ptr1};//编译错误
    ```
    
- 在类外编写类似于 `std::make_unique` 的函数模版，要求能够支持形如
    ```
    UniquePtr<int> ptr{make_unique<int>(10)};
    UniquePtr<std::vector<int>> ptr2{make_unique<std::vector<int>>(2,3)};
    ```
    的构造方式，注意传入的参数的个数以及值类别形式。
    
- 要求拥有析构函数 `~UniquePtr()` 删除动态指针并将其置为 `nullptr`(思考：为什么要置空)
    
- 要求重载解引用运算符 `operator*`，实现与普通指针相同的功能
    
     ```
     UniquePtr<int> ptr{new int{10}};
     std::cout << *ptr << std::endl; // output: 10
     ```
    
- 要求重载间接引用运算符 `operator->`，实现与普通指针相同的功能
     ```
      UniquePtr<std::string> ptr{new std::string{"hello"}};
      std::cout << ptr->length() << std::endl; // output: 5
     ```
    
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false;
      ```
      UniquePtr<std::string> ptr{new std::string{"hello"}};
      std::cout << bool(ptr) << std::endl; // output: true
      ```
    
- 要求重载运算符 `operator=`，实现 `unique_ptr` 间的移动赋值并禁止拷贝赋值
     ```
     UniquePtr<int> ptr1{new int{10}};
     UniquePtr<int> ptr2{new int{11}};
     ptr2 = ptr1;// 编译错误
     ```
    
- 要求实现 `get()` 函数用以返回存储在类中的原始指针
      ```
      UniquePtr<int> ptr{new int{10}};
      std::cout << ptr.get() << std::endl; // output: raw pointer stored in the class
      ```
- 要求实现 `reset()` 函数，包括实现以下两种参数形式：
      1.    `void reset();` 删除原有指针并分配 `nullptr` 给它；
     1.    `void reset(T* p)` 删除原有指针并分配 `p` 给它
 
     ```
     UniquePtr<std::string> ptr{new std::string{"hello"}};
     ptr.reset(new std::string{"nice"});
     std::cout << *ptr << std::endl; // output: nice
     ```
    
- 要求实现 `release` 函数用以返回一个指向原对象的普通指针，同时让对象脱离 `unique_ptr` 的管理。在此期间，`unique_ptr` 类不删除原有指针。
     ```
     UniquePtr<double> ptr{new double{1.567}};
     double *tmp{ptr.release()};
     std::cout << *tmp << std::endl; // output: 1.567
     delete tmp; // manual deletion
     ```


# `Shared_ptr`
    
`shared_ptr` 中你需要实现:
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 ```_p``` 置为 `nullptr` 的默认构造函数
    
     ``` 
     SharedPtr<int> ptr;
    ```
    
- 要求实现能够支持将普通指针和 `unique_ptr` 转换成 `shared_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
     UniquePtr<int> ptr{new int{1}};
     SharedPtr<int> sp1{new int{10}};
     SharedPtr<int> sp2{ptr};
    ```
    
- 要求实现 `shared_ptr` 间的移动构造函数与拷贝构造函数
    
     ```
     SharedPtr<int> ptr2{ptr1};//编译成功
    ```
    
- 在类外编写类似于 `std::make_shared` 的函数模版，要求能够支持形如
    ```
     SharedPtr<int> ptr{make_shared<int>(10)};
    ```
    的构造方式，注意传入的参数的个数以及值类别形式。
    
- 要求拥有析构函数 `~SharedPtr()` 删除动态指针并将其置为 `nullptr`
    
- 要求重载解引用运算符 `operator*`，实现与普通指针相同的功能
    
     ```
      SharedPtr<int> ptr{new int{10}};
      std::cout << *ptr << std::endl; // output: 10
     ```
    
- 要求重载间接引用运算符 `operator->`，实现与普通指针相同的功能
     ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      std::cout << ptr->length() << std::endl; // output: 5
     ```
    
- 要求重载运算符 `operator=`，实现 `shared_ptr` 间的移动赋值与拷贝赋值
     ```
      SharedPtr<int> ptr1{new int{10}};
      SharedPtr<int> ptr2{new int{11}};
      ptr2 = ptr1;
     ```
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false;
      ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      std::cout << bool(ptr) << std::endl; // output: true
      ```
    
- 要求实现 `get()` 函数用以返回存储在类中的原始指针
      ```
       SharedPtr<int> ptr{new int{10}};
       std::cout << ptr.get() << std::endl; // output: raw pointer of the class
      ```
- 要求实现 `reset()` 函数，包括实现以下两种参数形式：
      1.    `void reset();` 删除原有指针并分配 `nullptr` 给它；
     1.    `void reset(T* p)` 删除原有指针并分配 `p` 给它
 
     ```
      SharedPtr<std::string> ptr{new std::string{"hello"}};
      ptr.reset(new std::string{"nice"});
      std::cout << *ptr << std::endl; // output: nice
     ```
    
- 要求实现 `use_count()` 函数用以返回指向当前的对象的所有 `shared_ptr` 实例数
     ```
      SharedPtr<int> ptr1{make_shared<int>(10)};
      std::cout << ptr1.use_count() << std::endl; // output: 1
      SharedPtr<int> ptr2{ptr1};
      std::cout << ptr1.use_count() << std::endl; // output: 2
      std::cout << ptr2.use_count() << std::endl; // output: 2
     ```

# `Weak_ptr` 
为此，你需要构造的 `weak_ptr` 模版类的要求包括：
    
- 有名为 `T* _p`（T 是模板参数）的成员变量来存储给定的指针
    
- 要求实现能够将 `_p` 置为 `nullptr` 的默认构造函数
    
     ``` 
    WeakPtr<int> wp;
    ```
    
- 要求实现能够支持将 `shared_ptr` 转换成 `weak_ptr` 的构造函数,注意传入的参数的值类别形式：
    
     ```
    SharedPtr<int> sp{new int{10}};
    WeakPtr<int> wp{sp};
    ```
    
- 要求实现移动构造函数与拷贝构造函数，注意在拷贝构造中可以通过 $\mathrm{shared_ptr}$ 构造 $\mathrm{weak_ptr}$
    
     ```
     WeakPtr<int> wp1{sp};
    WeakPtr<int> wp2{wp1};//编译成功
    WeakPtr<int> wp2{std::move(wp1)};//编译成功
    ```
    
- 要求拥有析构函数 `~WeakPtr()` 删除动态指针并将其置为 `nullptr`
    
- 要求重载运算符 `operator=`，实现移动赋值与拷贝赋值，注意在拷贝赋值中可以将 `shared_ptr` 赋给 `weak_ptr`
     ```
     WeakPtr<int> wp1, wp2;
     SharedPtr<int> sp{new int{10}};
     wp1 = sp;//编译成功
     wp2 = wp1;//编译成功
     WeakPtr<int> wp1{sp}, wp2;
     wp2 = std::move(wp1);//编译成功
     ```
- 要求重载类型转换符 `bool()` 来判断指针是否为空，非空返回 true,空返回 false;
      ```
      WeakPtr<int> wp;
     SharedPtr<int> sp{new int{10}};
     wp = sp;
      std::cout << bool(wp) << std::endl; // output: true
      ```    

- 要求实现 `lock()` 函数用以转换 `weak_ptr` 为 `shared_ptr`。如果对象已被删除，则返回一个空的 `shared_ptr`。
      ```
      WeakPtr<int> wp{sp};
      SharedPtr<int> sp2 = wp.lock();
      if(sp2) {
          std::cout << *sp2 << std::endl;  // Use the object safely
      }
      ```
- 要求实现 `expired()` 函数用以检查 `weak_ptr` 所指向的对象是否已被删除，返回 `true` 表示被删除，返回 `false` 表示没有被删除
      ```
      WeakPtr<int> wp{sp};
      if(!wp.expired()) {
          SharedPtr<int> sp2 = wp.lock();
      // Use sp2...
      }
      ```
- 要求实现 `reset()` 函数，删除原有指针并分配 `nullptr` 给它；
     ```    
     WeakPtr<int> wp{sp};
     wp.reset();  // wp no longer references anything
     ```
    
- 要求实现 `use_count()` 函数用以返回指向当前的对象的所有 `shared_ptr` 实例数
     ```
      SharedPtr<int> ptr1{make_shared<int>(10)};
      std::cout << ptr1.use_count() << std::endl; // output: 1
      SharedPtr<int> ptr2{ptr1};
      std::cout << ptr1.use_count() << std::endl; // output: 2
      std::cout << ptr2.use_count() << std::endl; // output: 2
     ```
    
- 要求实现 `swap()` 函数，交换两个 `weak_ptr` 对象
     ```
     WeakPtr<int> wp1{sp1}, wp2{sp2};
     wp1.swap(wp2);  // wp1 now watches sp2's object, wp2 watches sp1's
     ```
    
# 注意事项
    
1. 在完成本次大作业时，请对三个智能指针全部有所了解之后再开始设计，以避免不必要的局部修改或整体重构 (尤其是 `shared_ptr` 与 `weak_ptr`)
   
2. 注意函数实现中的细节，譬如 `const`，`noexpect`,`explicit` 等，这些都需要自己补充，这些都有可能成为 `Code Review` 中考察的对象。
    
# Bonus
    
以下挑战完全是可选的，不会被测试或评分：
- 为 `weak_ptr` 实现线程安全的引用计数。
- 支持数组并使其与自定义删除器兼容。例如：
```cpp
  void TEST10(double& score) {
	    // Test weak_ptr with arrays
	    SharedPtr<int[]> sp1{new int[5]{1, 2, 3, 4, 5}};
	    WeakPtr<int[]> wp1(sp1);
	
	    // Test that after move, the moved-from weak_ptr is expired
	    WeakPtr<int[]> wp2(std::move(wp1));
	    // A moved-from weak_ptr should be expired
	    if (!wp1.expired()) {
	        result = false;
	        return;
	    }
	
	    // Test that the moved-to weak_ptr works correctly
	    SharedPtr<int[]> sp2 = wp2.lock();
	    if (!sp2 || sp2[0] != 1 || sp2[1] != 2) {
	        result = false;
	        return;
	    }
	
	    sp1.reset();
	    wp2.reset();  // Need to reset wp2 explicitly
	    if (wp2.lock()) {
	        result = false;
	        return;
	    }
	
	    score += 0.055;
    }
```
- 添加 `owner_before()` 成员函数以实现关联容器中的一致排序。
    
- 在 `if` 条件中使用自定义智能指针。如果智能指针包含 `nullptr` ，则该条件返回 `false` 否则返回 `true`。


	```cpp
	UniquePtr<double> ptr{new double{1.567}};
    if(ptr) // => true
        // something
	ptr.reset();
	if(ptr) // => false
        // some other thing
	```
	使其对 `UniquePtr`, `SharedPtr` and `WeakPtr` 都生效.
    
    
## 须知

### 截止时间

第九周周日（12/26）24:00

### 编译与运行

本项目需要自行构建样例的 `cpp` 文件用以调试，善用 `valgrind`，这会有所帮助。

### 提交方式

请各位自行测试无误后将 `git` 仓库提交到 ACMOJ 对应渠道即可.

### 评分规则

对于 `Basic` 部分：

`Unique_ptr`: 25 `pts`

`Shared_ptr`: 25 `pts`

`Weak_ptr`: 30 `pts`

对于 `Extension` 部分，`ACMOJ` 上的 `Allocator` 计 5pts ， 其余部分酌情加 0-5 pts；

对于 Code Review 部分，占 10 `pts`.

本项目的得分上限是 100 `pts`，不会溢出。
    
## Acknowledgement
    
特别感谢 `Amirkabir University of Technology 1400-2 —— Advanced Programming Course Project 4 'Smart Pointers'` .

感谢 2022 级汪畋宇学长创建了这个项目。

感谢 2025 级黄捷航修正了 `README.md`。

如有问题请联系本项目的发布者 `PhantomPhoenix`, 他的邮箱地址是: `logic_1729@sjtu.edu.cn`







