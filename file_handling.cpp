#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cctype>

using namespace std;

// ==================== OOP: BASE CLASS ====================

class User {
public:
    string id, name, phone, area, password;

    virtual void display() const {
        cout << "ID: " << id << "\nName: " << name << '\n';
    }

    virtual ~User() {}
};

// ==================== CUSTOMER CLASS ====================

class Customer : public User {
public:
    void display() const override {
        User::display();
        cout << "Phone: " << phone << "\nArea: " << area << '\n';
    }
};

// ==================== SERVICE PROVIDER CLASS ====================

class ServiceProvider : public User {
public:
    string service, status;
    double serviceChargePerHour = 0.0;

    void display() const override {
        User::display();
        cout << "Service: " << service
             << "\nArea: " << area
             << "\nService charge: Rs. " << serviceChargePerHour
             << " per hour"
             << "\nStatus: " << status << '\n';
    }
};

// ==================== RENTAL PROPERTY CLASS ====================

class RentalProperty {
public:
    string propertyID, ownerID, type, title, location, availability;
    double rent = 0.0;

    void display() const {
        cout << "\nProperty ID: " << propertyID
             << "\nOwner ID: " << ownerID
             << "\nType: " << type
             << "\nTitle: " << title
             << "\nLocation: " << location
             << "\nRent: Rs. " << rent
             << "\nStatus: " << availability << '\n';
    }
};

// ==================== GENERAL FUNCTIONS ====================

string readText(string message) {
    string value;
    cout << message;
    getline(cin, value);

    replace(value.begin(), value.end(), '|', '/');
    return value;
}

string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });
    return text;
}

bool readChoice(int& choice);

// ==================== FIXED SERVICE LIST ====================

const vector<string> SERVICES = {
    "Driver",
    "Teacher",
    "Nurse",
    "Househelp",
    "Cook",
    "Electrician",
    "Plumber",
    "Caretaker",
    "Makeup Artist",
    "Doctor",
    "Painter"
};

void displayServiceOptions() {
    cout << "\n===== AVAILABLE SERVICES =====\n";

    for (size_t i = 0; i < SERVICES.size(); i++) {
        cout << i + 1 << ". " << SERVICES[i] << '\n';
    }
}

string chooseService() {
    displayServiceOptions();

    int choice;
    cout << "Choose a service by entering its number: ";

    if (!readChoice(choice)) {
        return "";
    }

    if (choice < 1 || choice > static_cast<int>(SERVICES.size())) {
        cout << "Invalid service choice. Please select a number from the list.\n";
        return "";
    }

    return SERVICES[choice - 1];
}

// ==================== FILE HANDLING FUNCTIONS ====================

vector<string> splitLine(const string& line) {
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, '|')) {
        fields.push_back(field);
    }

    return fields;
}

