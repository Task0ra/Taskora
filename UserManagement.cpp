#include <iostream>
#include <string>
using namespace std;

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

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Phone: ";
        cin >> phone;
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
        inputUser();

        cout << "Enter Location: ";
        cin >> location;
    }

    void displayCustomer()
    {
        displayUser();

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
        inputUser();

        cout << "Enter Service: ";
        cin >> service;

        cout << "Enter Distance: ";
        cin >> distance;

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Rating: ";
        cin >> rating;
    }

    void displayProvider()
    {
        displayUser();

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

    cout << "===== CUSTOMER =====" << endl;

    c.inputCustomer();

    cout << "\n===== CUSTOMER DETAILS =====" << endl;

    c.displayCustomer();


    cout << "\n===== SERVICE PROVIDER =====" << endl;

    p.inputProvider();

    cout << "\n===== PROVIDER DETAILS =====" << endl;

    p.displayProvider();

    return 0;
}
