#include <iostream>
#include <vector>
using namespace std;

class Matrix
{
private:
    vector<vector<double>> data;
    int size;

public:
    // 构造函数
    Matrix(int size = 0) : size(size)
    {
        data.resize(size, vector<double>(size, 0.0));
    }

    // TODO: 重载 + 操作符（矩阵加法）
    Matrix operator+(const Matrix &other) const{
        Matrix result(size);
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // TODO: 重载 - 操作符（矩阵减法）
    Matrix operator-(const Matrix &other) const{
        Matrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // TODO: 重载 * 操作符（矩阵乘法）
    Matrix operator*(const Matrix &other) const{
        Matrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // TODO: 重载 == 操作符（判断矩阵相等）
    bool operator==(const Matrix &other) const{
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (data[i][j] != other.data[i][j])
                    return false;
            }
        }
        return true;
    }

    // TODO: 重载 [] 操作符（A[i][j]表示矩阵第i行第j列的元素）
    vector<double> &operator[](int index){
        return data[index];
    }

    // TODO: 重载 () 操作符（访问矩阵元素）
    double &operator()(int i, int j){
        return data[i][j];
    }

    // TODO：输出矩阵
    void print() const{
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << data[i][j];
                if (j < size - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
};

// TODO: 实现所有成员函数

// main函数部分请勿修改
int main()
{
    int n;
    cin >> n;

    Matrix A(n), B(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    int newA00, newB00;
    cin >> newA00 >> newB00;
    A[0][0] = newA00;
    B(0, 0) = newB00;

    cout << "A[0][0] = " << A[0][0] << endl;
    cout << "B(0,0) = " << B(0, 0) << endl;
    cout << "A + B:" << endl;
    (A + B).print();

    cout << "A - B:" << endl;
    (A - B).print();

    cout << "A * B:" << endl;
    (A * B).print();

    cout << "A == B: " << (A == B ? "true" : "false") << endl;

    return 0;
}