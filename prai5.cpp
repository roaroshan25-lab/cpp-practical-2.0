#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

class Student
{
public:
    string name;
    int mark = 0;
    char grade = ' ';
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
    // Get student details from the user
    int n = readInt("Enter number of students: ", 1, 1000);

    vector<Student> students;
    for (int i = 0; i < n; i++)
    {
        Student s;
        cout << "\nStudent " << i + 1 << endl;
        cout << "Enter name: ";
        getline(cin >> ws, s.name);
        s.mark = readInt("Enter mark (0-100): ", 0, 100);
        students.push_back(s);
    }

    // Sort students based on marks (highest first)
    sort(students.begin(), students.end(),
         [](const Student &a, const Student &b)
         {
             return a.mark > b.mark;
         });

    // Assign grades using transform
    transform(students.begin(), students.end(),
              students.begin(),
              [](Student s)
              {
                  if (s.mark >= 90)
                      s.grade = 'A';
                  else if (s.mark >= 75)
                      s.grade = 'B';
                  else if (s.mark >= 50)
                      s.grade = 'C';
                  else
                      s.grade = 'F';

                  return s;
              });

    // Find first student scoring above 80
    auto it = find_if(students.begin(), students.end(),
                      [](const Student &s)
                      {
                          return s.mark > 80;
                      });

    // Calculate total marks using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student &s)
                           {
                               return sum + s.mark;
                           });

    float average = (float)total / students.size();

    // Display results
    cout << "\nStudent Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";

    for (const Student &s : students)
    {
        cout << s.name << "\t"
             << s.mark << "\t"
             << s.grade << endl;
    }

    if (it != students.end())
        cout << "\nFirst student scoring above 80: " << it->name << endl;
    else
        cout << "\nNo student scored above 80." << endl;

    cout << "Total Marks: " << total << endl;
    cout << "Average Mark: " << average << endl;

    return 0;
}
