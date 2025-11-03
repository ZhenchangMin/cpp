# Lec18: 多继承
## 必要性
对于下面的两个类A和B：
```cpp
class A
{		int m;
	public:
		void fa();
};
class B
{		int n;
	public:
		void fb();
};
```
如何定义一个类C，它包含**A和B的所有成员**，另外还拥有**新的数据成员**r和**成员函数**fc？

### 用单继承实现
