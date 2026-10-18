
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>
using namespace std;

struct Customer {
    string id, name, phone, area, password;
};

struct Provider {
    string id, name, phone, service, area, password, status, charge;
};

string readText(string message) {
    string value;
    cout << message;
    getline(cin, value);

    for (int i = 0; i < (int)value.length(); i++)
        if (value[i] == '|') value[i] = '/';

    return value;
}

void registerCustomer() {
    Customer c;

    c.id = readText("Enter customer ID: ");

    ifstream check("customers.txt");
    string line;

    while (getline(check, line)) {
        if (line.substr(0, line.find('|')) == c.id) {
            cout << "This customer ID already exists.\n";
            return;
        }
    }
    check.close();

    c.name = readText("Enter name: ");
    c.phone = readText("Enter phone number: ");
    c.area = readText("Enter area/address: ");
    c.password = readText("Create password: ");

    ofstream file("customers.txt", ios::app);

    if (!file) {
        cout << "Unable to open customers.txt\n";
        return;
    }

    file << c.id << "|" << c.name << "|" << c.phone
         << "|" << c.area << "|" << c.password << "\n";

    cout << "Customer registered successfully!\n";
}

void registerProvider() {
    Provider p;

    p.id = readText("Enter provider ID: ");

    ifstream check("providers.txt");
    string line;

    while (getline(check, line)) {
        if (line.substr(0, line.find('|')) == p.id) {
            cout << "This provider ID already exists.\n";
            return;
        }
    }
    check.close();

    p.name = readText("Enter name: ");
    p.phone = readText("Enter phone number: ");
    p.service = readText("Enter service (cook, nurse, plumber, etc.): ");
    p.area = readText("Enter area/address: ");
    p.password = readText("Create password: ");

    p.charge = readText("Enter service charge per hour (in Rs.): ");

    p.status = "Off Duty";

    ofstream file("providers.txt", ios::app);

    if (!file) {
        cout << "Unable to open providers.txt\n";
        return;
    }

    file << p.id << "|" << p.name << "|" << p.phone
         << "|" << p.service << "|" << p.area
         << "|" << p.password << "|" << p.status
         << "|" << p.charge << "\n";

    cout << "Provider registered successfully!\n";
    cout << "Charge per hour: Rs. " << p.charge << "\n";
    cout << "Initial status: Off Duty\n";
}

void displayCustomers() {
    ifstream file("customers.txt");
    string line;

    cout << "\n===== REGISTERED CUSTOMERS =====\n";

    if (!file) {
        cout << "No customer records found.\n";
        return;
    }

    while (getline(file, line)) {
        size_t pos = line.find('|');

        if (pos != string::npos) {
            string fields[5];
            int field = 0;
            string value;

            for (char ch : line) {
                if (ch == '|') {
                    if (field < 5) fields[field++] = value;
                    value = "";
                } else {
                    value += ch;
                }
            }

            if (field < 5) fields[field] = value;

            cout << "ID: " << fields[0]
                 << "\nName: " << fields[1]
                 << "\nPhone: " << fields[2]
                 << "\nArea: " << fields[3]
                 << "\n----------------------\n";
        }
    }
}

void displayProviders() {
    ifstream file("providers.txt");
    string line;

    cout << "\n===== SERVICE PROVIDERS =====\n";

    if (!file) {
        cout << "No provider records found.\n";
        return;
    }

    while (getline(file, line)) {
        string fields[8];
        int field = 0;
        string value;

        for (char ch : line) {
            if (ch == '|') {
                if (field < 8) fields[field++] = value;
                value = "";
            } else {
                value += ch;
            }
        }

        if (field < 8) fields[field] = value;

        cout << "ID: " << fields[0]
             << "\nName: " << fields[1]
             << "\nPhone: " << fields[2]
             << "\nService: " << fields[3]
             << "\nArea: " << fields[4]
             << "\nStatus: " << fields[6]
             << "\nCharge per hour: Rs. " << fields[7]
             << "\n----------------------\n";
    }
}

bool checkLogin(string filename, string id, string password,
                int idField, int passwordField) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        string fields[8];
        int field = 0;
        string value;

        for (char ch : line) {
            if (ch == '|') {
                if (field < 8) fields[field++] = value;
                value = "";
            } else {
                value += ch;
            }
        }

        if (field < 8) fields[field] = value;

        if (fields[idField] == id &&
            fields[passwordField] == password)
            return true;
    }

    return false;
}

