# Lec14: 动态对象空间的自动回收
## 智能指针
可以针对某个类重载“->”、“*”等**用于指针的操作符**，这样就可以把该类的对象当指针来用，实现一种智能指针（smart pointers）。
例如，下面的B类中重载了操作符“->”：
```cpp
B b=&a; //或B b(&a); b是个智能指针对象，它指向a
b->f(); //把b当指针来用（通过b访问对象a的成员f）
```
- 通过智能指针去访问它指向的对象之前能做一些额外的事情。（**在操作符重载函数中实现**）
- 通过智能指针可以**管理**它指向的对象空间，实现动态对象空间的**自动回收**。

### 间接类成员访问操作符“->”的重载
“->”为一个双目操作符：
- 第一个操作数为一个指向类或结构的**指针**。
- 第二个操作数为第一个操作数所指向的类或结构的**成员**。

p->m 等价于 (*p).m，即先对p解引用，得到一个类或结构的对象，然后访问该对象的成员m。

需求：通过一个函数访问某个对象的成员，如何知道在该函数中访问了该对象的成员多少次？
```cpp
class A
{		int x,y;
	public:
		void f();
		void g();
};
void func(A *p) //p是一个普通指针
{  ...... p->f(); ...... p->g(); ...... //通过p访问对象a的成员
}
......
A a;
func(&a); //调用func，a传给它
...... //调用完func后，如何知道在func中访问了a的成员多少次？
```
第一种解决方案：在类A中加一个计数器count，在构造函数中把它初始化为0，在每个成员函数中把它加1
```cpp
class A
{	int x,y;
	int count;
public:
    int z;
	A() { count = 0; ... }
	void f() { count++; ... }
	void g() { count++; ... }
	int num_of_access() const { return count; }
};
void func(A *p) {  ...... p->f(); ...... p->g(); ...... p->z; }
......
A a;
func(&a);
... a.num_of_access() ... //获得对a的访问次数
```
缺点：需要修改类A的定义，增加了类A的复杂性。并且，如果类A中有外界可访问的数据成员（如z），无法对其访问进行计数！

更好的解决方案：定义一个智能指针类
```cpp
class PtrA  //智能指针类
{		A *p_a; //指向A类对象的普通指针
		int count; //用于对p_a指向的对象进行访问计数
	public:
		PtrA(A *p) 
		{	p_a = p; count = 0; 
		}
		A *operator ->()  //操作符“->”的重载函数，按单目操作符重载
		{	count++;  return p_a; 
		}
		int num_of_a_access() const
		{	return count; 
		}
};
void func(PtrA &p) //p是个PtrA类对象！
{  ... p->f(); ... p->g(); ...
}

A a;// 先声明一个A类对象
PtrA b(&a);  //b为一个智能指针，
		  //它指向了a
b->f(); //访问a的成员f，等价于
           //b.operator->()->f();编译器会编译成这样
func(b); //把b传给func
... b.num_of_a_access() ... 
		//获得func对a的访问次数

```

为了完全模拟普通指针的功能，针对智能指针类，还可以重载“*”（对象间接访问）、“[]”、“+”、“-”、“++”、“--”、“=”等操作符：
```cpp
class PtrA  //智能指针类
{		 A *p_a;
  public:
		PtrA(A *p) { p_a = p; }
		A *operator ->() { return p_a; }
		A& operator *()
		{ return *p_a; 
		}
		A& operator [](int i)
		{ return p_a[i]; 
		}
		......
};

A a[10];
A *p=&a[0]; //普通指针
p->f(); //a[0].f();
(*p).f(); //a[0].f();
p[2].f(); //a[2].f();
...... 

PtrA b=&a[0]; //智能指针
b->f(); //a[0].f();
(*b).f(); //a[0].f();
b[2].f(); //a[2].f();
......

```

### 动态对象空间的自动回收
在C++标准库（基于模板实现）提供了一些智能指针类型，其中包括：
- shared_ptr：能对动态对象进行**引用计数**。
- unique_ptr：实现对动态对象的**独占使用**。
- weak_ptr：与shared_ptr配合使用，防止循环引用。

例如，对于下面的类A：
```cpp
class A
{ int x;
public:	
   A(int i) 
   { x = i; 
	 cout << "constructor: x=" << x << endl;
   }	
   ~A() 
   { cout << "destructor: x=" << x << endl; 
   }	
   void f() { cout << "f: x=" << x << endl; }
};
```
用**智能指针**来管理A类的动态对象：
```cpp
shared_ptr<A> p1(new A(1)); //创建第一个动态指针类p1，指向第一个动态对象，其引用计数为1
p1->f(); //调用第一个动态对象的成员函数f，输出： f: x=1
shared_ptr<A> p2(new A(2)); //创建第二个动态指针类p2，指向第二个动态对象，其引用计数为1
p2->f(); //调用第二个动态对象的成员函数f，输出：f: x=2
p1 = p2; //第一个对象的引用计数减1（变成0），第一个对象自动消亡
              //第二个对象的引用计数加1（变成2）


p2 = nullptr;  //第二个对象的引用计数减1（变成1）
p1->f(); //调用第二个动态对象的成员函数f，输出：f: x=2
p1 = nullptr;  //第二个对象的引用计数减1(变成0)，第二个对象自动消亡


unique_ptr<A> p3(new A(3)); //创建第三个动态对象
unique_ptr<A> p4(new A(4)); //创建第四个动态对象
p3 = p4; //Error，第四个对象被p4独占
p3 = nullptr;  //第三个对象消亡
p4 = nullptr;  //第四个对象消亡
```
