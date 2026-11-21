#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;

public:
    Student(int r, string n)
    {
        rollNo = r;
        name = n;
        cout << "Student object created" << endl;
    }

    void display()
    {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
    }

    // Destructor
    ~Student()
    {
        cout << "Student object destroyed" << endl;
    }
};

// Reads an integer in [minValue, maxValue]; asks again on invalid input
int readInt(const string &prompt, int minValue = 1,
            int maxValue = numeric_limits<int>::max())
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
        cout << "Invalid input. Please try again." << endl;
    }
}

int main()
{
    int rollNo;
    string name;

    rollNo = readInt("Enter roll number: ");

    cout << "Enter name: ";
    getline(cin >> ws, name);   // 'ws' skips the leftover newline

    cout << endl;
    Student s1(rollNo, name);
    s1.display();
    return 0;
}
