# Lec23: 基于STL的编程
## 什么是STL
C++除了保留了C的标准库外，另外还提供了一个**基于模板实现的标准模板库**（Standard Template Library，简称STL）
- 实现了一些面向序列数据的表示及常用的操作。
- 支持了一种抽象的编程模式，该模式隐藏了一些低级的程序元素，如数组、链表、循环等。

STL包含以下几个组件：
- 容器（Containers）：用于存储序列化的数据元素
- 迭代器（Iterators）：属于一种**智能指针**，它们指向容器中的数据元素，用于对容器中的数据元素进行遍历和访问
- 算法（Algorithms）：用于对容器中的数据元素进行一些常用的操作
- ......

基于STL编程的例子：从键盘输入一批正整数，然后对它们求最大数、求和、排序、输出
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int main()
{	vector<int> v; //创建容器对象v，元素类型为int
	int x;
	cin >> x;
	while (x > 0) //生成容器v中的元素
	{	v.push_back(x); //往容器v中增加一个元素
		cin >> x;
	}
//利用算法max_element计算并输出容器v中的最大元素
	cout << "Max = " << *max_element(v.begin(),v.end()) 
		 << endl;
   //利用算法accumulate计算并输出容器v中所有元素的和
	cout << "Sum = " << accumulate(v.begin(),v.end(),0) 
		 << endl;
	//利用算法sort对容器v中的元素进行排序
	sort(v.begin(),v.end()); 
	//利用算法for_each输出排序结果
	cout << "Sorted result is:\n";
	for_each(v.begin(),v.end(), [](int x) { cout << ' ' << x;});
	cout << '\n';
	return 0;
}
```

## 容器
容器是由**同类型元素构成的、长度可变的元素序列**。
容器是用类模板来实现的，模板的参数包含了容器中元素的类型。
STL中提供了很多种容器，适合于不同的应用场合。

### 主要容器：
- vector<>
用于需要**快速定位**（访问）任意位置上的元素以及主要在元素序列的尾部增加/删除元素的场合。
在头文件vector中定义，用**动态数组**实现

- list<>
用于经常在元素序列中**任意位置上**插入/删除元素的场合。
在头文件list中定义，用**双向链表**实现

- deque<>
用于需要在元素序列的**头部和尾部**增加/删除元素以及需要**快速定位**的场合。
在头文件deque中定义，用**分段的连续空间结构**实现

- stack<>和queue<>
用于需要按照**先进后出**（FIFO）或**先进先出**（FILO）的顺序访问元素的场合。
在头文件stack和queue中定义，分别用**数组**和**链表**实现。

- priority_queue<>
它与queue的操作类似，不同之处在于：
每次增加/删除元素之后，它将对元素位置进行调整，使得头部元素总是最大的。也就是说，每次删除的总是最大（**优先级最高**）的元素。
在头文件queue中定义，基于deque或vector来实现。

- map<>和multimap<>
用于需要根据**关键字**来访问元素的场合。
容器中每个元素由**关键字和值**构成（它们属于一个pair结构类型，该结构有两个成员：first和second，first对应关键字，second对应值），元素是根据其关键字**排序**的。
对于map，不同元素的关键字不能相同；对于multimap，不同元素的关键字可以相同。
在头文件map中定义，用**红黑树**实现

- set<>和multiset<>
它们分别是map和multimap的特例，每个元素**只有关键字而没有值**，或者说，关键字与值合一了。
在头文件set中定义。

- basic_string<>
与vector类似，不同之处在于其元素为字符类型，并提供了一系列与字符串相关的操作。
string和wstring分别是它的两个实例：
basic_string<char>
basic_string<wchar_t>
在头文件string中定义。

### 容器的基本操作
- 往容器中增加元素
- 从容器中删除元素
- 获取容器中指定位置的元素
- 在容器中查找元素

如果容器的元素类型是一个类，则针对该类可能需要：
- 自定义拷贝构造函数和赋值操作符重载函数
容器内部进行的一些操作中可能会创建新的元素（对象的拷贝构造）或进行元素间的赋值（对象赋值）。
- 重载小于操作符（<）
容器内部进行的一些操作中可能要对元素进行“小于”比较运算。

## 迭代器
迭代器（iterator）属于一种**智能指针**，它们指向容器中的元素，用于对容器中的元素进行访问和遍历。
在STL中，迭代器是作为类模板来实现的（在头文件iterator中定义），它们可分为以下几种类型：
- 输出迭代器（output iterator，OouIt）
只能**修改**它所指向的容器元素,间接访问（*）,++（只能向后遍历）

- 输入迭代器（input iterator，InIt）
只能**读取**它所指向的容器元素,间接访问（*）和元素成员间接访问（->）,++、==、!=。

- 前向迭代器（forward iterator，FwdIt）
可以**读取/修改**它所指向的容器元素，元素间接访问（*）和元素成员间接访问（->），++、==、!=操作

- 双向迭代器（bidirectional iterator，BidIt）
可以**读取/修改**它所指向的容器元素，元素间接访问（*）和元素成员间接访问（->），++、**--**、==、!=操作

- 随机访问迭代器（random access iterator，RanIt）
可以读取/修改它所指向的容器元素，元素间接访问（*）、元素成员间接访问（->）和下标访问元素（[]），++、--、+、-、+=、-=、==、!=、<、>、<=、>=
注意：指向数组元素的**普通指针**可以看成是随机访问迭代器

由于不同的容器采用了不同的内部实现，因此，**不同的容器的迭代器的类型会有所不同**
- 对于vector、deque以及basic_string容器类，与它们关联的迭代器类型为随机访问迭代器（RanIt）
- 对于list、map/multimap以及set/multiset容器类，与它们关联的迭代器类型为双向迭代器（BidIt）。
- 对于queue、stack和priority_queue容器类，不支持迭代器！

可通过容器类的成员函数`begin`和`end`等获得容器的首尾迭代器。

## 算法
在STL中，除了用容器类自身提供的成员函数来操作容器元素外，还提供了一系列通用的对容器中元素进行操作的全局函数，称为算法（algorithm）。
算法是用函数模板实现的，除了算术算法在头文件`numeric`中定义外，其它算法都在头文件`algorithm`中定义。

在STL中，一般不是把容器传给算法，而是把容器的某些**迭代器**传给它们，在算法中通过迭代器来访问和遍历相应容器中的元素。
这样做的好处是提高了算法的通用性，只要容器的迭代器类型是符合要求的，就可以使用该算法，而不用针对不同的容器类重新实现算法。

一个算法能接收的迭代器的类型是通过**算法模板参数的名字**来体现的。例如：
```cpp
template <class InIt, class OutIt>
OutIt copy(InIt src_first, InIt src_last, 
                OutIt dst_first)
{ ...... }
```
src_first和src_last的类型是输入迭代器，算法中只读取它们指向的元素。
dst_first的类型是输出迭代器，算法中可以修改它指向的元素。
以上参数可以接受与之相容的迭代器。

用算法对容器中的元素进行操作时，大都需要用两个迭代器来指出要操作的元素的**范围**
```cpp
void sort(RanIt first, RanIt last);

