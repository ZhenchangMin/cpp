# Lec9: 友元

## 友元

类中定义的数据成员在外界不能直接访问，需要通过类的public成员函数来访问。
但是在有些情况下，这种访问方式**效率不高**。

为了提高访问效率，可以指定某些与一个类**密切相关**，又**不适合作为该类的一个成员**的程序实体，称为**友元**，可以直接访问该类的**非public数据成员**。

友元需要在类中用**friend**关键字来声明，他们可以是：

- 其他类的所有成员函数
- 其他类的某个成员函数
- 全局函数

```cpp
class A
{	......
	friend void func();  //全局函数func可访问x
	friend class B;  //类B的所有成员函数可访问x
	friend void C::f();  //类C的成员函数f可访问x
private:
   int x;
}; 
```

对友元的说明：

- 友元不是本类的成员
- 友元具有不对称性
- 友元不具有传递性

例子：实现矩阵与向量的乘法

```cpp
class Matrix  //矩阵类
{		int *p_data;  //表示矩阵数据
		int row,col;  //表示矩阵的行数和列数
	public:
		Matrix(int r, int c) //构造函数
		{	if (r <= 0 || c <= 0)
			{	cerr << "矩阵尺寸不合法！\n";//一般情况下等同于cout，用输入输出重定向的时候，两者有区别，cerr仍然会在显示器输出，而cout会输出成文本txt
				exit(-1);
			}
			row = r;	col = c;
			p_data = new int[row*col]; //动态分配内存
			for (int i=0; i<row*col; i++) p_data[i] = 0;
		}
		~Matrix() 	{ delete []p_data; }  //析构函数，要归还动态分配的内存

        int &element(int i, int j) //访问矩阵元素。为什么是引用类型？可以直接修改矩阵元素
		{	if (i < 0 || i >= row || j < 0 || j >= col)
			{	cerr << "矩阵下标越界\n";
				exit(-1);
			}
			return *(p_data+i*col+j); //通过解引用返回
		}
        int element(int i, int j) const //重载的特殊情况！虽然参数个数和类型都没变，但是因为是const，允许重载
                       //访问矩阵元素（为常量矩阵对象而提供）。
		{	if (i < 0 || i >= row || j < 0 || j >= col)
			{	cerr << "矩阵下标越界\n";
				exit(-1);
			}
			return *(p_data+i*col+j);
		}
        int dimension_row() const //获得矩阵的行数。
		{	return row;
		}
	    int dimension_column() const //获得矩阵的列数。
		{	return col;
		}
	    void input_data() //输入矩阵数据
		{	for (int i=0; i<row*col; i++)	cin >> p_data[i];
		}
	    void display() const //显示矩阵元素。
		{	int *p=p_data; 
			for (int i=0; i<row; i++)
			{	for (int j=0; j<col; j++)
				{ cout << *p << ' ';
				   p++;
				}
				cout << endl;
			}
		}
};


class Vector  //向量类
{		int *p_data;
		int num;
	public:
		Vector(int n)
		{	if (n <= 0) 
			{	cerr << "向量尺寸不合法！\n"; 
				exit(-1);
			}
			num = n;
			p_data = new int[num];
			for (int i=0; i<num; i++) p_data[i] = 0;
		}
		~Vector()
		{	delete []p_data;
		}

        int &element(int i) //访问向量元素。
		{	if (i < 0 || i >= num)
			{	cerr << "向量下标越界！\n";
				exit(-1);
			}
			return p_data[i];
		}
		int element(int i) const 
                     //访问向量元素（为常量对象而提供）。
		{	if (i < 0 || i >= num)
			{	cerr << "向量下标越界！\n";
				exit(-1);
			}
			return p_data[i];
		}
        int dimension() const //返回向量的尺寸。
		{	return num;
		}
		void input_data() //输入向量数据
		{	for (int i=0; i<num; i++)
		 		cin >> p_data[i];
		}
		void display() const //显示向量元素。
		{	int *p=p_data;
			for (int i=0; i<num; i++,p++)
				cout << *p << ' ';
			cout << endl;
		}
};
```

现在，有了这两个类，就可以创建对象。

```cpp
    int row,column; //矩阵的行数、列数
	cin >> row >> column;
	Matrix m(row,column); //创建矩阵对象m
	m.input_data(); //输入矩阵m的数据
	m.display(); //显示矩阵m的数据

	int dim; //向量元素个数
	cin >> dim;
	Vector v(dim); //创建向量对象v
	v.input_data(); //输入向量v的数据
	v.display(); //显示向量v的数据
```

编写一个multiply函数，实现矩阵与向量的乘法。
这个函数既不适合作为Matrix类的成员函数，也不适合作为Vector类的成员函数，
因为它需要访问两个类的私有数据成员。
因此，它应该是一个全局函数。

```cpp
void multiply(const Matrix &m, const Vector &v, Vector &r)//结果是向量，用r来表示
{	if (m.dimension_column() != v.dimension() || 
		  m.dimension_row() != r.dimension()) //判断合法性
	{  cerr << "矩阵和向量的尺寸不匹配！\n";
		  exit(-1);
	}
	int row=m.dimension_row(),
        col=m.dimension_column();
	for (int i=0; i<row; i++)
	{  r.element(i) = 0;
		  for (int j=0; j<col; j++) //计算r[i]
			r.element(i) += m.element(i,j)*v.element(j);
	}
}
```

这个程序频繁地通过调用成员函数element来访问矩阵和向量的元素，合法性判断和函数调用开销很大，因此效率很低

把multiply说明成Matrix和Vector的**友元**！

```cpp
class Vector; //Vector的声明（由于在定义Matrix时需要用到它）
class Matrix
{	......
	friend void multiply(const Matrix &m, const Vector &v, 
					Vector &r); //这里提前用到Vector。
};
class Vector
{	......
	friend void multiply(const Matrix &m, const Vector &v, 
					Vector &r);
};

void multiply(const Matrix &m, const Vector &v,
					    Vector &r)
{	if (m.col != v.num || m.row != r.num)
	{	cerr << "矩阵和向量的尺寸不匹配！\n";
			exit(-1);
	}
	int *p_m=m.p_data,*p_r=r.p_data,*p_v;
	for (int i=0; i<m.row; i++)
	{	*p_r = 0;
			p_v = v.p_data;
			for (int j=0; j<m.col; j++)
			{	*p_r += (*p_m)*(*p_v);
				p_m++;
				p_v++;
			}
			p_r++;
	}
}

```

这样，可以直接访问矩阵和向量的私有数据成员，效率高。
