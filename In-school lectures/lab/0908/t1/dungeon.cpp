#include <iostream>
#include "dungeon.h"

using namespace std;

// TODO: 完成 Printer 类中的函数实现
Printer::Printer(int d)
{
    this->level = d;
    for (int i = 0; i < level - 1; i++)
    {
        cout << "  ";
    }
    cout << "Entering level " << level << endl;
}
Printer::~Printer()
{
    for (int i = 0; i < level - 1; i++)
    {
        cout << "  ";
    }
    cout << "Leaving level " << level << endl;
}
