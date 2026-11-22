
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

float readAmount(string message)
{
    string line;
    float amount;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> amount) && !(ss >> extra) &&
            amount > 0 && amount <= 1000000000.0f)
            return amount;

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

class Booking
{
private:
    string customerName;
    string customerPhone;
    string bookingType;
    string listingName;
    string location;
    string bookingDate;
    float totalAmount;
    float advanceAmount;
    string bookingStatus;

public:
    Booking()
    {
        totalAmount = 0;
        advanceAmount = 0;
        bookingStatus = "Not Confirmed";
    }

    void inputBooking()
    {
        cout << "\n===== TASKORA BOOKING =====\n";

        customerName = readName("Enter Customer Name: ");
        customerPhone = readPhone();

        cout << "\n1. Service Booking\n";
        cout << "2. Property Booking\n";
        cout << "3. Rental Vehicle Booking\n";

        int choice = readChoice("Enter Booking Type: ", 3);

        if (choice == 1)
        {
            bookingType = "Service";
            listingName = readText("Enter Service Name: ");
        }
        else if (choice == 2)
        {
            bookingType = "Property";
            listingName = readText("Enter Property Type: ");
        }
        else
        {
            bookingType = "Rental Vehicle";
            listingName = readText("Enter Vehicle Type: ");
        }

        location = readLocation();
        bookingDate = readText("Enter Booking Date: ");

        totalAmount = readAmount("Enter Total Amount: Rs. ");

        while (true)
        {
            advanceAmount = readAmount("Enter Advance Payment: Rs. ");

            if (advanceAmount <= totalAmount)
                break;

            cout << "Advance payment cannot exceed the total amount.\n";
        }
    }

    void displayBooking()
    {
        cout << "\n BOOKING DETAILS \n";
        cout << "Customer Name: " << customerName << endl;
        cout << "Customer Phone: " << customerPhone << endl;
        cout << "Booking Type: " << bookingType << endl;
        cout << "Listing Name: " << listingName << endl;
        cout << "Location: " << location << endl;
        cout << "Booking Date: " << bookingDate << endl;
        cout << "Total Amount: Rs. " << totalAmount << endl;
        cout << "Advance Payment: Rs. " << advanceAmount << endl;
        cout << "Remaining Amount: Rs. "
             << totalAmount - advanceAmount << endl;
        cout << "Booking Status: " << bookingStatus << endl;
    }

    float getAdvanceAmount()
    {
        return advanceAmount;
    }

    void setBookingStatus(string status)
    {
        bookingStatus = status;
    }
};

class Payment
{
private:
    float amount;
    string paymentMethod;
    string paymentStatus;

public:
    Payment()
    {
        amount = 0;
        paymentMethod = "";
        paymentStatus = "Pending";
    }

    void processPayment(float advance)
    {
        amount = advance;

        cout << "\nADVANCE PAYMENT \n";
        cout << "Advance Amount: Rs. " << amount << endl;

        cout << "1. UPI\n";
        cout << "2. Card\n";
        cout << "3. Cash\n";

        int choice = readChoice("Select Payment Method: ", 3);

        if (choice == 1)
            paymentMethod = "UPI";
        else if (choice == 2)
            paymentMethod = "Card";
        else
            paymentMethod = "Cash";

        cout << "\n1. Confirm Simulated Payment\n";
        cout << "2. Cancel Payment\n";

        int paymentChoice = readChoice("Enter Choice: ", 2);

        if (paymentChoice == 1)
            paymentStatus = "Successful (Simulated)";
        else
            paymentStatus = "Cancelled";
    }

    void displayPayment()
    {
        cout << "\n PAYMENT DETAILS \n";
        cout << "Payment Amount: Rs. " << amount << endl;
        cout << "Payment Method: " << paymentMethod << endl;
        cout << "Payment Status: " << paymentStatus << endl;
    }

    string getPaymentStatus()
    {
        return paymentStatus;
    }
};

int main()
{
    Booking booking;
    Payment payment;

    cout << "\n===== TASKORA BOOKING AND PAYMENT SYSTEM =====\n";

    booking.inputBooking();

    payment.processPayment(booking.getAdvanceAmount());

    if (payment.getPaymentStatus() == "Successful (Simulated)")
        booking.setBookingStatus("Confirmed");
    else
        booking.setBookingStatus("Payment Cancelled");

    booking.displayBooking();
    payment.displayPayment();

    return 0;
}
