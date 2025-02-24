#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Product {
public:
    string name;
    double price;
    
    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class Slot {
public:
    int slotSize;
    Product* product;
    int quantity;
    bool isOccupied;

    Slot(int slotSize) {
        this->slotSize = slotSize;
        this->product = nullptr;
        this->quantity = 0;
        this->isOccupied = false;
    }

    ~Slot() {
        delete product;
    }
};

class Transaction {
public:
    double amount;
    Product* product;
    int quantity;
    bool successful;

    Transaction(double amount, Product* product, int quantity, bool successful) {
        this->amount = amount;
        this->product = product;
        this->quantity = quantity;
        this->successful = successful;
    }
};

class VendingMachine {
private:
    unordered_map<string, Slot*> productMap;  // Map product name to slot
    vector<Slot*> machine;
    vector<Transaction*> transactionsHistory;
    double money;

public:
    VendingMachine(int slots, int slotSize) {
        money = 0;
        for (int i = 0; i < slots; i++) {
            machine.push_back(new Slot(slotSize));
        }
        cout << "Vending Machine initialized with " << slots << " slots.\n";
    }

    ~VendingMachine() {
        for (auto slot : machine) {
            delete slot;
        }
        for (auto transaction : transactionsHistory) {
            delete transaction;
        }
        cout << "Vending Machine shutting down. Memory cleared.\n";
    }

    double purchaseProduct(const string& productName, int quantity, double amount) {
        if (productMap.find(productName) == productMap.end()) {
            cout << "Error: " << productName << " not available.\n";
            return amount;
        }

        Slot* slot = productMap[productName];

        if (quantity <= 0) {
            cout << "Error: Invalid quantity.\n";
            return amount;
        }

        double totalCost = slot->product->price * quantity;

        if (amount < totalCost) {
            cout << "Error: Insufficient funds. Required: " << totalCost << ", Provided: " << amount << "\n";
            return amount;
        }

        if (slot->quantity < quantity) {
            cout << "Error: Not enough stock of " << productName << ". Available: " << slot->quantity << "\n";
            return amount;
        }

        // Process transaction
        slot->quantity -= quantity;
        money += totalCost;
        double change = amount - totalCost;

        transactionsHistory.push_back(new Transaction(totalCost, slot->product, quantity, true));

        cout << "Dispensing " << quantity << " " << productName << "(s).\n";
        cout << "Change returned: $" << change << "\n";

        return change;
    }

    void addProduct(Product* product, int quantity) {
        if (quantity <= 0) {
            cout << "Error: Invalid quantity.\n";
            return;
        }

        for (auto& slot : machine) {
            if (!slot->isOccupied && quantity <= slot->slotSize) {
                slot->isOccupied = true;
                slot->quantity = quantity;
                slot->product = product;
                productMap[product->name] = slot;

                cout << "Added " << product->name << " with quantity " << quantity << " to the vending machine.\n";
                return;
            }
        }

        cout << "Error: No available slot for " << product->name << ".\n";
    }

    void addStock(const string& productName, int quantity) {
        if (productMap.find(productName) == productMap.end()) {
            cout << "Error: " << productName << " not found in vending machine.\n";
            return;
        }

        Slot* slot = productMap[productName];

        if (quantity <= 0) {
            cout << "Error: Invalid quantity.\n";
            return;
        }

        if (slot->quantity + quantity > slot->slotSize) {
            cout << "Error: Not enough space to add " << quantity << " more units of " << productName << ".\n";
            return;
        }

        slot->quantity += quantity;
        cout << "Stock updated: " << productName << " now has " << slot->quantity << " units.\n";
    }

    void removeProduct(const string& productName) {
        if (productMap.find(productName) == productMap.end()) {
            cout << "Error: " << productName << " not found.\n";
            return;
        }

        Slot* slot = productMap[productName];
        delete slot->product; // Free memory for Product
        slot->isOccupied = false;
        slot->product = nullptr;
        slot->quantity = 0;
        productMap.erase(productName);

        cout << "Product " << productName << " removed from the vending machine.\n";
    }

    int withdrawMoney() {
        cout << "Withdrawn amount: $" << money << "\n";
        int amount = money;
        money = 0;
        return amount;
    }

    void showTransactionHistory() {
        if (transactionsHistory.empty()) {
            cout << "No transactions recorded.\n";
            return;
        }

        cout << "Transaction History:\n";
        for (const auto& transaction : transactionsHistory) {
            cout << "Product: " << transaction->product->name
                 << " | Quantity: " << transaction->quantity
                 << " | Amount: $" << transaction->amount
                 << " | Status: " << (transaction->successful ? "Success" : "Failed") << "\n";
        }
    }
};

int main() {
    Product* coke = new Product("Coke", 2.5);
    Product* chips = new Product("Chips", 4);
    Product* chocolate = new Product("Chocolate", 5);

    VendingMachine machine(50, 30);

    machine.addProduct(coke, 25);
    machine.addProduct(chips, 10);
    machine.addProduct(chocolate, 20);

    // cout << "Attempting to purchase Coke...\n";
    machine.purchaseProduct("Coke", 3, 10);

    // cout << "Adding stock to Chips...\n";
    machine.addStock("Chips", 5);

    // cout << "Removing Chocolate...\n";
    machine.removeProduct("Chocolate");

    // cout << "Withdrawing money...\n";
    machine.withdrawMoney();

    // cout << "Displaying transaction history...\n";
    machine.showTransactionHistory();

    return 0;
}
