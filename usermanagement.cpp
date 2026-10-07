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
