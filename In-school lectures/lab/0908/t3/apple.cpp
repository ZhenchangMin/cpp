#include <iostream>
#include <vector>
using namespace std;
vector<int> current;

void backtrack(int m_left, int index, int max_n, int prev)
{
    if (index == max_n)
    {
        if (m_left == 0)
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

    if (m_left == 0)
    {
        current[index] = 0;
        backtrack(0, index + 1, max_n, 0); 
        return;
    }

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