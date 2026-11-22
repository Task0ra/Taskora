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
