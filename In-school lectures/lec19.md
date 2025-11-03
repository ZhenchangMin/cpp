# Lec19: 聚合与组合
## 继承不是类代码复用的唯一方式
有些代码复用不宜用继承来实现,继承除了支持代码复用外，还体现了类之间在概念上的**一般与特殊关系**（is-a-kind-of）
并且，继承与封装存在矛盾，而且继承加大了类之间的耦合度，不利于程序的维护

类之间除了继承关系外，还存在一种**整体与部分的关系**（is-a-part-of），即一个类的对象包含了另一个类的对象。
类之间的整体与部分的关系可以分为**聚合**和**组合**

## 聚合
在聚合关系中，被包含的对象与包含它的对象**独立**创建和消亡，被包含的对象可以脱离包含它的对象**独立存在**。
聚合类的成员对象一般是采用**对象指针**表示，用于指向被包含的成员对象。
被包含的成员对象是**在外部创建**，然后加入到聚合类对象中。

```cpp
class A { ...... };
class B //B与A是聚合关系
{ A *pm; //指向成员对象
public:
   B(A *p) { pm = p; } //成员对象在聚合类对象外部创建，然后传入
   ~B() { pm = NULL; } //传进来的成员对象不再是聚合类对象的成员
   ......
};
......
A *pa=new A; //创建一个A类对象
B *pb=new B(pa); //创建一个聚合类对象，其成员对象是pa指向的对象
......
delete pb; //聚合类对象消亡了，其成员对象并没有消亡
...... // pa指向的对象还可以用在其它地方
delete pa; //聚合类对象原来的成员对象消亡
```
### 例：公司由一批员工组成
```cpp
class Employee //职员类
{ string name; 
   int salary;
 public:
   Employee(const char *s, int n=0):name(s) 
   {	salary = n; }
   void set_salary(int n) { salary = n; }
   int get_salary() const { return salary; }
   ......
};

const int MAX_NUM_OF_EMPS=1000;
class Company //公司类
{ String name; 
   Employee *group[MAX_NUM_OF_EMPS]; //职员数组
   int num_of_emps; //职员人数
 public:
   Company(const char *s):name(s) 
   { num_of_emps = 0; }
   ~Company() { num_of_emps = 0; }
   bool add_employee(Employee *e);
   bool remove_employee(Employee *e);
   int get_num_of_emps() { return num_of_emps; }
   ......
};
//创建两个公司类对象
Company c1("Company_1"),c2("Company_2");
//创建两个职员对象
Employee e1("Jack",1000),e2("Jane",2000);

//职员Jack加入公司Company_1
c1.add_employee(&e1); 
//职员Jane加入公司Company_1
c1.add_employee(&e2); 

//职员Jack从公司Company_1离职
c1.remove_employee(&e1);

//职员Jack加入公司Company_2
c2.add_employee(&e1); 
......
```

## 组合
在组合关系中，被包含的对象**随包含它的对象创建和消亡**，被包含的对象不能脱离包含它的对象独立存在。
组合类的成员对象一般**直接是对象**，有时也可以采用**对象指针**表示。但不管是什么表示形式，成员对象一定是在组合类对象**内部创建**并随着组合类对象的消亡而消亡。

可以通过成员对象实现组合
```cpp
class A
{ ......
};
class C //C与A是组合关系
{ A a; //成员对象
public:
  ......
};
......
C *pc=new C; //创建一个组合类对象，其成员对象在组合类对象内部创建
.....
delete pc; //组合类对象与其成员对象都消亡了
```

## 继承与聚合/组合的比较
继承的代码复用功能常常可以用组合来实现
![1762157887892](image/lec19/1762157887892.png)
继承更容易实现子类型，具有聚合/组合关系的两个类不具有子类型关系。