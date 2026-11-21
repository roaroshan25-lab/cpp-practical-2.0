#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

// Derived exception class
class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.")
    {
    }
};

// Another derived exception class
class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();
        balance += amount;
    }

    void withdraw(double amount)
    {
        // Validate first before modifying the balance
        if (amount <= 0)
            throw InvalidAmountException();
        if (amount > balance)
            throw InsufficientFundsException();
        // State changes only after all checks succeed
        balance -= amount;
    }

    void display()
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

// Reads an integer in [minValue, maxValue]; asks again on invalid input
int readInt(const string &prompt, int minValue, int maxValue)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue)
            return value;
        if (cin.eof())
        {
            cout << "\nInput ended unexpectedly." << endl;
            exit(1);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number between " << minValue
             << " and " << maxValue << "." << endl;
    }
}

// Reads any number (zero/negative allowed so the exceptions can be demonstrated)
double readDouble(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        if (cin.eof())
        {
            cout << "\nInput ended unexpectedly." << endl;
            exit(1);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number." << endl;
    }
}

int main()
{
    string name;
    double initialBalance;

    cout << "Enter account holder name: ";
    getline(cin >> ws, name);

    do
    {
        initialBalance = readDouble("Enter initial balance: Rs. ");
        if (initialBalance < 0)
            cout << "Initial balance cannot be negative." << endl;
    } while (initialBalance < 0);

    BankAccount account(name, initialBalance);

    cout << "\nInitial Account Details:" << endl;
    account.display();

    int choice;
    do
    {
        cout << "\n----- Menu -----" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display account" << endl;
        cout << "4. Exit" << endl;
        choice = readInt("Enter your choice: ", 1, 4);

        try
        {
            if (choice == 1)
            {
                double amount = readDouble("Enter amount to deposit: Rs. ");
                account.deposit(amount);
                cout << "Deposit successful." << endl;
            }
            else if (choice == 2)
            {
                double amount = readDouble("Enter amount to withdraw: Rs. ");
                account.withdraw(amount);
                cout << "Withdrawal successful." << endl;
            }
            else if (choice == 3)
            {
                account.display();
            }
        }
        catch (const InsufficientFundsException &e)
        {
            cout << e.what() << endl;
        }
        catch (const InvalidAmountException &e)
        {
            cout << e.what() << endl;
        }
        catch (const BankException &e)
        {
            cout << "Bank Exception: " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cout << "General Exception: " << e.what() << endl;
        }
    } while (choice != 4);

    cout << "\nFinal Account Details:" << endl;
    account.display();
    return 0;
}
