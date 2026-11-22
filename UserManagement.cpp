
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool validText(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isalpha(s[i]) && s[i] != ' ')
            return false;
    }

    return !s.empty();
}

class User
{
protected:
    int id;
    string name;
    string phone;

public:
    User()
    {
        id = 0;
        name = "";
        phone = "";
    }

    User(int i, string n, string p)
    {
        id = i;
        name = n;
        phone = p;
    }

    void inputUser()
    {
        cout << "Enter User ID: ";
        cin >> id;

        do
        {
            cout << "Enter Name: ";
            cin >> name;

            if (!validText(name))
                cout << "Invalid Name! Try again.\n";

        } while (!validText(name));

        do
        {
            cout << "Enter Phone (10 digits): ";
            cin >> phone;

            bool valid = phone.length() == 10;

            for (int i = 0; i < phone.length(); i++)
            {
                if (!isdigit(phone[i]))
                    valid = false;
            }

            if (!valid)
                cout << "Invalid Phone! Try again.\n";

        } while (phone.length() != 10 ||
                 phone.find_first_not_of("0123456789") != string::npos);
    }

    void displayUser()
    {
        cout << "\nUser ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
    }
};

class Customer : public User
{
private:
    string location;

public:
    void inputCustomer()
    {
        User::inputUser();

        do
        {
            cout << "Enter Location: ";
            cin >> location;

            if (!validText(location))
                cout << "Invalid Location! Try again.\n";

        } while (!validText(location));
    }

    void displayCustomer()
    {
        User::displayUser();
        cout << "Location: " << location << endl;
    }
};

class ServiceProvider : public User
{
private:
    string service;
    float distance;
    float price;
    float rating;

public:
    void inputProvider()
    {
        User::inputUser();

        do
        {
            cout << "Enter Service: ";
            cin >> service;

            if (!validText(service))
                cout << "Invalid Service! Try again.\n";

        } while (!validText(service));

        cout << "Enter Distance: ";
        cin >> distance;

        while (distance < 0)
        {
            cout << "Invalid Distance! Enter again: ";
            cin >> distance;
        }

        cout << "Enter Price: ";
        cin >> price;

        while (price < 0)
        {
            cout << "Invalid Price! Enter again: ";
            cin >> price;
        }

        cout << "Enter Rating (0-5): ";
        cin >> rating;

        while (rating < 0 || rating > 5)
        {
            cout << "Invalid Rating! Enter again: ";
            cin >> rating;
        }
    }

    void displayProvider()
    {
        User::displayUser();

        cout << "Service: " << service << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Price: Rs. " << price << endl;
        cout << "Rating: " << rating << "/5" << endl;
    }
};

int main()
{
    Customer c;
    ServiceProvider p;

    cout << " CUSTOMER " << endl;
    c.inputCustomer();

    cout << "\n CUSTOMER DETAILS " << endl;
    c.displayCustomer();

    cout << "\nSERVICE PROVIDER" << endl;
    p.inputProvider();

    cout << "\n PROVIDER DETAILS " << endl;
    p.displayProvider();

    return 0;
}
