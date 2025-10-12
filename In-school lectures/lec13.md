# Lec13: 函数对象
## 函数调用操作符()的重载
可以针对某个类重载函数调用操作符，使得相应类的**对象可以当作函数来使用**。
```cpp
class A
{		int value;
	public:
		A(int i) { value = i; }
     int g() { return value; }
		int operator () (int x,int y) //函数调用操作符()的重载函数
		{ return x*y+value; }
};

A a(1); //a是个对象
cout << a.g() <<endl; //把a当对象来用
cout << 10+a(10,20) << endl; //把a当函数来用！
				//a(10,20)等价于：a.operator()(10,20)


void func(A& f) //f是个对象
{ ... 10+f(10,20) ... //把f当函数来使用
                     //f(10,20)等价于：f.operator()(10,20)
}
func(a); //把对象a传给f
```

## 函数对象
函数调用操作符重载主要用于**具有函数性质的对象**（称为：函数对象，functor）。
函数对象通常只有一个操作，可用**函数调用操作符重载函数**来表示该操作。
函数对象除了具有一般函数的行为外，它还可以拥有状态（由对象的数据成员来存储）。

例如，下面定义了一个幂函数类：
```cpp
class PowerFunc
{ int exponent;
public:
    PowerFunc(int n) { exponent=n; }
    double operator ()(double x)
    {   double power=1;
        for (int i=exponent; i>0; i--) power*=x;
        return power;
    }
};

PowerFunc square(2),cube(3);//创建两个函数对象：x^2和x^3，从语法上，是创建了两个对象，但是我们可以当做函数来用
int a;

cout << square(a) << cube(a); //计算a2和a3
```
再例如，下面定义了一个能生成随机数的对象类：
```cpp
class RandNumGen
{	  unsigned int seed; //状态
	public:
   	  RandNumGen(unsigned int i) { seed = i; }
	  unsigned int operator ()() //函数调用操作符重载，前一个（）表示函数调用操作符，后一个（）表示参数列表为空
   	  { seed = (25173*seed+13849)%65536; //修改了状态
	     return seed;
     }
};

RandNumGen rand_num(1); //创建一个函数对象，seed初值为1
... rand_num() ... //调用它表示的函数生成一个随机数
```

### $\lambda$表达式
C++中，$\lambda$ 表达式是通过函数对象来实现的。
例如，对于下面的λ表达式：
```cpp
	[...](int x)->int { ....... }
```
编译器：
首先，隐式定义一个类：
数据成员对应λ表达式中用到的环境变量（[...]），在构造函数中用环境变量对它们进行初始化。
按相应λ表达式的函数功能（即{}中的内容）重载了函数调用操作符。

然后，创建上述类的一个临时对象（设为obj）
最后，在使用上述λ表达式的地方用obj来替代，作用于实参进行函数调用

对于：cout << [...](int x)->int { ....... }(3);
替换成：cout << obj(3);
传给其它函数
对于：f([...](int x)->int { ....... });
替换成：f(obj);
