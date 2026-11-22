#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool validText(string s)
{
    if (s.empty())
        return false;

    for (int i = 0; i < s.length(); i++)
    {
        if (!isalpha(s[i]) && s[i] != ' ')
            return false;
    }

    return true;
}

class Listing
{
protected:
    string name;
    string location;
    float price;

public:
    virtual void input()
    {
        do
        {
            cout << "Enter Listing Name: ";
            getline(cin >> ws, name);

            if (!validText(name))
                cout << "Invalid Name! Use letters only.\n";

        } while (!validText(name));

        do
        {
            cout << "Enter Location: ";
            getline(cin, location);

            if (!validText(location))
                cout << "Invalid Location! Use letters only.\n";

        } while (!validText(location));

        cout << "Enter Price: ";
        while (!(cin >> price) || price < 0)
        {
            cout << "Invalid Price! Enter a number 0 or greater: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    virtual void display()
    {
        cout << "Listing Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Price: Rs. " << price << endl;
    }

    virtual ~Listing() {}
};

class ServiceListing : public Listing
{
public:
    void input() override
    {
        cout << "\n--- SERVICE LISTING ---\n";
        Listing::input();
    }

    void display() override
    {
        cout << "\nService Details\n";
        Listing::display();
    }
};

class RentalListing : public Listing
{
private:
    string rentalType;

public:
    void input() override
    {
        cout << "\n--- RENTAL LISTING ---\n";

        do
        {
            cout << "Enter Rental Type (Property/Vehicle): ";
            getline(cin >> ws, rentalType);

            if (rentalType != "Property" &&
                rentalType != "Vehicle" &&
                rentalType != "property" &&
                rentalType != "vehicle")
            {
                cout << "Invalid Type! Enter Property or Vehicle.\n";
            }

        } while (rentalType != "Property" &&
                 rentalType != "Vehicle" &&
                 rentalType != "property" &&
                 rentalType != "vehicle");

        Listing::input();
    }

    void display() override
    {
        cout << "\nRental Details\n";
        cout << "Rental Type: " << rentalType << endl;
        Listing::display();
    }
};

int main()
{
    Listing *item;
    ServiceListing service;
    RentalListing rental;

    int choice;

    cout << "===== TASKORA LISTING MANAGEMENT =====\n";
    cout << "1. Service Listing\n";
    cout << "2. Rental Listing\n";
    cout << "Enter Choice: ";

    while (!(cin >> choice) || choice < 1 || choice > 2)
    {
        cout << "Invalid Choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (choice == 1)
        item = &service;
    else
        item = &rental;

    item->input();
    item->display();

    return 0;
}