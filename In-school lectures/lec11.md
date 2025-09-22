# Lec11: 操作符重载
## 操作符重载概述
C++语言没有提供诸如复数、分数、集合、矩阵、多项式等数学类型，程序中可以通过分别定义一些类来实现它们。
例如，下面定义了一个复数类来实现复数类型的基本功能
```cpp
class Complex	//复数类定义
{public:
	 Complex(double r=0.0,double i=0.0)      
     { real=r; imag=i; 
     } 
     void display() const
     { cout << real << '+' << imag << 'i';
     } 
    ...... //复数的操作
  private:	
	 double real;
	 double imag;
};	
Complex a(1.0,2.0),b(3.0,4.0);
a.display(); b.display();
```
如何实现复数的相加操作？
要么在类中定义一个add函数，要么定义一个全局函数并且声明为友元

但是这样不符合数学上的习惯$c=a+b$，所以需要重载操作符$+$
C++只针对基本数据类型以及指针类型定义了+操作，对自定义类型的对象，+是无定义的，但C++允许对已有的操作符进行**重载**（定义新的含义），使得用它们能对自定义类型（类）的对象进行操作。

### 操作符重载的实现途径
操作符重载可通过定义一个函数名为“operator #”（ “#”代表某个可重载的操作符）的函数来实现，该函数可以作为：
- 一个类的成员函数。
- 一个全局（友元）函数。

```cpp
class Complex
{	public:
		Complex operator + (const Complex& x) const//参数是一个Complex对象的引用，返回一个Complex对象
		{	Complex temp;
			temp.real = real+x.real;
			temp.imag = imag+x.imag;
			return temp;
		}
    ......
};
……
Complex a(1.0,2.0),b(3.0,4.0),c;
c = a + b; //按 a.operator+(b) 实现
```
这个是以成员函数实现的重载，也可以以全局函数实现：
```cpp
class Complex
{	......
	friend Complex operator + (const Complex& c1, 
					           const Complex& c2);//要声明成friend，因为要访问private成员
};
Complex operator + (const Complex& c1, 
				        const Complex& c2)
{	Complex temp;
	temp.real = c1.real + c2.real;
	temp.imag = c1.imag + c2.imag;
	return temp;
}
……
Complex a(1.0,2.0),b(3.0,4.0),c;
c = a + b; //按 operator+(a,b) 实现
```
### 操作符重载的基本原则
只能重载C++语言中**已有的操作符**，不可臆造新的操作符。
可以重载C++中除下列操作符外的所有操作符：“.”， “.*”，“?:”，“::”，“sizeof”
需要遵循已有操作符的**语法**：不能改变**操作数的个数**，并且原操作符的**优先级和结合性**不变。
尽量遵循已有操作符原来的语义：语言本身没有对此做任何规定，使用者自己把握

作为全局函数重载操作符时，至少要有一个参数为类、结构、枚举或它们的引用类型，并且该全局函数往往要说明成相应类、结构、枚举的**友元**，因为基本数据类型语言编译器已经重载好了。成员函数不需要，因为成员函数有一个隐藏的this指针。

## 双目操作符重载
### 作为**成员函数**重载
只需要提供一个参数，它对应第二个操作数（第一个操作数则由隐藏的参数this给出）。
```cpp
class Complex
{		double real, imag;
	public:
		......//判断复数的等于和不等于
		bool operator ==(const Complex& x) const
		{	return (real == x.real) && (imag == x.imag);
		}
		bool operator !=(const Complex& x) const
		{	return (real != x.real) || (imag != x.imag);
		}
        //最好写成下面这样，因为如果==的逻辑又改变了，只需要改一个函数就行
        bool operator !=(const Complex& x) const
		{	return !(*this == x);
		}
};
......
Complex c1,c2;
...... 
if (c1 == c2) //或 if (c1 != c2)
```
### 作为**全局函数**重载
需要提供两个参数，其中至少应该有一个是类、结构、枚举或它们的引用类型。
```cpp
class Complex
{		double real, imag;
	public:
		Complex() { real = 0; imag = 0; }
		Complex(double r, double i) { real = r; imag = i; }
		......
        //重载操作符+，使其能够实现实数与复数的混合运算。 
	friend Complex operator + (const Complex& c1, 
							    const Complex& c2);
	friend Complex operator + (const Complex& c, 
 							    double d);
	friend Complex operator + (double d, 
							    const Complex& c);
};

Complex operator + (const Complex& c1, 
				      const Complex& c2)
{	return Complex(c1.real+c2.real,c1.imag+c2.imag);
}
Complex operator + (const Complex& c, double d)
{	return Complex(c.real+d,c.imag);
}
Complex operator + (double d, const Complex& c)
//“实数+复数”只能作为全局函数重载。为什么？因为如果作为成员函数重载，
//则第一个操作数必须是Complex对象，而不是double类型的实数。
{	return Complex(d+c.real,c.imag);
}
......
Complex a(1,2),b(3,4),c1,c2,c3;
c1 = a + b;
c2 = b + 21.5;
c3 = 10.2 + a;
```

