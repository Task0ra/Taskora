#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cctype>

using namespace std;

// ==================== OOP: BASE CLASS ====================

class User {
public:
    string id, name, phone, area, password;

    virtual void display() const {
        cout << "ID: " << id << "\nName: " << name << '\n';
    }

    virtual ~User() {}
};

// ==================== CUSTOMER CLASS ====================

class Customer : public User {
public:
    void display() const override {
        User::display();
        cout << "Phone: " << phone << "\nArea: " << area << '\n';
    }
};

// ==================== SERVICE PROVIDER CLASS ====================

class ServiceProvider : public User {
public:
    string service, status;
    double serviceChargePerHour = 0.0;

    void display() const override {
        User::display();
        cout << "Service: " << service
             << "\nArea: " << area
             << "\nService charge: Rs. " << serviceChargePerHour
             << " per hour"
             << "\nStatus: " << status << '\n';
    }
};

// ==================== RENTAL PROPERTY CLASS ====================

class RentalProperty {
public:
    string propertyID, ownerID, type, title, location, availability;
    double rent = 0.0;

    void display() const {
        cout << "\nProperty ID: " << propertyID
             << "\nOwner ID: " << ownerID
             << "\nType: " << type
             << "\nTitle: " << title
             << "\nLocation: " << location
             << "\nRent: Rs. " << rent
             << "\nStatus: " << availability << '\n';
    }
};

// ==================== GENERAL FUNCTIONS ====================

string readText(string message) {
    string value;
    cout << message;
    getline(cin, value);

    replace(value.begin(), value.end(), '|', '/');
    return value;
}

string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });
    return text;
}

bool readChoice(int& choice);

// ==================== FIXED SERVICE LIST ====================

const vector<string> SERVICES = {
    "Driver",
    "Teacher",
    "Nurse",
    "Househelp",
    "Cook",
    "Electrician",
    "Plumber",
    "Caretaker",
    "Makeup Artist",
    "Doctor",
    "Painter"
};

void displayServiceOptions() {
    cout << "\n===== AVAILABLE SERVICES =====\n";

    for (size_t i = 0; i < SERVICES.size(); i++) {
        cout << i + 1 << ". " << SERVICES[i] << '\n';
    }
}

string chooseService() {
    displayServiceOptions();

    int choice;
    cout << "Choose a service by entering its number: ";

    if (!readChoice(choice)) {
        return "";
    }

    if (choice < 1 || choice > static_cast<int>(SERVICES.size())) {
        cout << "Invalid service choice. Please select a number from the list.\n";
        return "";
    }

    return SERVICES[choice - 1];
}
