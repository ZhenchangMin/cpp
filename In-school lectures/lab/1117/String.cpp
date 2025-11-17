// String.cpp
#include "String.h"
#include <cstring>

// TODO: 实现 String 的各个成员函数

String::String(const char *s) {
  if (s == nullptr) {
        len = 0;
        str_p = new char[1];
        str_p[0] = '\0';
    } else {
        len = strlen(s);
        str_p = new char[len + 1];
        strcpy(str_p, s);
    }
}

String::String(const String &s) {
  len = s.len;
  str_p = (char *)malloc(sizeof(char) * len);
  strcpy(str_p, s.str_p);
}

String::~String() {
  delete[] str_p;
  len = 0;
  str_p = nullptr;
}

void String::print() {
  cout << str_p << endl;
}

String &String::operator=(const String &s) {
    if (this == &s) return *this;

    delete[] str_p;
    len = s.len;
    str_p = new char[len + 1];
    strcpy(str_p, s.str_p);

    return *this;
}

String &String::operator=(const char *s) {
    delete[] str_p;

    len = strlen(s);
    str_p = new char[len + 1];
    strcpy(str_p, s);

    return *this;
}

char &String::operator[](int index) { return str_p[index]; }


String String::operator+(const String &s) const {
    int total_len = len + s.len;
    char *new_str = new char[total_len + 1];

    strcpy(new_str, str_p);
    strcat(new_str, s.str_p);

    String result(new_str);

    delete[] new_str;

    return result;
}

bool String::operator==(const String &s) {
    if (len != s.len) return false;
    return strcmp(str_p, s.str_p) == 0;
}

bool String::operator!=(const String &s) {
    return !(*this == s);
}

bool String::operator<(String &s) {
    return strcmp(str_p, s.str_p) < 0;
}