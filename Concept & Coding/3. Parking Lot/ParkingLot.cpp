#include <iostream>
#include <chrono>
#include <thread> 
using namespace std;

enum class VehicleType {
    Car,
    Bike,
    Truck
};

class Vehicle{
public:
    VehicleType type;
    string lisencePlate;
    Vehicle(VehicleType type,string lisencePlate){
        this->type=type;
        this->lisencePlate=lisencePlate;
    }
};


enum class PaymentMode { UPI, DEBIT_CARD, CREDIT_CARD, PAYPAL };
class Payment{
public:
    PaymentMode mode;
    virtual void processPayment(double amount)=0;
};

class UPIPayment: public Payment{
public:
    UPIPayment(){ mode = PaymentMode::UPI; }
    void processPayment(double amount) override{ cout<<amount<<" paid via UPI \n"; }
};

class CREDIT_CARDPayment: public Payment{
public:
    CREDIT_CARDPayment(){ mode = PaymentMode::CREDIT_CARD; }
    void processPayment(double amount) override{ cout<<amount<<" paid via CREDIT_CARD \n"; }
};


class ParkingSpot{
public:
    int spotID;
    VehicleType type;
    bool isOccupied;
    ParkingSpot(int spotID,VehicleType type,bool isOccupied) { 
        this->spotID=spotID;
        this->isOccupied=isOccupied;
        this->type=type;
    }
};

class Ticket{
public:
    Vehicle* vehicle;
    time_t startTime;
    ParkingSpot* spot;
    Ticket(Vehicle* vehicle,ParkingSpot* spot){
        this->vehicle=vehicle;
        this->spot=spot;
        startTime = time(0);
    }
};

class ParkingLot{
private:
    ParkingLot(){}
    static ParkingLot* instance;
public:
    vector<vector<ParkingSpot*>> parking;

    static ParkingLot* getInstance(){
        if(instance==NULL) instance= new ParkingLot();
        return instance;
    }


    void initialize(int levels, int car, int bike, int truck){
        parking.resize(levels);
        int spotID=1;
        for(auto &level: parking){
            for(int i=0;i<car;i++) level.emplace_back(new ParkingSpot(spotID++,VehicleType::Car,false) );
            for(int i=0;i<bike;i++) level.emplace_back(new ParkingSpot(spotID++,VehicleType::Bike,false) );
            for(int i=0;i<truck;i++) level.emplace_back(new ParkingSpot(spotID++,VehicleType::Truck,false) );
        }
    }

    Ticket* parkVehicle(Vehicle* vehicle){
        for(auto &level: parking){
            for(auto &spot: level){
                if(!spot->isOccupied && spot->type==vehicle->type){
                    cout<<vehicle->lisencePlate<<" parked at "<<spot->spotID<<" \n";
                    spot->isOccupied=true;
                    return new Ticket(vehicle,spot);
                }
            }
        }
        cout<<"No parking available";
        return NULL;
    }
    int calculateFees(Ticket* ticket){
        time_t startTime=ticket->startTime;
        time_t endTime=time(0);
        int hours = difftime(endTime, startTime)/3600+1;
        double rate;
        switch (ticket->vehicle->type) {
            case VehicleType::Car: rate = 5.0; break;
            case VehicleType::Bike: rate = 2.0; break;
            case VehicleType::Truck: rate = 10.0; break;
            default: rate=3.5; break;
        }
        
        return rate*hours;
    }
    void exitVehicle(Ticket* ticket, Payment* method){
        double fees=calculateFees(ticket);
        method->processPayment(fees);
        ticket->spot->isOccupied=false;
        cout<<ticket->vehicle->lisencePlate<<" exited parking\n";
    }
    
};


ParkingLot* ParkingLot::instance=NULL;

class Driver{
    public:
        string name;
        Vehicle* vehicle;
        Ticket* ticket;
        Driver(string name, Vehicle* vehicle ) {
            this->name=name;
            this->vehicle=vehicle;
        }
    
        void parkVehicle(ParkingLot* lot){
            ticket=lot->parkVehicle(vehicle);
        }

        void exitVehicle(ParkingLot* lot, Payment* payment){
            lot->exitVehicle(ticket,payment);
        }

    };

int main() {
    ParkingLot* lot=ParkingLot::getInstance();
    lot->initialize(4,10,5,2);
    
    Vehicle* car1=new Vehicle(VehicleType::Car,"Plate1");
    Driver* dhaval=new Driver("Dhaval", car1);
    dhaval->parkVehicle(lot);
    dhaval->exitVehicle(lot, new UPIPayment());
    cout<<endl;
    
    Vehicle* bike1=new Vehicle(VehicleType::Bike,"Plate2");
    Driver* dhaval2=new Driver("Dhaval", bike1);
    dhaval2->parkVehicle(lot);
    dhaval2->exitVehicle(lot, new CREDIT_CARDPayment());
    cout<<endl;
    
    // this_thread::sleep_for(chrono::milliseconds(3000)); // 3 sec delay
    
    return 0;
}