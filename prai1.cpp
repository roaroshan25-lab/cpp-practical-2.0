#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

class Shape
{
public:
    virtual float area() = 0; // Pure virtual function
};

class Circle : public Shape
{
private:
    float radius;

public:
    Circle(float r)
    {
        radius = r;
    }
    float area()
    {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape
{
private:
    float length, breadth;

public:
    Rectangle(float l, float b)
    {
        length = l;
        breadth = b;
    }
    float area()
    {
        return length * breadth;
    }
};

class Triangle : public Shape
{
private:
    float base, height;

public:
    Triangle(float b, float h)
    {
        base = b;
        height = h;
    }
    float area()
    {
        return 0.5 * base * height;
    }
};

// Reads a positive number; asks again on invalid input
float readPositive(const string &prompt)
{
    float value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value > 0)
            return value;
        if (cin.eof())
        {
            cout << "\nInput ended unexpectedly." << endl;
            exit(1);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number." << endl;
    }
}

int main()
{
    float radius, length, breadth, base, height;

    cout << "--- Circle ---" << endl;
    radius = readPositive("Enter radius: ");

    cout << "\n--- Rectangle ---" << endl;
    length = readPositive("Enter length: ");
    breadth = readPositive("Enter breadth: ");

    cout << "\n--- Triangle ---" << endl;
    base = readPositive("Enter base: ");
    height = readPositive("Enter height: ");

    Circle c(radius);
    Rectangle r(length, breadth);
    Triangle t(base, height);

    Shape *ptr;
    cout << endl;

    ptr = &c;
    cout << "Area of Circle: " << ptr->area() << endl;

    ptr = &r;
    cout << "Area of Rectangle: " << ptr->area() << endl;

    ptr = &t;
    cout << "Area of Triangle: " << ptr->area() << endl;

    return 0;
}
