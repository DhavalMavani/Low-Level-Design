#include <iostream>
#include <string>
using namespace std;

class RideService{
public:
    void requestRide(string &passenger, string &srcLoc, string &destLoc){
        cout << "Requesting a ride for passenger: " << passenger << " from " << srcLoc << " to " << destLoc << endl;
    }

    void cancelRide(string &passenger){ cout << "Canceling the ride for passenger: " << passenger << endl; }
};

class Command{
public:
    virtual void execute()=0;
};

class RideRequestCommand: public Command{
public:
    string passenger, srcLoc, destLoc;
    RideService* receiver;
    RideRequestCommand(RideService* receiver,string passenger, string srcLoc, string destLoc): receiver(receiver),passenger(passenger),
    srcLoc(srcLoc), destLoc(destLoc){};

    void execute(){ receiver->requestRide(passenger, srcLoc, destLoc); }
};

class RideCancelCommand: public Command{
public:
    string passenger, srcLoc, destLoc;
    RideService* receiver;
    RideCancelCommand(RideService* receiver,string passenger){
        this->receiver=receiver;
        this->passenger=passenger;
    };

    void execute() override{ receiver->cancelRide(passenger); }
};


class RideRequestInvoker {
public:
    void processRequest(Command* command){ command->execute(); }
};

int main(){
    RideService* rideService= new RideService();
    Command* request1= new RideRequestCommand(rideService,"Dhaval", "RJK", "BLR");
    Command* request2= new RideRequestCommand(rideService,"Taylor", "NYC", "BLR");
    Command* cancel1= new RideCancelCommand(rideService,"Taylor");

    RideRequestInvoker* rideRequestInvoker= new RideRequestInvoker();

    rideRequestInvoker->processRequest(request1);
    rideRequestInvoker->processRequest(request2);
    rideRequestInvoker->processRequest(cancel1);
    
    return 0;
}