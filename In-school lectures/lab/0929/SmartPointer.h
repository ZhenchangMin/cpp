#include <iostream>
class Node;
class SmartPointer
{
  Node *pointer;
  int *ref_cnt;

public:
  SmartPointer()
  {
    // 空指针
    pointer = nullptr;
    ref_cnt = nullptr;
  }
  SmartPointer(Node *p)
  {
    pointer = p;
    ref_cnt = new int(1);
  }

  // 需要完成的函数
  SmartPointer(const SmartPointer &sptr);
  void assign(const SmartPointer &sptr); // 指针赋值，将sptr赋值给本指针
  ~SmartPointer();                       // 析构函数，注意：为通过测试样例，需要保证析构函数可以被重复调用
};

class Node
{
  int id;

public:
  Node(int id)
  {
    this->id = id;
  }
  ~Node()
  {
    std::cout << id << ' ';
  }
};
