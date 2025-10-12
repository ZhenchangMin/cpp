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
