#include <iostream>

using namespace std;
class LazySingleton {
private:
    // The single instance, initially null
    static LazySingleton* instance;

    // Private constructor to prevent instantiation
    LazySingleton() { 
        cout << "Singleton instance created!" << std::endl;
    }

public:
    // Public method to get the instance
    static LazySingleton* getInstance() {
        if (instance == nullptr) instance = new LazySingleton();
        return instance;
    }
};

// Initialize static member
LazySingleton* LazySingleton::instance = nullptr;

int main() {
    // Access the singleton instance
    LazySingleton* singleton1 = LazySingleton::getInstance();
    LazySingleton* singleton2 = LazySingleton::getInstance();

    cout << "Are the instances the same? " << (singleton1 == singleton2 ? "Yes" : "No") << std::endl;

    return 0;
}