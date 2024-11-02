//-----------------------------------------------
// Filename: main.cpp
// By: Jack Hartwig
// Description: CPP program to simulate a vending machine
// Compile Command: g++ main.cpp -o vending_machine -std=c++11
// Running Command: ./vending_machine
// or use the ./compile_and_run script
//-----------------------------------------------


#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>

// Constants
const std::string SECRET_CODE = "1234"; // Secret code to display inventory
const int INITIAL_INVENTORY = 2;
const double GUM_COST = 0.50;
const double PEANUTS_COST = 0.55;
const double CRACKERS_COST = 0.65;
const double MMS_COST = 1.00;

// Item details
struct Item {
    std::string name;
    double cost;
    int inventory;
};

// Initialize vending machine items
std::unordered_map<char, Item> items = {
    {'G', {"Gum", GUM_COST, INITIAL_INVENTORY}},
    {'P', {"Peanuts", PEANUTS_COST, INITIAL_INVENTORY}},
    {'C', {"Cheese Crackers", CRACKERS_COST, INITIAL_INVENTORY}},
    {'M', {"M&Ms", MMS_COST, INITIAL_INVENTORY}}
};

// Display welcome message and instructions
void displayWelcomeMessage() {
    std::cout << "Welcome to Mr. Zippy’s vending machine.\n";
    std::cout << "Cost of Gum ($0.50), Peanuts ($0.55), Cheese Crackers ($0.65), or M&Ms ($1.00).\n";
    std::cout << "Enter item selection: Gum (G), Peanuts (P), Cheese Crackers (C), or M&Ms (M)\n";
}

// Display current inventory for all items
void displayInventory() {
    std::cout << "\nCurrent Inventory:\n";
    for (const auto& item : items) {
        std::cout << item.second.name << ": " << item.second.inventory << "\n";
    }
}

// Prompt for item selection and validate
char selectItem() {
    std::string selection;
    while (true) {
        std::cout << "\nEnter item selection (G, P, C, M) or enter the secret code to view inventory: ";
        std::cin >> selection;
        
        if (selection == SECRET_CODE) {
            displayInventory();
            continue;
        }
        
        if (selection.size() == 1 && items.find(selection[0]) != items.end()) {
            char selectedChar = selection[0];
            if (items[selectedChar].inventory > 0) return selectedChar;
            else std::cout << "Out of stock. Please select another item.\n";
        } else {
            std::cout << "Invalid selection. Try again.\n";
        }
    }
}

// Prompt for confirmation of item selection
bool confirmSelection(const Item& item) {
    char confirm;
    while (true) {
        std::cout << "You selected " << item.name << ". Is this correct? (Y/N): ";
        std::cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') return true;
        else if (confirm == 'N' || confirm == 'n') return false;
        else std::cout << "Invalid input. Please enter Y or N.\n";
    }
}

// Accept payment from user
double acceptPayment(double cost) {
    double total = 0.0;
    char payment;

    std::cout << "Enter payment (D for dime, Q for quarter, B for dollar):\n";
    while (total < cost) {
        std::cout << "Total entered: $" << std::fixed << std::setprecision(2) << total << "\n";
        std::cin >> payment;
        if (payment == 'D' || payment == 'd') total += 0.10;
        else if (payment == 'Q' || payment == 'q') total += 0.25;
        else if (payment == 'B' || payment == 'b') total += 1.00;
        else std::cout << "Invalid input. Please enter D, Q, or B.\n";
    }

    return total;
}

// Process item vending, including dispensing and updating inventory
void processItem(const Item& item, double totalPayment) {
    double change = totalPayment - item.cost;
    items[item.name[0]].inventory--; // Update inventory for the item

    std::cout << item.name << " has been dispensed.\n";
    if (change > 0) {
        std::cout << "Change of $" << std::fixed << std::setprecision(2) << change << " has been returned.\n";
    }
}

// Check if vending machine should shut down
bool checkShutdown() {
    for (const auto& item : items) {
        if (item.second.inventory > 0) return false;
    }
    return true;
}

int main() {
    displayWelcomeMessage();

    while (true) {
        char selection = selectItem();
        Item& selectedItem = items[selection];

        if (!confirmSelection(selectedItem)) continue;

        double totalPayment = acceptPayment(selectedItem.cost);
        processItem(selectedItem, totalPayment);

        if (checkShutdown()) {
            std::cout << "Machine is out of stock. Shutting down...\n";
            break;
        }
    }

    return 0;
}
