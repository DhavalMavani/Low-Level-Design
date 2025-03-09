#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum class SignType { Red, Yellow, Green };

class Signal {
private:
    int ID;
    SignType currSignType;
    int redTime, yellowTime, greenTime;
    int timeRemaining;

public:
    Signal(int ID, int redTime, int yellowTime, int greenTime) 
        : ID(ID), redTime(redTime), yellowTime(yellowTime), greenTime(greenTime) {
        reset();
    }

    void reset() {
        currSignType = SignType::Red;
        timeRemaining = redTime;
    }

    void timeElapsed(int time) {
        timeRemaining -= time;
        if (timeRemaining <= 0) {
            switchSign();
        }
    }

    void switchSign() {
        switch (currSignType) {
            case SignType::Red: 
                currSignType = SignType::Green;
                timeRemaining = greenTime;
                break;
            case SignType::Green: 
                currSignType = SignType::Yellow;
                timeRemaining = yellowTime;
                break;
            case SignType::Yellow: 
                currSignType = SignType::Red;
                timeRemaining = redTime;
                break;
        }
    }

    void overrideSignal(SignType newSign) {  // Emergency override
        currSignType = newSign;
        switch (newSign) {
            case SignType::Red: timeRemaining = redTime; break;
            case SignType::Yellow: timeRemaining = yellowTime; break;
            case SignType::Green: timeRemaining = greenTime; break;
        }
    }

    void updateDurations(int red, int yellow, int green) {  // Update signal timing dynamically
        redTime = red;
        yellowTime = yellow;
        greenTime = green;
    }

    void currStatus() const {
        static unordered_map<SignType, string> signMap = {
            {SignType::Red, "Red"}, {SignType::Yellow, "Yellow"}, {SignType::Green, "Green"}
        };
        cout << "Signal " << ID << ": " << signMap[currSignType] << " (" << timeRemaining << "s remaining)\n";
    }
};

class Intersection {
private:
    vector<Signal*> signals;

public:
    int ID;
    Intersection(int ID) : ID(ID) {}

    ~Intersection() {  // Proper cleanup
        for (auto signal : signals) delete signal;
    }

    void addSignal(Signal* signal) {
        signals.push_back(signal);
    }

    void syncSignals() {
        for (auto& signal : signals) signal->reset();
    }

    void updateSignals(int time) {
        for (auto& signal : signals) signal->timeElapsed(time);
    }

    void overrideEmergency(SignType emergencySign) {  // Emergency mode activation
        for (auto& signal : signals) signal->overrideSignal(emergencySign);
    }

    void getStatus() const {
        cout << "Intersection " << ID << ":\n";
        for (auto& signal : signals) signal->currStatus();
        cout << endl;
    }
};

class TrafficControl {
private:
    static TrafficControl* instance;
    vector<Intersection*> intersections;

    TrafficControl() {}

public:
    static TrafficControl* getInstance() {
        if (!instance) instance = new TrafficControl();
        return instance;
    }

    ~TrafficControl() {  // Cleanup memory
        for (auto& intersection : intersections) delete intersection;
    }

    void addIntersection(Intersection* intersection) {
        intersections.push_back(intersection);
    }

    void syncIntersections() {
        for (auto& intersection : intersections) intersection->syncSignals();
    }

    void updateSystem(int time) {
        for (auto& intersection : intersections) intersection->updateSignals(time);
    }

    void triggerEmergency(int intersectionID, SignType emergencySign) { // Emergency handling
        for (auto& intersection : intersections) {
            if (intersectionID == intersection->ID) { 
                intersection->overrideEmergency(emergencySign);
            }
        }
    }

    void getStatus() const {
        for (auto& intersection : intersections) intersection->getStatus();
    }
};

// Initialize singleton instance
TrafficControl* TrafficControl::instance = nullptr;

int main() {
    TrafficControl* trafficControl = TrafficControl::getInstance();

    // Create signals
    Signal* s1 = new Signal(1, 20, 5, 15);
    Signal* s2 = new Signal(2, 20, 5, 15);
    Signal* s3 = new Signal(3, 20, 5, 15);
    Signal* s4 = new Signal(4, 20, 5, 15);

    // Create intersections
    Intersection* i1 = new Intersection(1);
    Intersection* i2 = new Intersection(2);

    i1->addSignal(s1);
    i1->addSignal(s2);
    i2->addSignal(s3);
    i2->addSignal(s4);

    trafficControl->addIntersection(i1);
    trafficControl->addIntersection(i2);

    trafficControl->syncIntersections();

    // Simulate traffic system
    for (int i = 0; i < 10; i++) {
        trafficControl->updateSystem(5);
    }

    cout << "\n--- Traffic Status ---\n";
    trafficControl->getStatus();

    // Simulate emergency at intersection 1
    cout << "\n--- Emergency: Ambulance Approaching Intersection 1 ---\n";
    trafficControl->triggerEmergency(1, SignType::Green);
    trafficControl->getStatus();

    return 0;
}
