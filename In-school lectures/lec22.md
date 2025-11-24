# Lec22: 泛型程序设计
## 泛型的基本概念
在程序设计中，经常需要用到一些**功能和实现都完全相同**的程序实体，但它们所涉及的**数据类型不同**。

例如，下面是对不同元素类型的数组进行排序的函数：
```cpp
void int_sort(int x[],int num);
void double_sort(double x[],int num);
void A_sort(A x[],int num);
```
这三个函数采用了同一种排序算法，并且都是由小到大排序。
能不能只用一个函数？

再例如，下面是元素类型不同的栈类：
```cpp
class IntStack
{		int buf[100];
	public:
		void push(int);
		void pop(int&);
};

class DoubleStack
{	double buf[100];
   public:
	void push(double);
	void pop(double&);
};

class AStack
{	A buf[100];
   public:
	void push(A);
	void pop(A&);
};
```
这三个类都用数组来表示栈的元素，操作的实现也相同
能不能只写一个类？

### 泛型程序设计
一个程序实体能对**多种类型的数据**进行相同操作的特性称为**类属**（Generics）
基于具有类属特性的程序实体进行程序设计的技术称为：**泛型程序设计**(Generic Programming)
具有类属特性的**程序实体**通常有：
- 类属函数
- 类属类

## 类属函数
类属函数是指能对**多种类型的数据**进行**相同操作**的函数。
C++中提供两种实现类属函数的方式：
- 通用指针类型的参数（C语言继承而来）
- 函数模板

### 用**通用指针参数**实现类属的排序函数
```cpp
typedef unsigned char byte;

void sort(void *base, //需排序的数据（数组）内存首地址
        unsigned int num, //数据元素的个数
        unsigned int element_size, //一个数据元素所占内存大小（字节数）
        bool (*cmp)(const void *, const void *) ) //比较两个元素的函数，函数指针
{ //不论采用何种排序算法，一般都需要对数组进行以下操作：
     //取第i个元素（由数组内存首地址、元素的偏移量以及元素所占内存大小决定）
      (byte *)base+i*element_size
     //比较第i个和第j个元素的大小 （利用调用者提供的回调函数cmp来实现，该函数返回true表示是需要的顺序）
      if (!cmp((byte *)base+i*element_size,(byte *)base+j*element_size))
      { //交换第i个和第j个元素的位置
        byte *p1=(byte *)base+i*element_size,
	     *p2=(byte *)base+j*element_size;
         for (int k=0; k<element_size; k++) //把两个元素逐个字节进行交换
         { byte temp=p1[k]; p1[k] = p2[k]; p2[k] = temp; } 
      }
}
```
使用这个sort函数，以对int型数组进行排序为例：
```cpp
//先定义一个对int型数据进行比较的函数
bool int_cmp(const void *p1, const void *p2)
{ return *((int *)p1) < *((int *)p2); }

int a[100]; 
......
//用int型数组调用sort
sort(a,100,sizeof(int),int_cmp);
```

用通用指针实现类属函数面临的问题：
- 需要大量的指针操作，比较麻烦，容易出错！
- 编译程序无法进行参数类型检查。

### 用**函数模板**实现类属的排序函数
函数模板是指带有类型参数的函数定义，格式如下：
```cpp
template <class T1, class T2, ...> //class也可以写成typename
<返回值类型> <函数名>(<参数表>)
{	......
}
```
在函数定义的前面加上关键词template以及函数模板的参数T1、T2等（它们的取值是某个类型）。
函数的<返回值类型> 、<参数表>中的参数类型以及函数体中的局部变量的类型可以是：T1、T2等。

```cpp
template <class T> 
void sort(T elements[], unsigned int count)
{	
	......
	//比较第i个和第j个元素的大小
	if (!(elements[i] < elements[j]))
   { //交换第i个和第j个元素
	   T temp=elements [i];
	   elements[i] = elements [j];
	   elements[j] = temp;
   }
    ......
}
```
如何使用？
```cpp
int a[100];
sort(a,100);  //对int类型数组进行排序

double b[200]; 
sort(b,200);  //对double类型数组进行排序

A c[300]; 
sort(c,300);  //对A类型数组进行排序
       //在类A中，需重载操作符：<
       //可能还需要自定义拷贝构造函数和重载操作符=
```

**函数模板的实例化**
函数模板定义了一系列重载的函数。
要使用函数模板所定义的函数，首先必须要对函数模板进行实例化，给模板参数提供一个**具体的类型**，从而生成具体的函数
函数模板的实例化通常是**隐式**的，由编译程序根据**函数调用的实参类型**自动地把函数模板实例化为具体的函数。
这种确定函数模板实例的过程叫做**模板实参推导**（template argument deduction）
```cpp
int a[100];
sort (a,100);  
//实例化：用int去替代模板参数T
void sort(int elements[], unsigned int count) { ...... }
```
如果我们想要自定义的排序顺序，该怎么办？
```cpp
template <class T1, class T2> 
void sort(T1 elements[], unsigned int count, T2 cmp)
{	......
	//调用cmp来比较第i个和第j个元素的大小
	if (!cmp(elements[i],elements[j]))
   { 交换元素次序 
   }
	......
}
int a[100];
//由小到大排序
sort(a,100,[](int &x1,int &x2) { return x1<x2;});
//由大到小排序
sort(a,100,[](int &x1,int &x2) { return x1>x2;});
//上述调用的实例化：用int去替代T1，用λ表达式所属类型去替代T2
```

