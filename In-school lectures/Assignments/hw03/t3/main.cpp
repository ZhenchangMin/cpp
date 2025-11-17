#include "p2.h"
int main(){
    AmphibianCar* A = new AmphibianCar("My amphibian car");
    Car* CarMode = A;
    Boat* BoatMode = A;
    CarMode->drive(); // 将Car中的drive()方法重写为driveAsCar()
    BoatMode->drive(); // 将Boat中的drive()方法重写为driveAsBoat()
}