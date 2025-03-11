/*
Designing a Car Rental System

Requirements

1) The car rental system should allow customers to browse and reserve available cars for specific dates.
2) Each car should have details such as make, model, year, license plate number, and rental price per day.
3) Customers should be able to search for cars based on various criteria, such as car type, price range, and availability.
4) The system should handle reservations, including creating, modifying, and canceling reservations.
5) The system should keep track of the availability of cars and update their status accordingly.
6) The system should handle customer information, including name, contact details, and driver's license information.
7) The system should handle payment processing for reservations.
8) The system should be able to handle concurrent reservations and ensure data consistency.


User/custiomers: name, contact details,  driver's license information
Vehicles: cars, bike, truck
Reservations: Vehicles, User, startDate, endDate, totalcost
Rental System: creating, modifying, canceling
Search: type, price range, availability, location
Payments: Credit, Debit, UPI, Paypal

*/

#include <bits/stdc++.h>
#include <chrono>

using namespace std;

enum class VehicleType { Car, Bike, Bus };
enum class PaymentStatus { Successful, Failed, Pending };

class Vehicle{
public:
    static int ID;
    
    VehicleType type;
    string registrationPlate;
    string model;
    string location;
    int vehicleID;
    bool available;

    Vehicle(VehicleType type,string registrationPlate,string model,string location) : type(type), registrationPlate(registrationPlate),model(model), location(location){
        available=true;
        this->vehicleID=ID++;
    }
    void getDetails(){
        string vehicleTypeString;
        if(type==VehicleType::Car) vehicleTypeString="Car";
        else if(type==VehicleType::Bike) vehicleTypeString="Bike";
        else vehicleTypeString="Bus";

        cout<<vehicleID<<" "<<vehicleTypeString<<" "<<model<<" "<<location<<" ";
        if(available) cout<<"available \n";
        else cout<<"not-available \n";
    }
};
int Vehicle::ID=1;


class Payment{
public:
    virtual void processPayment(int amount)=0;
};

class UPIPayment: public Payment{
public:
    void processPayment(int amount) override{
        cout<<"Paid "<<amount<<" via UPI\n";
    }
};

class CreditCardPayment: public Payment{
public:
    void processPayment (int amount) override{
        cout<<"Paid "<<amount<<" via Credit Card\n";
    }
};

class DebitCardPayment: public Payment{
public:
    void processPayment (int amount) override{
        cout<<"Paid "<<amount<<" via Debit Card\n";
    }
};

class Reservation;

class User{
public: 
    string name, mobile, email, lisenceNumber;
    Reservation* reservation;
    Payment* payment;
    User(string name,string mobile,string email,string lisenceNumber,Payment* payment): name(name), mobile(mobile), email(email), lisenceNumber(lisenceNumber),payment(payment) {};
};

class Reservation {
public:
    Vehicle* vehicle;
    User* user;
    chrono::system_clock::time_point startDate;
    chrono::system_clock::time_point endDate;
    int totalcost;
    PaymentStatus paymentStatus;

    Reservation(Vehicle* vehicle, User* user, std::chrono::system_clock::time_point startDate,std::chrono::system_clock::time_point endDate, int totalcost) 
        : vehicle(vehicle), user(user), startDate(startDate), endDate(endDate), totalcost(totalcost) {
        paymentStatus = PaymentStatus::Pending;
    }
};

class PricingStrategy{
public:
    virtual int claculatePrice(chrono::system_clock::time_point startDate, chrono::system_clock::time_point endDate)=0;
};

class CarStrategy: public PricingStrategy{
public:
    int claculatePrice(chrono::system_clock::time_point startDate, chrono::system_clock::time_point endDate) override{
        auto duration = chrono::duration_cast<std::chrono::hours>(endDate - startDate);
        int days = duration.count() / 24;
        
        return  100*days;
    }
};
class BikeStrategy: public PricingStrategy{
    public:
    int claculatePrice(chrono::system_clock::time_point startDate, chrono::system_clock::time_point endDate) override{
        auto duration = chrono::duration_cast<std::chrono::hours>(endDate - startDate);
        int days = duration.count() / 24;
        
        return  50*days;
    }
};
class BusStrategy: public PricingStrategy{
    public:
    int claculatePrice(chrono::system_clock::time_point startDate, chrono::system_clock::time_point endDate) override{
        auto duration = chrono::duration_cast<std::chrono::hours>(endDate - startDate);
        int days = duration.count() / 24;
        
        return  200*days;
    }
};


