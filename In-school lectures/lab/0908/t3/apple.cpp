#include <iostream>
#include <vector>
using namespace std;
vector<int> current;

void backtrack(int m_left, int index, int max_n, int prev)
{
    if (index == max_n)//n个位置占满了
    {
        if (m_left == 0)//如果m已经被分配完
        {
            for (int i = 0; i < max_n; ++i)
            {
                if (i > 0)
                    cout << " ";
                cout << current[i];
            }
            cout << endl;
        }
        return;
    }

    if (m_left == 0)//如果m已经被分配完，并且n没有被占满
    {
        current[index] = 0;//用递归来把后面的位置都赋值为0，因为后面的递归都会进入这一个if分支，而index不断加一，直到n个位置填满进入上面的分支，输出
        backtrack(0, index + 1, max_n, 0); 
        return;
    }
//其余的情况，如果m没有被分配完，尝试所有剩下的数字，对每个数字num采用递归，相当于现在有m_left-num个苹果分给n_left-1个盘子，n_left是剩下的n，这里通过更新index来实现
    for (int num = min(m_left, prev); num >= 0; --num)
    {
        current[index] = num;
        backtrack(m_left - num, index + 1, max_n, num);
    }
}

int main()
{
    int M, N;
    cin >> M >> N;
    current.resize(N, 0);
    backtrack(M, 0, N, M);
    return 0;
}