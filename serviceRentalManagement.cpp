#include <iostream>
#include <string>
using namespace std;

class Service
{
protected:
    int serviceId;
    string serviceName;
    string location;
    float price;

public:
    Service();

    void inputService();
    void displayService();
};
Service::Service()
{
    serviceId = 0;
    serviceName = "";
    location = "";
    price = 0;
}
void Service::inputService()
{
    cout << "Enter Service ID: ";
    cin >> serviceId;
    cout << "Enter Service Name: ";
    cin >> serviceName;
    cout << "Enter Location: ";
    cin >> location;
    cout << "Enter Service Price: ";
    cin >> price;
}

void Service::displayService()
{
    cout << "\nService ID: " << serviceId << endl;
    cout << "Service Name: " << serviceName << endl;
    cout << "Location: " << location << endl;
    cout << "Service Price: Rs. " << price << endl;
}

class Property
{
protected:
    int propertyId;
    string propertyType;
    string location;
    float rent;

public:
    Property();

    void inputProperty();
    void displayProperty();
};

Property::Property()
{
    propertyId = 0;
    propertyType = "";
    location = "";
    rent = 0;
}
void Property::inputProperty()
{
    cout << "Enter Property ID: ";
    cin >> propertyId;
    cout << "Enter Property Type: ";
    cin >> propertyType;
    cout << "Enter Location: ";
    cin >> location;
    cout << "Enter Rent: ";
    cin >> rent;
}

void Property::displayProperty()
{
    cout << "\nProperty ID: " << propertyId << endl;
    cout << "Property Type: " << propertyType << endl;
    cout << "Location: " << location << endl;
    cout << "Rent: Rs. " << rent << endl;
}

class Vehicle
{
protected:
    int vehicleId;
    string vehicleType;
    string location;
    float price;

public:
    Vehicle();

    void inputVehicle();
    void displayVehicle();
};
Vehicle::Vehicle()
{
    vehicleId = 0;
    vehicleType = "";
    location = "";
    price = 0;
}
void Vehicle::inputVehicle()
{
    cout << "Enter Vehicle ID: ";
    cin >> vehicleId;
    cout << "Enter Vehicle Type: ";
    cin >> vehicleType;
    cout << "Enter Location: ";
    cin >> location;
    cout << "Enter Rental Price: ";
    cin >> price;
}

void Vehicle::displayVehicle()
{
    cout << "\nVehicle ID: " << vehicleId << endl;
    cout << "Vehicle Type: " << vehicleType << endl;
    cout << "Location: " << location << endl;
    cout << "Rental Price: Rs. " << price << endl;
}