bool readPositiveAmount(string message, double& amount) {
    cout << message;

    if (!(cin >> amount) || amount <= 0) {
        cout << "Please enter a valid amount greater than zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

bool readChoice(int& choice) {
    if (!(cin >> choice)) {
        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

bool idExists(string filename, string id) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> fields = splitLine(line);

        if (!fields.empty() && fields[0] == id) {
            return true;
        }
    }

    return false;
}

// ==================== CUSTOMER REGISTRATION ====================

void registerCustomer() {
    Customer c;

    cout << "\n===== CUSTOMER REGISTRATION =====\n";

    c.id = readText("Create customer ID: ");

    if (c.id.empty() || idExists("customers.txt", c.id)) {
        cout << "ID is empty or already registered.\n";
        return;
    }

    c.name = readText("Enter name: ");
    c.phone = readText("Enter phone number: ");
    c.area = readText("Enter area/locality: ");
    c.password = readText("Create password: ");

    if (c.name.empty() || c.password.empty()) {
        cout << "Name and password cannot be empty.\n";
        return;
    }

    ofstream file("customers.txt", ios::app);

    if (!file) {
        cout << "Unable to open customers.txt.\n";
        return;
    }

    file << c.id << "|" << c.name << "|" << c.phone
         << "|" << c.area << "|" << c.password << '\n';

    cout << "Customer registered successfully!\n";
}

// ==================== PROVIDER REGISTRATION ====================

void registerProvider() {
    ServiceProvider p;

    cout << "\n===== SERVICE PROVIDER REGISTRATION =====\n";

    p.id = readText("Create provider ID: ");

    if (p.id.empty() || idExists("providers.txt", p.id)) {
        cout << "ID is empty or already registered.\n";
        return;
    }

    p.name = readText("Enter name: ");
    p.phone = readText("Enter phone number: ");
    p.service = chooseService();

    if (p.service.empty()) {
        cout << "Provider registration cancelled because no valid service was selected.\n";
        return;
    }

    p.area = readText("Enter area/locality: ");

    if (p.name.empty()) {
        cout << "Name cannot be empty.\n";
        return;
    }

    if (!readPositiveAmount(
            "Set your service charge per hour (Rs.): ",
            p.serviceChargePerHour)) {
        return;
    }

    p.password = readText("Create password: ");

    if (p.password.empty()) {
        cout << "Password cannot be empty.\n";
        return;
    }

    p.status = "Off Duty";

    ofstream file("providers.txt", ios::app);

    if (!file) {
        cout << "Unable to open providers.txt.\n";
        return;
    }

    file << p.id << "|" << p.name << "|" << p.phone
         << "|" << p.service << "|" << p.area
         << "|" << p.password << "|" << p.status
         << "|" << p.serviceChargePerHour << '\n';

    cout << "Provider registered successfully!\n";
    cout << "Your charge: Rs. " << p.serviceChargePerHour
         << " per hour.\n";
}
// ==================== DISPLAY CUSTOMERS ====================

void displayCustomers() {
    ifstream file("customers.txt");
    string line;
    bool found = false;

    cout << "\n===== REGISTERED CUSTOMERS =====\n";

    while (getline(file, line)) {
        vector<string> f = splitLine(line);

        if (f.size() >= 5) {
            found = true;
            cout << "\nID: " << f[0]
                 << "\nName: " << f[1]
                 << "\nPhone: " << f[2]
                 << "\nArea: " << f[3] << '\n';
        }
    }

    if (!found) {
        cout << "No customers registered yet.\n";
    }
}

// ==================== DISPLAY PROVIDERS ====================

void displayProviders() {
    ifstream file("providers.txt");
    string line;
    bool found = false;

    cout << "\n===== REGISTERED SERVICE PROVIDERS =====\n";

    while (getline(file, line)) {
        vector<string> f = splitLine(line);

        if (f.size() >= 7) {
            found = true;

            double charge = 0.0;

            if (f.size() >= 8) {
                try {
                    charge = stod(f[7]);
                } catch (...) {
                    charge = 0.0;
                }
            }

            cout << "\nID: " << f[0]
                 << "\nName: " << f[1]
                 << "\nPhone: " << f[2]
                 << "\nService: " << f[3]
                 << "\nArea: " << f[4]
                 << "\nStatus: " << f[6];

            if (f.size() >= 8) {
                cout << "\nService charge: Rs. " << charge
                     << " per hour";
            } else {
                cout << "\nService charge: Not set (older record)";
            }

            cout << '\n';
        }
    }

    if (!found) {
        cout << "No service providers registered yet.\n";
    }
}

// ==================== LOGIN VALIDATION ====================

bool checkLogin(string filename, string id, string password,
                int idField, int passwordField) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> f = splitLine(line);

        if (f.size() > static_cast<size_t>(
                max(idField, passwordField)) &&
            f[idField] == id &&
            f[passwordField] == password) {
            return true;
        }
    }

    return false;
}

// ==================== PROVIDER DUTY STATUS ====================

bool updateProviderStatus(string id, string newStatus) {
    ifstream file("providers.txt");

    if (!file) {
        cout << "Unable to open providers.txt.\n";
        return false;
    }

    ofstream temp("providers_temp.txt");

    if (!temp) {
        cout << "Unable to create temporary provider file.\n";
        return false;
    }

    string line;
    bool updated = false;

    while (getline(file, line)) {
        vector<string> f = splitLine(line);

        if (f.size() >= 7 && f[0] == id) {
            f[6] = newStatus;
            updated = true;

            if (f.size() == 7) {
                f.push_back("0");
            }
        }

        if (f.size() >= 7) {
            temp << f[0] << "|" << f[1] << "|" << f[2]
                 << "|" << f[3] << "|" << f[4]
                 << "|" << f[5] << "|" << f[6];

            if (f.size() >= 8) {
                temp << "|" << f[7];
            }

            temp << '\n';
        }
    }

    file.close();
    temp.close();

    if (!updated) {
        remove("providers_temp.txt");
        cout << "Provider record not found.\n";
        return false;
    }

    if (remove("providers.txt") != 0) {
        cout << "Could not update provider file. Close any program "
             << "using the file and try again.\n";
        remove("providers_temp.txt");
        return false;
    }

    if (rename("providers_temp.txt", "providers.txt") != 0) {
        cout << "Could not rename the temporary file.\n";
        return false;
    }

    return true;
}

// ==================== PROVIDER MENU ====================

void providerMenu(string id) {
    int choice;

    cout << "\n===== PROVIDER MENU =====\n";
    cout << "1. Go On Duty\n";
    cout << "2. Go Off Duty\n";
    cout << "Enter choice: ";

    if (!readChoice(choice)) {
        return;
    }

    if (choice == 1) {
        if (updateProviderStatus(id, "On Duty")) {
            cout << "You are now On Duty.\n";
        }
    } else if (choice == 2) {
        if (updateProviderStatus(id, "Off Duty")) {
            cout << "You are now Off Duty.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }

    cout << "Returning to the main menu...\n";
}
