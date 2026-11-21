#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

// Resource class
class Resource
{
private:
    string name;

public:
    Resource(string n)
    {
        name = n;
        cout << "Resource '" << name << "' acquired" << endl;
    }
    ~Resource()
    {
        cout << "Resource '" << name << "' released" << endl;
    }
    void use()
    {
        cout << "Resource '" << name << "' is being used" << endl;
    }
};

// Manual Smart Pointer using RAII
class MySmartPointer
{
private:
    Resource *ptr;

public:
    MySmartPointer(Resource *p)
    {
        ptr = p;
    }
    ~MySmartPointer()
    {
        delete ptr;
        cout << "Manual smart pointer destroyed" << endl;
    }
    Resource *operator->()
    {
        return ptr;
    }

    // Disable copying to avoid double deletion
    MySmartPointer(const MySmartPointer &) = delete;
    MySmartPointer &operator=(const MySmartPointer &) = delete;
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
        cout << "Invalid input. Enter a number between " << minValue
             << " and " << maxValue << "." << endl;
    }
}

int main()
{
    string resourceName;
    cout << "Enter resource name: ";
    getline(cin >> ws, resourceName);

    int uses = readInt("How many times should the resource be used? ", 1, 100);
    int extraOwners = readInt("How many extra shared_ptr copies to create? ", 0, 100);

    cout << "\n----- Manual RAII Smart Pointer -----" << endl;
    {
        MySmartPointer smartPtr(new Resource(resourceName));
        for (int i = 0; i < uses; i++)
            smartPtr->use();
    }

    cout << "\n----- unique_ptr -----" << endl;
    {
        unique_ptr<Resource> uniquePtr = make_unique<Resource>(resourceName);
        for (int i = 0; i < uses; i++)
            uniquePtr->use();
    }

    cout << "\n----- shared_ptr -----" << endl;
    {
        shared_ptr<Resource> sharedPtr1 = make_shared<Resource>(resourceName);

        // Create the extra owners requested by the user
        vector<shared_ptr<Resource>> owners;
        for (int i = 0; i < extraOwners; i++)
            owners.push_back(sharedPtr1);

        for (int i = 0; i < uses; i++)
            sharedPtr1->use();

        cout << "Shared Pointer Count: " << sharedPtr1.use_count() << endl;
    }

    cout << "\nProgram completed successfully." << endl;
    return 0;
}
