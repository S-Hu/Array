# Array
模拟 Vector 实现作业
要求:
1. 作业提交时间:2015 年 11 月 04 日 24:00 前,延期记为 0 分;
2. 尽量模拟 Vector 实现,支持在任意位置的增删改等操作;
3. 定义的 Array 独立放在 Array.h 中(类的实现也在该文件中),类命名
为 Array。迭代器定义在 Array 之中,其实现在 Array 之外。 Array
及其 iterator 的函数都必须在类之外定义。
4. 防止头文件被多次载入;
5. 注意指针、构造函数、拷贝构造函数以及析构函数的使用,尤其
是析构函数中有关 new 分配内存空间的正确释放;
6. 适当注释有助于得分;
7. 注意 const、&的使用;
8. 实现迭代器,不包括const系列迭代器,支持begin()、end()、rbegin()、
rend()等函数;支持++、--、!=等运算符重载;
9. 支持如下有关容量的函数:size()、resize()、capacity()、empty()等;
10.支持如下数据读取函数:[]、back()、at()、front()等; 11.支持如下数据修改函数:assign()、push_back()、pop_back()、insert()、
erase()、swap()、clear()。
