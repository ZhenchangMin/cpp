#include "SmartPointer.h"

SmartPointer::SmartPointer(const SmartPointer &sptr)
{
    if (sptr.pointer == nullptr || sptr.ref_cnt == nullptr)
    {
        pointer = nullptr;
        ref_cnt = nullptr;
    }
    else
    {
        pointer = sptr.pointer;
        ref_cnt = sptr.ref_cnt;
        ++(*ref_cnt);
    }
}

void SmartPointer::assign(const SmartPointer &sptr)
{
    if (this == &sptr) {
        return;
    }
    if (ref_cnt != nullptr)
    {
        --(*ref_cnt);
        if (*ref_cnt == 0)
        { 
            delete pointer;
            delete ref_cnt;
        }
    }
    if (sptr.pointer != nullptr && sptr.ref_cnt != nullptr) {
        pointer = sptr.pointer;
        ref_cnt = sptr.ref_cnt;
        ++(*ref_cnt); // 引用计数+1
    }
}

SmartPointer::~SmartPointer()
{
    if (ref_cnt == nullptr)
    {
        return;
    }

    --(*ref_cnt);
    if (*ref_cnt == 0)
    { 
        delete pointer;
        delete ref_cnt;
    }

    if (pointer != nullptr)
        pointer = nullptr;
    ref_cnt = nullptr;
}

int main()
{
    SmartPointer sp1(new Node(1));
    SmartPointer *sp2 = new SmartPointer(new Node(2));
    // 函数结束，sp1被销毁，此时sp2仍持有node1的地址，node1不被销毁
}