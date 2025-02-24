#include <iostream>
#include <string>
#include <vector>
#include <stack>


using namespace std;

class Command{
public:
    virtual void execute()=0;
    virtual void unExecute()=0;
};

class Light{
public:
    string location;
    bool isOn;
    Light(string location) : location(location) {isOn=false; }
    void turnOnLight(){
        isOn=true;
        cout<<location<<" light turned on \n";
    }

    void turnOffLight(){
        isOn=false;
        cout<<location<<" light turned off \n";
    }
};

class LightOnCommand: public Command{
public:
    Light* light;
    LightOnCommand(Light* light) : light(light){}
    void execute() override { light->turnOnLight(); }
    void unExecute() override { light->turnOffLight(); }
};

class LightOffCommand: public Command{
public:
    Light* light;
    LightOffCommand(Light* light) : light(light){}
    void execute() override { light->turnOffLight(); }
    void unExecute() override { light->turnOnLight(); }
};

class Fan{
public:
    string location;
    bool isOn;
    Fan(string location) : location(location) {isOn=false; }
    void turnOnFan(){
        isOn=true;
        cout<<location<<" fan turned on \n";
    }

    void turnOffFan(){
        isOn=false;
        cout<<location<<" fan turned off \n";
    }
};

class FanOnCommand: public Command{
public:
    Fan* fan;
    FanOnCommand(Fan* fan) : fan(fan){}
    void execute() override { fan->turnOnFan(); }
    void unExecute() override { fan->turnOffFan(); }
};

class FanOffCommand: public Command{
public:
    Fan* fan;
    FanOffCommand(Fan* fan) : fan(fan){}
    void execute() override { fan->turnOffFan(); }
    void unExecute() override { fan->turnOnFan(); }
};

class GarageDoor{
public:
    string location;
    bool isOpen;
    GarageDoor(string location) : location(location) {isOpen=false; }
    void openDoor(){
        isOpen=true;
        cout<<location<<" door is open \n";
    }
    
    void closeDoor(){
        isOpen=false;
        cout<<location<<" door is close \n";
    }
};

class GarageDoorOpenCommand: public Command{
public:
    GarageDoor* garageDoor;
    GarageDoorOpenCommand(GarageDoor* garageDoor) : garageDoor(garageDoor) {}
    void execute() override{garageDoor->openDoor(); }
    void unExecute() override{garageDoor->closeDoor(); }
};

class GarageDoorCloseCommand: public Command{
public:
    GarageDoor* garageDoor;
    GarageDoorCloseCommand(GarageDoor* garageDoor) : garageDoor(garageDoor) {}
    void execute() override{garageDoor->closeDoor(); }
    void unExecute() override{garageDoor->openDoor(); }
};

class NoCommand: public Command{
public:
    void execute() override{ cout<<"Do Nothing"; }
    void unExecute() override{ cout<<"Do Nothing"; }
};

class Remote{
public:
    stack<Command*> st;
    vector<Command*> onCommands;
    vector<Command*> offCommands;
    Remote(){
        onCommands.resize(7,new NoCommand()); 
        offCommands.resize(7,new NoCommand()); 
    }
    void setCommand(int slot, Command* cmd1,Command* cmd2 ){
        onCommands[slot]=cmd1;
        offCommands[slot]=cmd2;
    };

    void pressOnButton(int slot){
        onCommands[slot]->execute();
        st.emplace(onCommands[slot]);
    }
    void pressOffButton(int slot){ 
        offCommands[slot]->unExecute(); 
        st.emplace(offCommands[slot]);
    }

    void pressUndo(){
        if(!st.empty()){
            st.top()->unExecute();
            st.pop();
        }
        else cout<<"No Undo options available\n";
    }
};


int main(){    
    Light* light1= new Light("Kitchen");
    Light* light2= new Light("Hall");
    Fan* fan1= new Fan("Hall");
    GarageDoor* garageDoor= new GarageDoor("garage");

    LightOnCommand* light1On=new LightOnCommand(light1);
    LightOffCommand* light1Off=new LightOffCommand(light1);

    LightOnCommand* light2On=new LightOnCommand(light2);
    LightOffCommand* light2Off=new LightOffCommand(light2);

    FanOnCommand* fan1On= new FanOnCommand(fan1);
    FanOffCommand* fan1Off= new FanOffCommand(fan1);

    GarageDoorOpenCommand* garageDoorOpen= new GarageDoorOpenCommand(garageDoor);
    GarageDoorCloseCommand* garageDoorClose= new GarageDoorCloseCommand(garageDoor);

    Remote* remote= new Remote();
    remote->setCommand(0,light1On, light1Off);
    remote->setCommand(1,light2On, light2Off);
    remote->setCommand(2,fan1On, fan1Off);
    remote->setCommand(3,garageDoorOpen, garageDoorClose);


    // remote->pressOnButton(0);
    // remote->pressOnButton(1);
    // remote->pressOnButton(2);
    // remote->pressOnButton(3);
    // remote->pressUndo();
    // remote->pressUndo();
    // remote->pressOffButton(1);
    // remote->pressUndo();
    // remote->pressUndo();
    
    while(true){
        int choice, slot;
        cout << "\nSelect an option:\n1. Turn On\n2. Turn Off\n3. Undo\n4. Exit\nChoice: ";
        cin >> choice;

        if(choice == 4) break;

        if(choice == 1 || choice == 2){
            cout << "Enter slot (0-Kitchen Light, 1-Hall Light, 2-Hall Fan): ";
            cin >> slot;
            if(choice == 1)
                remote->pressOnButton(slot);
            else
                remote->pressOffButton(slot);
        } else if(choice == 3){
            remote->pressUndo();
        } else {
            cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}