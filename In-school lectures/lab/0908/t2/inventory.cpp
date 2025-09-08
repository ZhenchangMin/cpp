#include "inventory.h"
#include <iostream>
using namespace std;

void Inventory::setStorage(int category, int quality, int storage){
    for(Thing thing:this->things){
        if(thing.getCategory() == category && thing.getQuality() == quality){
            thing.setStorage(storage);
            break;
        }
    }
}
int Inventory::getStorage(int category, int quality){
    for(Thing thing:this->things){
        if(thing.getCategory() == category && thing.getQuality() == quality){
            return thing.getStorage();
        }
    }
    return 0;
}

void Inventory::add(Thing thing){
    if(size == 0){
        this->things[0] = thing;
        this->size = 1;
        return;
    }
    bool found = false;
    for (Thing t : this->things)
    {
        if (thing.getCategory() == t.getCategory() && thing.getQuality() == t.getQuality())
        {
            t.setStorage(t.getStorage() + thing.getStorage());
            found = true;
            break;
        }
    }
    if(!found) this->things[this->size] = thing;
    this->size++;
}

void Inventory::inquiry(int category)
{
    bool found = false;
    for(Thing thing:this->things){
        if(thing.getCategory() == category && thing.getQuality() == 0){
            cout << thing.getStorage() << ' ';
            found = true;
            break;
        }
    }
    if(!found) cout << 0 << ' ';
    found = false;
    for (Thing thing : this->things)
    {
        if (thing.getCategory() == category && thing.getQuality() == 1)
        {
            cout << thing.getStorage() << ' ';
            found = true;
            break;
        }
    }
    if(!found) cout << 0 << ' ';
    found = false;
    for (Thing thing : this->things)
    {
        if (thing.getCategory() == category && thing.getQuality() == 2)
        {
            cout << thing.getStorage() << ' ';
            found = true;
            break;
        }
    }
    if(!found) cout << 0 << ' ';
    found = false;
    for (Thing thing : this->things)
    {
        if (thing.getCategory() == category && thing.getQuality() == 3)
        {
            cout << thing.getStorage() << endl;
            found = true;
            break;
        }
    }
    if(!found) cout << 0 << endl;
}
void Inventory::combine(int category, int a, int b, int c, int d)
{

}

void Inventory::use(int *numbers)
{
    for(int i = 0; i < 5; i++){
        if(numbers[0] != -1){
            for(Thing thing:this->things){
                if(thing.getCategory() == numbers[0] && thing.getQuality() == 0){
                    if(thing.getStorage() >= numbers[1]){
                        thing.setStorage(thing.getStorage() - numbers[1]);
                        break;
                    }
                }
            }
                for(Thing thing:this->things){
                    if(thing.getCategory() == numbers[0] && thing.getQuality() == 1){
                        if(thing.getStorage() >= numbers[2]){
                            thing.setStorage(thing.getStorage() - numbers[2]);
                            break;
                        }
                    }
                }
                for(Thing thing:this->things){
                    if(thing.getCategory() == numbers[0] && thing.getQuality() == 2){
                        if(thing.getStorage() >= numbers[3]){
                            thing.setStorage(thing.getStorage() - numbers[3]);
                            break;
                        }
                    }
                }
                for(Thing thing:this->things){
                    if(thing.getCategory() == numbers[0] && thing.getQuality() == 3){
                        if(thing.getStorage() >= numbers[4]){
                            thing.setStorage(thing.getStorage() - numbers[4]);
                            break;
                        }
                    }
                }
        }
    }
}