## 下标访问操作符“[]”的重载 
“[]”是一个双目操作符，第一个操作数为一个数组或指针，第二个操作数为一个整型数，操作结果为数组元素

对于一个由具有**线性关系的成员**所构成的对象，可通过重载下标访问操作符“[]”来实现**对其成员的访问**。
```cpp
class String
{	 int len;
	 char *str; //指向一个存储字符串的内存空间
    public:
 		......
		char &operator [](int i) {	return str[i]; }
		char operator [](int i) const { return str[i];} //用于常量对象
};
......
String s("abcd");
cout << s[0];  //输出：a
s[0] = 'A';
cout << s[0];  //输出：A
```
```cpp
class Vector  //向量类
{	   int *p_data;
	   int num;
	public:
		......
		int& operator[](int i) //访问向量第i个元素。
		{	return p_data[i];
		}
};
......
Vector v(10);
v[2] = 23;
cout << v[2]; //输出：23
```

如果要访问矩阵的元素，不能直接重载`[][]`，怎么办？
重载`[]`运算符，返回一个向量类型，再把向量的`[]`也重载了，就可以用m[2,3]访问m的第二行第三列。

## 单目操作符重载
### 作为成员函数重载
对复数取负
```cpp
class Complex
{	......
	public:
		......
		Complex operator -() const
		{	return Complex(-real, -imag);
		}
};
......
Complex a(1,2),b;
b = -a;  //把a的负数赋值给b
```

### 作为全局函数重载
判断复数是否为0
```cpp
class Complex
{	......
	public:
		......
		friend bool operator !(const Complex &c);
};
bool operator !(const Complex &c)
{	return (c.real == 0.0) && (c.imag == 0.0);
}
......
Complex a(1,2);
......
if (!a) //a为0时true
```
### 特殊的单目操作符++和--
他们的操作数必须是**左值**，不能是临时单元中的右值。
而前缀++和--返回的是操作数的引用，后缀++和--返回的是操作数的副本，副本是右值存在于一个临时单元之中。
所以++(++x)和(++x)++是可以的，但是(x++)++和++(x++)是错误的。

区分操作数和操作结果，就可以很容易理解前缀和后缀的区别。

## 自定义类型转换操作符
可以通过操作符重载来实现**从一个类到其它类型的转换**。
```cpp
class A
{  int x,y;
  public:
   ......
   operator int() //用于把A类型的对象转换成int类型
   { return x+y; 
   }
};
...…
A a;
int i=1;
... (i + a) ... //将调用类型转换操作符重载函数operator int()
			   //把对象a隐式转换成int型数据。
```
另外，类中带一个参数的构造函数可以作为类型转换来用：**从该参数的类型到该类的转换**。
```cpp
class Complex
{		double real, imag;
	public:
		Complex() { real = 0; imag = 0; }
		Complex(double r)  {	real = r; imag = 0; }//1.7通过这个构造函数转换成了一个复数对象
		Complex(double r, double i) { real = r; imag = i; }
		......
  friend Complex operator + (const Complex& x, const Complex& y);
}; //只针对Complex重载了“复数+复数”操作
......
Complex c(1,2);
... (c + 1.7) ...  //1.7隐式转换成一个复数对象Complex(1.7)
... (2.5 + c) ...  //2.5隐式转换成一个复数对象Complex(2.5)
```

### 歧义问题
```cpp
class A
{		int x,y;
	public:
		A() { x = 0;  y = 0; }
		A(int i) { x = i; y = 0; }
      A(int i,int j) { x = i;  y = j; }
		operator int() { return x+y; }
	friend A operator +(const A &a1, const A &a2);
};
......
A a;
int i=1;
... (a + i) ...  //是把a转换成int呢，还是把i转换成A呢？
```
对于这样的情况，可以用显式类型转换来解决：
```cpp
... ((int)a + i) ... //把a转换成int
... (a + (A)i) ...  //把i转换成A
```
也可以通过给A类的构造函数A(int i)加上一个修饰符`explicit`，禁止把它用于隐式类型转换：
```cpp
class A
{		int x,y;
	public:
		A() { x = 0;  y = 0; }
		explicit A(int i) { x = i; y = 0; }
      A(int i,int j) { x = i;  y = j; }
		operator int() { return x+y; }
	friend A operator +(const A &a1, const A &a2);
};
```
当然，也可以给int类型转换操作符重载函数加一个`explicit`，禁止其用作隐式类型转换，此处不再赘述。