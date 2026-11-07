
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

bool validName(string name)
{
    if (name.empty())
        return false;

    bool hasLetter = false;

    for (int i = 0; i < name.length(); i++)
    {
        unsigned char ch = name[i];

        if (!isalpha(ch) && ch != ' ')
            return false;

        if (isalpha(ch))
            hasLetter = true;
    }

    return hasLetter;
}

string readName(string message)
{
    string name;

    while (true)
    {
        cout << message;
        getline(cin, name);

        if (validName(name))
            return name;

        cout << "Invalid Name! Use letters and spaces only.\n";
    }
}

int readID()
{
    string line;
    int id;
    char extra;

    while (true)
    {
        cout << "Enter User ID: ";
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> id) && !(ss >> extra) && id > 0)
            return id;

        cout << "Invalid ID! Enter a positive numerical ID.\n";
    }
}

string readPhone()
{
    string phone;

    while (true)
    {
        cout << "Enter Phone (10 digits): ";
        getline(cin, phone);

        bool valid = phone.length() == 10;

        for (int i = 0; valid && i < phone.length(); i++)
        {
            if (!isdigit(static_cast<unsigned char>(phone[i])))
                valid = false;
        }

        if (valid)
            return phone;

        cout << "Invalid Phone! Enter exactly 10 digits.\n";
    }
}

string readLocation()
{
    string location;

    while (true)
    {
        cout << "Enter Location (minimum 8 characters): ";
        getline(cin, location);

        if (location.length() >= 8 &&
            location.find_first_not_of(" \t") != string::npos)
            return location;

        cout << "Invalid Location! Enter at least 8 characters.\n";
    }
}

string readText(string message)
{
    string value;

    while (true)
    {
        cout << message;
        getline(cin, value);

        if (value.find_first_not_of(" \t") != string::npos)
            return value;

        cout << "This field cannot be empty.\n";
    }
}

float readPrice(string message)
{
    string line;
    float price;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> price) && !(ss >> extra) &&
            price > 0 && price <= 1000000000.0f)
            return price;

        cout << "Invalid amount! Enter a number greater than zero.\n";
    }
}

string readAvailability()
{
    string availability;

    while (true)
    {
        cout << "Enter Availability (Yes/No): ";
        getline(cin, availability);

        if (availability == "Yes" || availability == "No")
            return availability;

        cout << "Invalid Availability! Enter Yes or No.\n";
    }
}

int readChoice()
{
    string line;
    int choice;
    char extra;

    while (true)
    {
        cout << "\nEnter your choice: ";
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> choice) && !(ss >> extra) &&
            choice >= 1 && choice <= 3)
            return choice;

        cout << "Invalid choice! Enter 1, 2 or 3.\n";
    }
}

class User
{
protected:
    int id;
    string name;
    string phone;
    string location;

public:
    User()
    {
        id = 0;
        name = "";
        phone = "";
        location = "";
    }

    void inputUser()
    {
        id = readID();
        name = readName("Enter Name: ");
        phone = readPhone();
        location = readLocation();
    }

    void displayUser()
    {
        cout << "User ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Location: " << location << endl;
    }
};

class Service : public User
{
private:
    string serviceName;
    string description;
    float price;
    string availability;

public:
    Service()
    {
        serviceName = "";
        description = "";
        price = 0;
        availability = "";
    }

    void inputService()
    {
        cout << "\n ENTER SERVICE DETAILS\n";

        inputUser();

        serviceName = readText("Enter Service Name: ");
        description = readText("Enter Description: ");
        price = readPrice("Enter Price: Rs. ");
        availability = readAvailability();
    }

    void displayService()
    {
        cout << "\n SERVICE DETAILS\n";

        displayUser();

        cout << "Service Name: " << serviceName << endl;
        cout << "Description: " << description << endl;
        cout << "Price: Rs. " << price << endl;
        cout << "Availability: " << availability << endl;
    }
};

class Property : public User
{
private:
    string propertyType;
    string description;
    float rent;
    string availability;

public:
    Property()
    {
        propertyType = "";
        description = "";
        rent = 0;
        availability = "";
    }

    void inputProperty()
    {
        cout << "\n ENTER PROPERTY DETAILS\n";

        inputUser();

        propertyType = readText("Enter Property Type: ");
        description = readText("Enter Description: ");
        rent = readPrice("Enter Rent: Rs. ");
        availability = readAvailability();
    }

    void displayProperty()
    {
        cout << "\n PROPERTY DETAILS\n";

        displayUser();

        cout << "Property Type: " << propertyType << endl;
        cout << "Description: " << description << endl;
        cout << "Rent: Rs. " << rent << endl;
        cout << "Availability: " << availability << endl;
    }
};

class Vehicle : public User
{
private:
    string vehicleType;
    string description;
    float rent;
    string availability;

public:
    Vehicle()
    {
        vehicleType = "";
        description = "";
        rent = 0;
        availability = "";
    }

    void inputVehicle()
    {
        cout << "\n ENTER VEHICLE DETAILS\n";

        inputUser();

        vehicleType = readText("Enter Vehicle Type: ");
        description = readText("Enter Description: ");
        rent = readPrice("Enter Rent: Rs. ");
        availability = readAvailability();
    }

    void displayVehicle()
    {
        cout << "\n VEHICLE DETAILS\n";

        displayUser();

        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Description: " << description << endl;
        cout << "Rent: Rs. " << rent << endl;
        cout << "Availability: " << availability << endl;
    }
};

int main()
{
    Service service;
    Property property;
    Vehicle vehicle;

    cout << "\n TASKORA SERVICE & RENTAL MANAGEMENT\n";
    cout << "\n1. Add Service";
    cout << "\n2. Add Property";
    cout << "\n3. Add Vehicle";

    int choice = readChoice();

    if (choice == 1)
    {
        service.inputService();
        service.displayService();
    }
    else if (choice == 2)
    {
        property.inputProperty();
        property.displayProperty();
    }
    else if (choice == 3)
    {
        vehicle.inputVehicle();
        vehicle.displayVehicle();
    }

    return 0;
}
