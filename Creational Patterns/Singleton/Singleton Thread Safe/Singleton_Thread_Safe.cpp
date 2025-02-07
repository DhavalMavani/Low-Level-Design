#include <iostream>
#include <mutex>

using namespace std;

class LazySingleton {
private:
    static LazySingleton* instance; // The single instance, initially null
    
    static mutex mtx;  // Mutex for thread safety

    LazySingleton() { 
        cout << "Singleton Thread_Safe instance created!" << endl;
    }// Private constructor to prevent instantiation

public:
    // Public method to get the instance
    static LazySingleton* getInstance() {
        // First check (not locked) for performance
        if (instance == NULL) {
            // Lock the mutex to ensure thread safety
            mtx.lock();
            if (instance == nullptr) { instance = new LazySingleton(); } // Second check (locked) to ensure only one instance is created
            mtx.unlock();
        }
        return instance;
    }
};

// Initialize static members
LazySingleton* LazySingleton::instance = nullptr;
mutex LazySingleton::mtx;

int main() {
    // Access the singleton instance
    LazySingleton* singleton1 = LazySingleton::getInstance();
    LazySingleton* singleton2 = LazySingleton::getInstance();

    // Confirm the two pointers are the same
    cout << "Are the instances the same? " << (singleton1 == singleton2 ? "Yes" : "No") <<endl;

    return 0;
}
