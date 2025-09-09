# Lec2 数据抽象与封装概述
## 抽象与封装
主要用于驾驭程序的**复杂度**和提高程序的**安全性**，便于**大型程序**的设计、理解与维护。
抽象：该程序实体**外部**可观察到的行为，使用者不考虑该程序实体的内部是如何实现的。（复杂度控制）
封装：把该程序实体**内部**的具体实现细节对使用者**隐藏起来**，只对外提供一个接口。（信息保护）
主要的程序抽象与封装机制包括：
- 过程抽象与封装
- 数据抽象与封装

### 过程抽象与封装
实现过程抽象与封装的程序实体成为**子程序**
在C/C++种，子程序用**函数**表示

#### 过程抽象
用一个名字代表一段程序代码，使用者只需要知道这个名字，就可以调用这段代码。

#### 过程封装
把命名代码的具体实现隐藏起来。

### 数据抽象与封装
能够实现更好的数据保护

#### 数据抽象
只描述对数据能够实施的操作和操作之间的关系，不需要知道数据的表示形式。

#### 数据封装
把数据和对数据的操作封装在一起，数据的具体表示被隐藏，对数据的访问（使用）只能通过定义的**对外接口**进行。

### 例：“栈”数据的表示与操作
后进先出(Last In First Out，LIFO)
#### 栈的实现--非数据抽象与封装途径
```cpp
const int STACK_SIZE=100;
struct Stack
{int buffer[STACK_SIZE]; //存放栈元素
  int top; //栈顶位置
};
```
##### 操作方式一：直接操作栈数据
```cpp
Stack st; //定义栈数据
st.top = -1; //对st进行初始化
//把12放进栈
if (st.top == STACK_SIZE-1)   
{ cout << "Stack is overflow.\n"; exit(-1); }
st.top++; 
st.buffer[st.top] = 12; 
......
//把栈顶元素退栈并存入变量x
if (st.top == -1)    
{ cout << "Stack is empty.\n"; exit(-1); }
int x = st.buffer[st.top]; 
st.top--;
```
**存在的问题：**
- 操作必须知道数据的具体表示形式，修改表示形式会影响操作
- 麻烦并易产生误操作，因此不安全，如忘记初始化top或者把--和++写反

##### 操作方式二：通过过程抽象与封装来操作栈数据
```cpp
void init(Stack &s)
{   s.top = -1;
}
void push(Stack &s, int e)
{	if (s.top == STACK_SIZE-1) 
	{	cout << “Stack is overflow.\n”;
		exit(-1);
	}
	else
	{	s.top++; s.buffer[s.top] = e;
		return;
	}
}
void pop(Stack &s, int &e)
{	if (s.top == -1) 
	{	cout <<“Stack is empty.\n”;
		exit(-1);
	}
  	else 
	{	 e = s.buffer[s.top]; s.top--;
		return;
	}
}
```
**存在的问题：**
- 数据定义与操作的定义是**分开**的，二者之间没有必然的联系，仅仅依靠操作的**参数类型**把二者关联起来。
比如，我引入一个新的函数f,用f也能操作栈st，从而可能破坏st的某些性质。
```cpp
void f(Stack &s) { ...... }
f(st); //操作st之后，st可能不再是一个“栈”了！
```
- 数据表示仍然是**公开**的，无法防止使用者直接操作栈数据，因此也会面临直接操作栈数据所面临的问题。
- 忘了调用初始化操作。

#### “栈”的实现--数据抽象与封装途径
栈数据类型：把数据表示和操作作为一个整体
```cpp
const int STACK_SIZE=100;
class Stack
{	 
public: //对外的接口（外部可使用的内容）
	Stack();
   void push(int e);
   void pop(int &e);
private: //隐藏的内容（外部不可使用）
   int buffer[STACK_SIZE];
	int top;
};
Stack::Stack()
{
    top = -1;
}
void Stack::push(int e)
{ 	if (top == STACK_SIZE-1) 
	{	cout << “Stack is overflow.\n”;
		exit(-1);
	}
	else
	{	top++;  buffer[top] = e;
		return;
	}
}
void Stack::pop(int &e)
{ 	if (top == -1) 
	{	cout << “Stack is empty.\n”;
		exit(-1);
	}
	else 
	{	e = buffer[top]; top--;
		return;
	}
}
```
使用栈类型数据:
```cpp
Stack st;  //会自动地去调用st.Stack()对st进行初始化。
int x;
st.push(12);  //把12放进栈st
......
st.pop(x);  //把栈顶元素退栈并存入变量x
......
st.top = -1;  //Error，不能直接操作st！
st.top++;  //Error ，不能直接操作st！
st.buffer[st.top] = 12;  //Error ，不能直接操作st！
st.f(); //Error，f不属于能对st进行的操作！
```

#### 栈的另一种实现：使用链表
```cpp
class Stack
{	public: //对外接口没变！
		Stack();
		void push(int e);
		void pop(int &e);
	private: //数据表示改成了链表
		struct Node
		{ int content;
		   Node *next;
		} *top; 
};
Stack::Stack()
{ top = NULL; 
}
void Stack::push(int e)
{	Node *p=new Node;
	if (p == NULL)
	{	cout << "Stack is overflow.\n";
		exit(-1);
	}
	else
	{	p->content = e;
		p->next = top;	top = p;
		return;
	}
}
void Stack::pop(int &e)
{	if (top == NULL) 
	{	cout << "Stack is empty.\n";
		exit(-1);
	}
	else 
	{	Node *p=top;
		top = top->next;
		e = p->content;
		delete p;
		return;
	}
}
```
改变栈的数据表示对使用者没有任何影响，原来使用栈的代码不需要做任何修改。