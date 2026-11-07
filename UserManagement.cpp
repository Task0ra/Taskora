
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

float readNumber(string message, float minimum, float maximum)
{
    string line;
    float number;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> number) && !(ss >> extra) &&
            number >= minimum && number <= maximum)
            return number;

        cout << "Invalid Input! Enter a valid number.\n";
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

    User(int i, string n, string p, string l)
    {
        id = i;
        name = n;
        phone = p;
        location = l;
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
        cout << "\nUser ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Location: " << location << endl;
    }
};

class Customer : public User
{
public:
    void inputCustomer()
    {
        User::inputUser();
    }

    void displayCustomer()
    {
        User::displayUser();
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

        service = readText("Enter Service: ");
        distance = readNumber("Enter Distance: ", 0, 1000000);
        price = readNumber("Enter Price: Rs. ", 0.01, 1000000000);
        rating = readNumber("Enter Rating (0-5): ", 0, 5);
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

    cout << "\n CUSTOMER \n";
    c.inputCustomer();

    cout << "\n CUSTOMER DETAILS \n";
    c.displayCustomer();

    cout << "\nSERVICE PROVIDER\n";
    p.inputProvider();

    cout << "\n PROVIDER DETAILS \n";
    p.displayProvider();

    return 0;
}