有时，编译程序无法根据调用时的实参类型来确定所调用的模板实例函数。例如： 
```cpp
template <class T> 
T max(T a, T b)
{ return a>b?a:b;
}
......
int x,y,z;
double l,m,n;
z = max(x,y); //实例化和调用：int max(int,int)
l = max(m,n); //实例化和调用：double max(double,double)
max(x,m) //这个如何实例化？
```
解决办法：
- 显式类型转换
```cpp
   max((double)x,m); //实例化：double max(double a,double b)
   // OR
   max(x,(int)m); //实例化：int max(int a,int b)
```
- 显式实例化，在尖括号中指定模板参数的类型
```cpp
	max<double>(x,m); //实例化：double max(double a,double b)
    // OR
	max<int>(x,m); //实例化：int max(int a,int b)
```

除了类型参数外，函数模板还可以带有非类型参数
```cpp
template <class T, int size> //size为一个int型的普通参数
void f(T a)
{	T temp[size];
	......  
}
```
这样的函数模板在使用时需要显式实例化。例如，
```cpp
f<int,10>(1);  //实例化成模板函数f(int a)，其中的size为10 
```

## 类模板
例如，用类模板实现类属的栈类：
```cpp
template <class T> 
class Stack
{		T buffer[100];
		int top;
public:
		Stack() { top = -1; }
		void push(const T &x);
		void pop(T &x);
};
template <class T> //注意！！！类外实现的成员函数需加上模板头
void Stack <T>::push(const T &x) { ...... }
template <class T> //注意！！！类外实现的成员函数需加上模板头
void Stack <T>::pop(T &x) { ...... }
```

**类模板的实例化**
类模板定义了若干个类，在使用这些类之前需要对类模板进行实例化
类模板的实例化需要在程序中**显式地指出**
```cpp
Stack<int> st1; //实例化int型栈类并创建一个相应类的对象
int x;
st1.push(10); st1.pop(x);
```

除了类型参数外，类模板也可以带**非类型参数**。 例如：
```cpp
template <class T, int size> 
class Stack
{		T buffer[size];
		int top;
	public:
		Stack() { top = -1; }
		void push(const T &x);
		void pop(T &x);
};
template <class T,int size> 
void Stack <T,size>::push(const T &x) { ...... }
template <class T, int size> 
void Stack <T,size>::pop(T &x) { ...... }
......
// 实例化：用int去替代T，用100去替代size
Stack<int,100> st1; //st1为元素个数最多为100的int型栈
// 实例化：用double去替代T，用200去替代size
Stack<double,200> st2; //st2为元素个数最多为200的double型栈
```

## 模板的复用
模板也属于一种多态，称为**参数化多态**：
一段带有类型参数的代码，给该参数提供不同的类型就能得到多个不同的代码，即，**一段代码有多种解释**。
模板的复用是通过对模板进行**实例化**（用一个具体的类型去替代模板的类型参数）来实现的。
由于模板的实例化是在编译时刻进行的，它一定要见到相应的源代码，因此，模板属于**源代码复用**。

下面情况，可能会出问题：
```cpp
// file1.h
template <class T> 
class S //类模板S的定义
{    T a;
  public:
      void f();
};
extern void func(); //全局函数的声明

// file1.cpp
#include "file1.h"
template <class T> 
void S<T>::f() //类模板S中f的实现
{ ......
}
void func()
{ S<float> x; //实例化“S<float>”并创建该类的一个对象x
   x.f(); //实例化“void S<float>::f()”并调用之
} 
// file2.cpp
#include "file1.h"
int main()
{ S<float> s1; //实例化“S<float>”并创建该类的一个对象s1
   s1.f(); //没有实例化“void S<float>::f()”，但调用之
   S<int> s2; //实例化“S<int>”并创建该类的一个对象s2 
   s2.f(); //没有实例化“void S<int>::f()”，但调用之
   func();
   return 0;
} 
```
两个模块都能通过编译，但在连接时出错，连接程序指出：
```
undefined reference to `void S<int>::f()'
```
在file2里面，只include了.h而没有.cpp，所以在他的成员函数f()调用时：
- “void S<int>::f()”不存在，没有具体实现！
- 虽然也没实例化“void S<float>::f()”，但在file1.cpp中有这个实例，file2中调用的是file1中的实例。

解决上述问题的通常做法是把模板的定义和实现**都放在头文件中**，把有关模板的源代码都包含在头文件中。
但是这样有新问题，就是重复实例的问题。

**重复实例的处理**
在由多模块构成的程序中，由于每个模块是单独编译的，因此，会导致一个模板的某个实例存在于多个模块的编译结果中：
- 相同的函数模板实例
- 相同的类模板成员函数实例
相同代码的存在会造成目标代码庞大

由**开发环境**来解决：记住已编译过的模块信息，编译第二个模块的时候不生成重复实例。（代价大！）
由**链接程序**来解决：相同的实例只保留一个，其余的舍弃。