void updateProviderStatus(string id, string newStatus) {
    ifstream input("providers.txt");
    ofstream output("providers_temp.txt");

    if (!input || !output) {
        cout << "Unable to update provider file.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(input, line)) {
        string fields[8];
        int field = 0;
        string value;

        for (char ch : line) {
            if (ch == '|') {
                if (field < 8) fields[field++] = value;
                value = "";
            } else {
                value += ch;
            }
        }

        if (field < 8) fields[field] = value;

        if (fields[0] == id) {
            fields[6] = newStatus;
            found = true;
        }

        output << fields[0] << "|" << fields[1] << "|"
               << fields[2] << "|" << fields[3] << "|"
               << fields[4] << "|" << fields[5] << "|"
               << fields[6] << "|" << fields[7] << "\n";
    }

    input.close();
    output.close();

    if (!found) {
        remove("providers_temp.txt");
        cout << "Provider record not found.\n";
        return;
    }

    if (remove("providers.txt") != 0) {
        cout << "Could not remove the original provider file.\n";
        remove("providers_temp.txt");
        return;
    }

    if (rename("providers_temp.txt", "providers.txt") != 0) {
        cout << "Could not replace provider file.\n";
        return;
    }

    cout << "Provider status updated to " << newStatus << ".\n";
}

void providerMenu(string id) {
    while (true) {
        cout << "\n===== SERVICE PROVIDER MENU =====\n";
        cout << "1. Go On Duty\n";
        cout << "2. Go Off Duty\n";
        cout << "3. Return to Main Menu\n";

        string choice = readText("Enter choice: ");

        if (choice == "1") {
            updateProviderStatus(id, "On Duty");
            return;
        } else if (choice == "2") {
            updateProviderStatus(id, "Off Duty");
            return;
        } else if (choice == "3") {
            return;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void searchService() {
    string wanted = readText("Which service do you need? ");

    ifstream file("providers.txt");
    string line;
    bool found = false;

    cout << "\n===== AVAILABLE PROVIDERS =====\n";

    while (getline(file, line)) {
        string fields[8];
        int field = 0;
        string value;

        for (char ch : line) {
            if (ch == '|') {
                if (field < 8) fields[field++] = value;
                value = "";
            } else {
                value += ch;
            }
        }

        if (field < 8) fields[field] = value;

        string service = fields[3];
        string query = wanted;

        for (char& ch : service)
            if (ch >= 'A' && ch <= 'Z')
                ch += ('a' - 'A');

        for (char& ch : query)
            if (ch >= 'A' && ch <= 'Z')
                ch += ('a' - 'A');

        if (service == query && fields[6] == "On Duty") {
            cout << "\nProvider ID: " << fields[0]
                 << "\nName: " << fields[1]
                 << "\nPhone: " << fields[2]
                 << "\nService: " << fields[3]
                 << "\nArea: " << fields[4]
                 << "\nCharge per hour: Rs. " << fields[7]
                 << "\n";

            found = true;
        }
    }

    if (!found)
        cout << "No matching providers are currently on duty.\n";
}

void submitRating() {
    string providerID = readText("Enter provider ID to rate: ");

    ifstream file("providers.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.substr(0, line.find('|')) == providerID) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Provider ID not found.\n";
        return;
    }

    string input = readText("Enter rating (1 to 5): ");
    int rating;

    try {
        size_t used;
        rating = stoi(input, &used);

        if (used != input.size() || rating < 1 || rating > 5) {
            cout << "Rating must be a whole number from 1 to 5.\n";
            return;
        }
    } catch (...) {
        cout << "Invalid rating.\n";
        return;
    }

    ofstream reviews("reviews.txt", ios::app);

    reviews << providerID << "|" << rating << "\n";

    cout << "Rating saved successfully!\n";
}

void customerMenu() {
    cout << "\n===== CUSTOMER MENU =====\n";
    cout << "1. Search for a service\n";
    cout << "2. Submit a provider rating\n";

    string choice = readText("Enter choice: ");

    if (choice == "1")
        searchService();
    else if (choice == "2")
        submitRating();
    else
        cout << "Invalid choice.\n";
}

void customerLogin() {
    string id = readText("Customer ID: ");
    string password = readText("Password: ");

    if (checkLogin("customers.txt", id, password, 0, 4)) {
        cout << "Customer login successful!\n";
        cout << "A real app can request phone location permission here.\n";
        customerMenu();
    } else {
        cout << "Incorrect customer ID or password.\n";
    }
}

void providerLogin() {
    string id = readText("Provider ID: ");
    string password = readText("Password: ");

    if (checkLogin("providers.txt", id, password, 0, 5)) {
        cout << "Provider login successful!\n";
        cout << "A real app can request phone location permission here.\n";
        providerMenu(id);
    } else {
        cout << "Incorrect provider ID or password.\n";
    }
}

int main() {
    while (true) {
        cout << "\n========== TASKORA ==========\n";
        cout << "1. Register Customer\n";
        cout << "2. Register Service Provider\n";
        cout << "3. Customer Login\n";
        cout << "4. Service Provider Login\n";
        cout << "5. Display Customers\n";
        cout << "6. Display Service Providers\n";
        cout << "7. Exit\n";

        string choice = readText("Enter choice: ");

        if (choice == "1")
            registerCustomer();
        else if (choice == "2")
            registerProvider();
        else if (choice == "3")
            customerLogin();
        else if (choice == "4")
            providerLogin();
        else if (choice == "5")
            displayCustomers();
        else if (choice == "6")
            displayProviders();
        else if (choice == "7") {
            cout << "Thank you for using Taskora!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
