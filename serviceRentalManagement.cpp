#include <iostream>
#include <string>
using namespace std;
class Service
{
private:
    string serviceName;
    string description;
    float price;
    string location;
    string availability;

public:
    Service()
    {
        serviceName = "";
        description = "";
        price = 0;
        location = "";
        availability = "";
    }
    void inputService()
    {
        cout << "\n ENTER SERVICE DETAILS" << endl;
        cout << "Enter Service Name: ";
        cin >> serviceName;
        cout << "Enter Description: ";
        cin >> description;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Location: ";
        cin >> location;
        cout << "Enter Availability (Yes/No): ";
        cin >> availability;
    }
    void displayService()
    {
        cout << "\n SERVICE DETAILS " << endl;
        cout << "Service Name: " << serviceName << endl;
        cout << "Description: " << description << endl;
        cout << "Price: Rs. " << price << endl;
        cout << "Location: " << location << endl;
        cout << "Availability: " << availability << endl;
    }
};
class Property
{
private:
    string propertyType;
    string description;
    float rent;
    string location;
    string availability;
public:
    Property()
    {
        propertyType = "";
        description = "";
        rent = 0;
        location = "";
        availability = "";
    }
    void inputProperty()
    {
        cout << "\n ENTER PROPERTY DETAILS " << endl;
        cout << "Enter Property Type: ";
        cin >> propertyType;
        cout << "Enter Description: ";
        cin >> description;
        cout << "Enter Rent: ";
        cin >> rent;
        cout << "Enter Location: ";
        cin >> location;
        cout << "Enter Availability (Yes/No): ";
        cin >> availability;
    }
    void displayProperty()
    {
        cout << "\n PROPERTY DETAILS " << endl;
        cout << "Property Type: " << propertyType << endl;
        cout << "Description: " << description << endl;
        cout << "Rent: Rs. " << rent << endl;
        cout << "Location: " << location << endl;
        cout << "Availability: " << availability << endl;
    }
};
class Vehicle
{
private:
    string vehicleType;
    string description;
    float rent;
    string location;
    string availability;
public:
    Vehicle()
    {
        vehicleType = "";
        description = "";
        rent = 0;
        location = "";
        availability = "";
    }
    void inputVehicle()
    {
        cout << "\n ENTER VEHICLE DETAILS " << endl;
        cout << "Enter Vehicle Type: ";
        cin >> vehicleType;
        cout << "Enter Description: ";
        cin >> description;
        cout << "Enter Rent: ";
        cin >> rent;
        cout << "Enter Location: ";
        cin >> location;
        cout << "Enter Availability (Yes/No): ";
        cin >> availability;
    }

    void displayVehicle()
    {
        cout << "\n VEHICLE DETAILS" << endl;
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Description: " << description << endl;
        cout << "Rent: Rs. " << rent << endl;
        cout << "Location: " << location << endl;
        cout << "Availability: " << availability << endl;
    }
};
int main()
{
    Service service;
    Property property;
    Vehicle vehicle;
    int choice;
    cout << "   TASKORA SERVICE & RENTAL MANAGEMENT" << endl;
    cout << "\n1. Add Service";
    cout << "\n2. Add Property";
    cout << "\n3. Add Vehicle";
    cout << "\n\nEnter your choice: ";
    cin >> choice;
    if(choice == 1)
    {
        service.inputService();
        service.displayService();
    }
    else if(choice == 2)
    {
        property.inputProperty();
        property.displayProperty();
    }
    else if(choice == 3)
    {
        vehicle.inputVehicle();
        vehicle.displayVehicle();
    }
    else
    {
        cout << "\nInvalid choice." << endl;
    }
    return 0;
}