vector<int> v;
...... //往容器中放了元素
sort(v.begin(),v.end()); //对v中的所有元素进行排序
```

有些算法可以让使用者提供一个函数或函数对象来作为**自定义操作条件**（或称为谓词），其参数类型为相应容器的**元素类型**，**返回值类型为bool**。
自定义操作条件可分为：
一元“谓词”（记为：Pred）：需要一个元素作为参数
二元“谓词”（记为：BinPred）：需要两个元素作为参数
例如，下面的“统计”算法需要一个一元谓词作为统计的条件：
```cpp
size_t count_if(InIt first, InIt last, Pred cond); // 统计[first,last)范围内满足条件cond的元素个数的算法

bool f(int x) { return x > 0; }
vector<int> v;
...... //往容器中放了元素
cout<<count_if(v.begin(),v.end(),f); //统计v中正数的个数
```

再例如，下面 “排序”算法的第二个重载需要一个二元谓词作为排序条件：
```cpp
void sort(RanIt first, RanIt last); //按“<”排序
void sort(RanIt first, RanIt last, BinPred comp); 
                             //按comp返回true规定的次序

vector<int> v;
...... //往容器中放了元素
//从小到大排序
sort(v.begin(),v.end()); 
//从大到小排序
bool greater(int x1, int x2) { return x1>x2; }
sort(v.begin(),v.end(),greater); 
```


有些算法可以让使用者提供一个函数或函数对象作为自定义操作，其参数和返回值类型由相应的算法决定。
自定义操作可分为：
一元操作（记为：Op或Fun），需要一个参数
二元操作（记为：BinOp或BinFun），需要两个参数
例如，下面的“元素遍历”算法需要提供一个一元操作，其参数为容器的元素类型，返回值为任意类型：
```cpp
Fun for_each(InIt first, InIt last, Fun f); // 对[first,last)范围内的每个元素去调用函数f进行操作，返回值为Fun

void display(int x) { cout << ' ' << x; }
vector<int> v;
...... //往容器中放了元素
for_each(v.begin(),v.end(),display); //对v中的每个元素去调用
					//函数display进行操作
```