class TypeStrategy{
public:
    static void search(unordered_set<Vehicle*> vehicles, VehicleType vehicleType ) {
        for(auto &i: vehicles){
            if(i->type==vehicleType) i->getDetails();
        }
    }
};

class LocationStrategy {
public:
    static void search(unordered_set<Vehicle*> vehicles, string location){
        for(auto &i: vehicles){
            if(i->location==location) i->getDetails();
        }
    }
};

class AvailabilityStrategy{
public:
    static void search(unordered_set<Vehicle*> vehicles){
        for(auto &i: vehicles){
            if(i->available) i->getDetails();
        }
    }
};


class RentalSystem{
private:
    static RentalSystem* instance;
    RentalSystem(){}

public:

    unordered_set<Vehicle*> vehicles;
    unordered_set<Reservation*> reservations;
    PricingStrategy* pricingStrategy;

    static RentalSystem* getInstance(){
        if(instance==NULL) instance=new RentalSystem();
        return instance;
    };

    void createReservations(User* user, Vehicle* vehicle, int days) { 
        
        if(vehicle->type==VehicleType::Car) pricingStrategy= new CarStrategy();
        else if(vehicle->type==VehicleType::Bike) pricingStrategy= new BikeStrategy();
        if(vehicle->type==VehicleType::Bus) pricingStrategy= new BusStrategy();

        auto now = std::chrono::system_clock::now();
        auto endTime = now + std::chrono::hours(24 * days); //  days later
        int totalCost=pricingStrategy->claculatePrice(now, endTime);
        
        user->payment->processPayment(totalCost);
        vehicle->available=false;

        user->reservation= new Reservation( vehicle,user,now,endTime, totalCost );
    }

    Vehicle* findVehicle(int ID){
        for(auto &i: vehicles){
            if(i->ID==ID) return i;
        }
        return NULL;
    }

    void searchByType(VehicleType type){
        TypeStrategy::search(vehicles, type);
    }

    void searchByLocation(string location){
        LocationStrategy::search(vehicles,location);
    }

    void searchByAvailability (){
        AvailabilityStrategy::search(vehicles);
    }
    
    void addVehicle (Vehicle* vehicle){
        vehicles.emplace(vehicle);
    }
};

RentalSystem* RentalSystem::instance=NULL;


int main(){
    User* dhaval= new User("Dhaval","9898777712", "dhaval@gmail.com","LisenceDha1",new CreditCardPayment());
    User* tay= new User("Tay","1989198913", "tay@gmail.com","LisenceTay2",new UPIPayment());

    Vehicle* tesla=new Vehicle(VehicleType::Car,"tesla1", "Tesla-Model-X","New-York");
    Vehicle* ferrari=new Vehicle(VehicleType::Car,"ferrari2", "ferrari-italia-458","London");
    Vehicle* v3=new Vehicle(VehicleType::Car,"vehicle-3", "vehicle-3-car", "Location1");
    Vehicle* v4=new Vehicle(VehicleType::Car,"vehicle-4", "vehicle-4-car", "Location1");

    Vehicle* r15=new Vehicle(VehicleType::Bike,"r15-2", "Yamaha-r15","New-York");
    Vehicle* b2=new Vehicle(VehicleType::Bike,"Bike-2", "Bike-2","Location1");

    Vehicle* bus1=new Vehicle(VehicleType::Bus,"Bus-1", "Bus-1","London" );

    RentalSystem* rentalSystem= RentalSystem::getInstance();

    rentalSystem->addVehicle(tesla);
    rentalSystem->addVehicle(ferrari);
    rentalSystem->addVehicle(r15);
    rentalSystem->addVehicle(v3);
    rentalSystem->addVehicle(v4);
    rentalSystem->addVehicle(b2);
    rentalSystem->addVehicle(bus1);

    cout<<endl;
    rentalSystem->searchByLocation("New-York");
    cout<<endl;
    rentalSystem->searchByLocation("London");
    cout<<endl;
    
    rentalSystem->searchByType(VehicleType::Car);
    cout<<endl;
    rentalSystem->searchByAvailability();
    cout<<endl;
    
    rentalSystem->createReservations(dhaval,tesla,7);
    cout<<endl;
    rentalSystem->createReservations(tay,r15,5);
    cout<<endl;
    
    rentalSystem->searchByAvailability();
    cout<<endl;
    return 0;
}