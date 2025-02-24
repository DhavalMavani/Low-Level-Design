#include <iostream>
using namespace std;


class IDriveStrategy{
public:
    virtual void drive()=0;
};

class NormalDrive: public IDriveStrategy{
public:
    void drive() override{cout<<"Normal Drive \n"; }
};

class SportsDrive: public IDriveStrategy{
public:
    void drive() override{cout<<"Sports Drive \n"; }
};

class Vehicle{
public:
    IDriveStrategy* driveStrategy;
    Vehicle(IDriveStrategy* driveStrategy){ this->driveStrategy=driveStrategy;}
    void drive(){driveStrategy->drive(); };
};

int main(){
    Vehicle* sports=new Vehicle(new SportsDrive());
    Vehicle* normal=new Vehicle(new NormalDrive());

    sports->drive();
    normal->drive();
    
}
