
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stdexcept>
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

class User
{
protected:
    int id;
    string name;
    string phone;
    string location;

public:
    void inputUser()
    {
        id = readID();
        name = readName("Enter Name: ");
        phone = readPhone();
        location = readLocation();
    }

    void displayUser()
    {
        cout << "\nUser ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Location: " << location << endl;
    }

    void saveUser(ofstream &file, string userType)
    {
        file << userType << "|"
             << id << "|"
             << name << "|"
             << phone << "|"
             << location;
    }
};

class ServiceProvider : public User
{
private:
    string category;
    string listingName;
    string description;
    float price;
    string availability;

public:
    void inputProvider()
    {
        inputUser();

        cout << "\n1. Services\n";
        cout << "2. Rentals\n";

        int choice = readChoice("Enter Category: ", 2);

        if (choice == 1)
        {
            category = "Service";
            listingName = readText("Enter Service Name: ");
            description = readText("Enter Description: ");
        }
        else
        {
            cout << "\n1. Properties\n";
            cout << "2. Rental Vehicles\n";

            int rentalChoice = readChoice(
                "Enter Rental Category: ", 2);

            if (rentalChoice == 1)
            {
                category = "Property";
                listingName = readText("Enter Property Type: ");
            }
            else
            {
                category = "Rental Vehicle";
                listingName = readText("Enter Vehicle Type: ");
            }

            description = readText("Enter Description: ");
        }

        price = readPrice("Enter Price/Rent: Rs. ");
        availability = readAvailability();
    }

    void displayProvider()
    {
        displayUser();

        cout << "Category: " << category << endl;
        cout << "Listing Name: " << listingName << endl;
        cout << "Description: " << description << endl;
        cout << "Price/Rent: Rs. " << price << endl;
        cout << "Availability: " << availability << endl;
    }

    void saveProvider(ofstream &file)
    {
        saveUser(file, "Service Provider");

        file << "|" << category
             << "|" << listingName
             << "|" << description
             << "|" << price
             << "|" << availability << endl;
    }
};

class Customer : public User
{
public:
    void inputCustomer()
    {
        inputUser();
    }

    void saveCustomer(ofstream &file)
    {
        saveUser(file, "Customer");
        file << endl;
    }
};

void displayRecords()
{
    ifstream file("taskora.txt");

    if (!file)
        throw runtime_error("Unable to open the file.");

    string line;
    bool found = false;

    cout << "\n===== SAVED TASKORA RECORDS =====\n";

    while (getline(file, line))
    {
        cout << line << endl;
        found = true;
    }

    if (!found)
        cout << "No records found.\n";

    file.close();
}

int main()
{
    try
    {
        Customer customer;
        ServiceProvider provider;

        cout << "\n===== TASKORA FILE MANAGEMENT SYSTEM =====\n";

        cout << "\n1. Customer\n";
        cout << "2. Service Provider\n";

        int choice = readChoice("Enter User Type: ", 2);

        ofstream file("taskora.txt", ios::app);

        if (!file)
            throw runtime_error("Unable to open file for saving.");

        if (choice == 1)
        {
            cout << "\n===== CUSTOMER DETAILS =====\n";

            customer.inputCustomer();
            customer.displayUser();
            customer.saveCustomer(file);
        }
        else
        {
            cout << "\n===== SERVICE PROVIDER DETAILS =====\n";

            provider.inputProvider();
            provider.displayProvider();
            provider.saveProvider(file);
        }

        file.close();

        if (!file)
            throw runtime_error("Error while saving the record.");

        cout << "\nRecord saved successfully!\n";

        displayRecords();
    }
    catch (const exception &e)
    {
        cout << "\nError: " << e.what() << endl;
    }

    return 0;
}
