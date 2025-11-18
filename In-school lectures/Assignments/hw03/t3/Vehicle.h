#include <iostream>
#include <string>
using namespace std;
class Vehicle {
    protected:
        string name;
    public:
        Vehicle(string name): name(name) {};
        virtual void drive() = 0;
};