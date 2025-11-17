#include <iostream>
using namespace std;

class Vehicle {
protected:
    string name;
public:
    Vehicle(const string& n) : name(n) {}
    virtual void drive() = 0;
};

class Car : public Vehicle {
public:
    Car(const string& n) : Vehicle(n) {}
    void drive() override{
        cout << name << " drive on road" << endl;
    }
    string getName() const {
        return name;
    }
};

class Boat : public Vehicle {
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
    AmphibianCar(const string& n) : Car(n), Boat(n) {}
    void driveAsCar(){
        cout << Car::getName() << " drive on road as car" << endl;
    }
    void driveAsBoat(){
        cout << Boat::getName() << " drive on river as boat" << endl;
    }
    void drive() override {
        if (Car *car = dynamic_cast<Car*>(this)) {
            
        }
        else if (dynamic_cast<Boat*>(this)) {
            driveAsBoat();
        }
    }
};