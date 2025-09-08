#include "inventory.h"
#include <iostream>
using namespace std;

int main()
{
    Inventory inventory;
    while (true)
    {
        int q = 0;
        cin >> q;
        if (q == -1)
            break;
        switch (q)
        {
        case 1:
        {
            int a, b, c;
            cin >> a >> b >> c;
            Thing thing = Thing(a, b, c);
            inventory.add(thing);
            break;
        }
        case 2:
        {
            int category;
            cin >> category;
            inventory.inquiry(category);
            break;
        }
        case 3:
        {
            int category, a, b, c, d;
            cin >> category >> a >> b >> c >> d;
            inventory.combine(category, a, b, c, d);
            break;
        }
        case 4:
        {
            while (true)
            {
                int category;
                cin >> category;
                if (category == -1)
                {
                    break;
                }

                int inquiries[5];
                inquiries[0] = category;
                for (int i = 1; i < 5; i++)
                {
                    cin >> inquiries[i];
                }
                inventory.use(inquiries);
            }
            break;
        }
        }
    }
    return 0;
}