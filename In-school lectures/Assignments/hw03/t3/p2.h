#include "Vehicle.h"
class Car : public Vehicle
{
protected:
    virtual void car_mode() {
        cout << name << " drive on road" << endl;
    }
public:
    Car(string name) : Vehicle(name) {}
    void drive() override {
        car_mode();
    }
};

class Boat : public Vehicle
{
protected:
    virtual void boat_mode() {
        cout << name << " drive on river" << endl;
    }
public:
    Boat(string name) : Vehicle(name) {}
    void drive() override {
        boat_mode();
    }
};

class AmphibianCar : public Car, public Boat
{
public:
    AmphibianCar(string name) : Car(name), Boat(name) {}
    void driveAsCar() {
        cout << Car::name << " drive on road as car" << endl;
    }
    void driveAsBoat() {
        cout << Boat::name << " drive on river as boat" << endl;
    }
protected:
    void car_mode() override {
        cout << Car::name << " drive on road as car" << endl;
    }
    void boat_mode() override {
        cout << Boat::name << " drive on river as boat" << endl;
    }
};