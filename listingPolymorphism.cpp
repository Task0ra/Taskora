
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

        cout << "Invalid name! Use letters and spaces only.\n";
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

        cout << "Invalid location! Enter at least 8 characters.\n";
    }
}

string readPhone()
{
    string phone;

    while (true)
    {
        cout << "Enter 10-digit Phone Number: ";
        getline(cin, phone);

        bool valid = phone.length() == 10;

        for (int i = 0; valid && i < phone.length(); i++)
        {
            if (!isdigit(static_cast<unsigned char>(phone[i])))
                valid = false;
        }

        if (valid)
            return phone;

        cout << "Invalid phone number! Enter exactly 10 digits.\n";
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

int readChoice(string message, int maximum)
{
    string line;
    int choice;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> choice) && !(ss >> extra) &&
            choice >= 1 && choice <= maximum)
            return choice;

        cout << "Invalid choice! Enter a number from 1 to "
             << maximum << ".\n";
    }
}

class Listing
{
protected:
    string location;
    float price;

public:
    Listing()
    {
        location = "";
        price = 0;
    }

    virtual void input()
    {
        location = readLocation();
        price = readPrice("Enter Price: Rs. ");
    }

    virtual void display()
    {
        cout << "Location: " << location << endl;
        cout << "Price: Rs. " << price << endl;
    }

    virtual ~Listing() {}
};

class ServiceListing : public Listing
{
private:
    string serviceName;
    string providerName;
    string phone;
    string experience;

public:
    void input() override
    {
        cout << "\nSERVICE LISTING\n";

        serviceName = readText("Enter Service Name: ");
        providerName = readName("Enter Provider Name: ");
        phone = readPhone();
        experience = readText("Enter Experience (e.g. 2 years): ");
        location = readLocation();
        price = readPrice("Enter Service Charge: Rs. ");
    }

    void display() override
    {
        cout << "\nSERVICE DETAILS\n";
        cout << "Service Name: " << serviceName << endl;
        cout << "Provider Name: " << providerName << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Experience: " << experience << endl;
        cout << "Location: " << location << endl;
        cout << "Service Charge: Rs. " << price << endl;
    }
};

class PropertyListing : public Listing
{
private:
    string propertyType;
    string ownerName;
    string ownerPhone;
    string propertyAddress;

public:
    void input() override
    {
        cout << "\nPROPERTY RENTAL LISTING\n";

        propertyType = readText(
            "Enter Property Type (e.g. room, flat, shop, store): ");

        ownerName = readName("Enter Owner Name: ");
        ownerPhone = readPhone();
        propertyAddress = readText("Enter Property Address: ");
        location = readLocation();
        price = readPrice("Enter Rent Amount: Rs. ");
    }

    void display() override
    {
        cout << "\nPROPERTY DETAILS\n";
        cout << "Property Type: " << propertyType << endl;
        cout << "Owner Name: " << ownerName << endl;
        cout << "Owner Phone: " << ownerPhone << endl;
        cout << "Property Address: " << propertyAddress << endl;
        cout << "Location: " << location << endl;
        cout << "Monthly Rent: Rs. " << price << endl;
    }
};

class VehicleListing : public Listing
{
private:
    string vehicleType;
    string vehicleModel;
    string ownerName;
    string ownerPhone;
    string registrationNumber;
    string fuelType;

public:
    void input() override
    {
        cout << "\nRENTAL VEHICLE LISTING\n";

        vehicleType = readText(
            "Enter Vehicle Type (e.g. car, bike, scooter): ");

        vehicleModel = readText("Enter Vehicle Model: ");
        ownerName = readName("Enter Owner Name: ");
        ownerPhone = readPhone();
        registrationNumber = readText("Enter Registration Number: ");
        fuelType = readText("Enter Fuel Type: ");
        location = readLocation();
        price = readPrice("Enter Rental Price: Rs. ");
    }

    void display() override
    {
        cout << "\nVEHICLE DETAILS\n";
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Vehicle Model: " << vehicleModel << endl;
        cout << "Owner Name: " << ownerName << endl;
        cout << "Owner Phone: " << ownerPhone << endl;
        cout << "Registration Number: " << registrationNumber << endl;
        cout << "Fuel Type: " << fuelType << endl;
        cout << "Location: " << location << endl;
        cout << "Rental Price: Rs. " << price << endl;
    }
};

int main()
{
    ServiceListing service;
    PropertyListing property;
    VehicleListing vehicle;

    Listing *item = nullptr;

    cout << "\n";
    cout << "       TASKORA LISTING SYSTEM\n";
    cout << "\n";
    cout << "1. Services\n";
    cout << "2. Rentals\n";

    int choice = readChoice("Enter your choice: ", 2);

    if (choice == 1)
    {
        item = &service;
    }
    else
    {
        cout << "\n1. Properties\n";
        cout << "2. Rental Vehicles\n";

        int rentalChoice = readChoice(
            "Enter rental category: ", 2);

        if (rentalChoice == 1)
            item = &property;
        else
            item = &vehicle;
    }

    item->input();
    item->display();

    return 0;
}
