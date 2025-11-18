#include <iostream>
#include "Vehicle.h"
using namespace std;

class Car : virtual public Vehicle {
public:
    Car(const string& n) : Vehicle(n) {}
    void drive() override{
        cout << name << " drive on road" << endl;
    }
    string getName() const {
        return name;
    }
};

class Boat : virtual public Vehicle {
public:
    Boat(const string& n) : Vehicle(n) {}
    void drive() override{
        cout << name << " drive on river" << endl;
    }
    string getName() const {
        return name;
    }
};
class AmphibianCar : public Car, public Boat {
public:
    AmphibianCar(const string& n) : Car(n), Boat(n), Vehicle(n) {}
    void driveAsCar(){
        cout << Car::getName() << " drive on road as car" << endl;
    }
    void driveAsBoat(){
        cout << Boat::getName() << " drive on river as boat" << endl;
    }
    void drive() override {
        if ((Car*)this != nullptr && typeid(*this) == typeid(AmphibianCar)) {
            driveAsCar();
        }
        else if ((Boat*)this != nullptr) {
            driveAsBoat();
        }
    }
};