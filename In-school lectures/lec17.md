# Lec17: 纯虚函数与抽象类
为什么需要抽象类？
假如说我要表示一组图形，有矩形有线段有圆，我想用一个数组，有的元素是线段有的元素是圆，就可以用抽象类。

## 纯虚函数
纯虚函数是**没给出实现的虚函数**，函数体用“=0”表示
```cpp
class A
{	......
	public:
		virtual int f()=0; //纯虚函数
	......
};
```
纯虚函数要在派生类中给出实现

## 抽象类
包含纯虚函数的类称为**抽象类**。
```cpp
class A //抽象类
{	  ......
	public:
		virtual int f()=0; //纯虚函数
	......
};
```
至少要包含一个纯虚函数
抽象类不能用于创建对象
抽象类的作用：
- 对不同类型的**公共特征**进行抽象描述。除了纯虚函数外，它可以包含普通虚函数和非虚函数。
- 为同一个类型的**不同实现**提供一个抽象描述（**接口**）。它只包含纯虚函数。


### 例：实现图形的基本框架
比如在上面那个图形的例子中：
```cpp
class Figure //抽象基类
{  int id;
public:
	Figure(int i) { id = i; }
	//派生类必须实现的功能	
	virtual void draw() const=0; 
	virtual void input_data()=0; 
	//派生类可以自己实现的功能
	virtual double area() const { return 0;}
	//派生类不能自己实现的功能
	int get_id() { return id; }
	......
};
```
下面实现矩形类：
```cpp
class Rectangle: public Figure // 继承
{		double left,top,right,bottom;
	public:
		void draw() const
		{	...... //画矩形
		}
		void input_data()
		{	cout << "请输入矩形的左上角和右下角坐标 (x1,y1,x2,y2) ：";
			cin >> left >> top >> right >> bottom;
		}
		double area() const //派生类自己实现
	  { return (bottom-top)*(right-left); 
     }
     ......
};
```
圆形同理
```cpp
const double PI=3.1416;
class Circle: public Figure
{		double x,y,r;
	public:
		void draw() const
		{	...... //画圆
		}
		void input_data()
		{	cout << "请输入圆的圆心坐标和半径 (x,y,r) ：";
			cin >> x >> y >> r;
		}
		double area() const //派生类自己实现
     { return r*r*PI; }
     ......
};
```
还有线段
```cpp
class Line: public Figure
{		double x1,y1,x2,y2;
	public:
		void draw() const
		{	...... //画线
		}
		void input_data()
		{	cout << "请输入线段的起点和终点坐标 (x1,y1,x2,y2) ：";
			cin >> x1 >> y1 >> x2 >> y2;
		}
	  //派生类没有自己实现area，用基类的，因为线段不存在面积这一说
     ......
};
```

一批图形的输入：
```cpp
const int MAX_NUM_OF_FIGURES=100;
Figure *figures[MAX_NUM_OF_FIGURES];
int count=0;

for (count=0; count<MAX_NUM_OF_FIGURES;	count++)
{	int shape;
	do
	{	cout << "请输入图形的种类(0：线段，1：矩形，2：圆，-1：结束)：";
		cin >> shape;
	} while (shape < -1 || shape > 2);
	if (shape == -1) break;
	switch (shape)
	{	case 0: //线
			figures[count] = new Line(count);	break;
		case 1: //矩形
			figures[count] = new Rectangle(count); break;
		case 2: //圆
			figures[count] = new Circle(count); break;
 	}
	figures[count]->input_data(); //动态绑定到相应类的input_data并且调用
}

for (int i=0; i<count; i++)	
		figures[i]->draw();  //通过动态绑定
						//调用相应类的draw
//输出图形
```
即使今后增加了图形的种类，上述代码（属于高层代码）也不需要改动，只要增加相应的类（属于低层代码）就行。
这就是多态的好处，便于高层代码复用。

### 例：实现抽象数据类型Stack
抽象数据类型ADT，只考虑类型的抽象性质，不考虑该类型的内部实现。
从抽象数据类型的角度来讲，栈类型是由若干**具有线性关系的元素构成**，它包含两个操作`push`和`pop`

C++的**类**不是抽象数据类型，它是抽象数据类型的**实现**！
对于一个用数组实现的栈类`ArrayStack`和一个用链表实现的栈类`LinkedStack`：
虽然从抽象数据类型的角度看，它们应该是相同的类型，但由于它们是用不同的类实现的，因此，在C++中它们是不同的类型！

对于需要一个栈对象的函数f：
void f(T& st); 
如果要求它既可以接受ArrayStack类的对象，也可以接受LinkedStack类的对象，
那么，它的参数T的类型应该怎么表示？
用一个抽象基类Stack作为接口
```cpp
class Stack
{	public:
		virtual void push(int i)=0;
		virtual void pop(int& i)=0;
};
```

具体实现：
```cpp
class ArrayStack: public Stack
{		int elements[100],top;
  public:
   		ArrayStack() { top = -1; }
		void push(int i) { ...... }
		void pop(int& i) { ...... }
};
class LinkedStack: public Stack
{		struct Node
		{	int content;
			Node *next;
		} *first;
	public:
		LinkedStack() { first = NULL; }
		void push(int i) { ...... }
		void pop(int& i) { ...... }
};
void func(Stack &st)
{	......
	st.push(...);  //将根据st引用的对象类来确定push的归属
	......
	st.pop(...);  //将根据st引用的对象类来确定pop的归属
	......
}
int main()
{	ArrayStack st1;
	LinkedStack st2;
	func(st1);  //OK
	func(st2);  //OK
	......
}
```

### 用抽象类实现类的真正抽象作用
由于在C++中使用某个类时必须要见到该类的定义，因此，使用者能够见到该类的一些实现细节（如：非public成员），这样会使得类的抽象和封装作用大打折扣。
比如：
```cpp
//A.h （类A的定义，公开的）
class A
{	int i,j;
  public:
	A();
	A(int x,int y);
	void f(int x);
    ......
};
//A.cpp （类A的实现，不公开）
#include "A.h"
void A::A() { ...... }
void A::A(int x,int y) { ...... }
void A::f(int x) { ...... }

//B.cpp （类A的某个使用者）
#include "A.h"
void func(A *p)
{	p->f(2); //Ok
	p->i = 1; //Error
	p->j = 2; //Error
    //可绕过对象类的访问控制！看到了是i和j是int型变量
	*((int *)p) = 1; //Ok，访问p所指向的对象的成员i
	*((int *)p+1) = 2; //Ok，访问p所指向的对象的成员j
}
```
如何防止这种情况？
用抽象类，给类A提供一个抽象基类作为对外接口
```cpp
//I_A.h （类A的对外接口，公开）
class I_A
{ public:
   	  virtual void f(int)=0;
      ......
};
//A.h （类A的定义，部分公开）
#include "I_A.h"
class A: public I_A
{   int i,j;
   public:
A();
A(int x,int y);
void f(int x);
......
};
//A.cpp （类A的实现，不公开）
#include "A.h"
void A::A() { ...... }
void A::A(int x,int y) { ...... }
void A::f(int x) { ...... }
......
//B.cpp （类A的某个使用者）
#include "I_A.h"
void func(I_A *p)
{	p->f(2);  //Ok

	*((int *)p) = 1;  //这里不知道p所指向的对象有哪些数据成员，
		   //因此，该操作不知道它访问的是什么数据成员
}
```