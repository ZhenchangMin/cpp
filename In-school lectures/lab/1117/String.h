// String.h
// 注意：当前文件为String.h，请在String.cpp中实现各成员函数！
// 注意：当前文件为String.h，请在String.cpp中实现各成员函数！
// 注意：当前文件为String.h，请在String.cpp中实现各成员函数！

#include <iostream>
using namespace std;

class String {
private:
  int len;     // 字符串长度
  char *str_p; // 字符串数据

public:
  const char *getStr_p() { return str_p; }
  const int getLen() { return len; }
  String() {
    len = 0;
    str_p = new char[1];
    str_p[0] = '\0';
    }
  String(const char *s);
  String(const String &s);

  ~String(); // 注意内存泄漏和野指针问题

  void print(); // 输出字符串，最后输出换行符\n
  // TODO: 重载操作符=
  String &operator=(const String &s);
  String &operator=(const char *s);

  // TODO: 重载操作符[]
  char &operator[](int index);

  // TODO:重载操作符+实现字符串拼接 a+b=ab
  String operator+(const String& s) const;
  // TODO:重载实现操作符 ==
  bool operator==(const String& s);
  // TODO:重载实现操作符 !=
  bool operator!=(const String& s);
  // TODO:重载实现操作符 <  返回值为bool类型，按ASCII码值比较，约定 a<aa
  bool operator<(String& s);
};