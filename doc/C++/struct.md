```c++
// struct的对其方式，如下三种
#pragma pack(1) // 设置以1字节对齐
#pragma pack() // 取消对齐
#pragma pack(2) // 设置两字节对其
#pragma pack() // 取消对齐
#pragma pack(push, 1) // 临时设置1字节对其
#pragma pack(pop) // 回复原来的对齐模式

// C++11以上
struct alignas(16) MyStruct{
  int a,
  char b
}
alignas(32) int a[4]; // alignas作用在变量上，也可以作用在成员变量
alignof(MySturct); // 可以获取到对应类型的对齐方式
```
