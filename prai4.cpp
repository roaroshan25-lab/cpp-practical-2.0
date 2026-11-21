#include <iostream>
#include <stack>
#include <queue>
#include <chrono>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;
using namespace chrono;

// Capacity is now chosen at run time, so the array is allocated dynamically
template <class T>
class MyStack
{
private:
    T *data;
    int top;
    int capacity;

public:
    MyStack(int size)
    {
        capacity = size;
        data = new T[capacity];
        top = -1;
    }
    ~MyStack()
    {
        delete[] data;
    }
    MyStack(const MyStack &) = delete;
    MyStack &operator=(const MyStack &) = delete;

    void push(T value)
    {
        if (top < capacity - 1)
            data[++top] = value;
    }
    void pop()
    {
        if (top >= 0)
            top--;
    }
};

template <class T>
class MyQueue
{
private:
    T *data;
    int front, rear;
    int capacity;

public:
    MyQueue(int size)
    {
        capacity = size;
        data = new T[capacity];
        front = 0;
        rear = -1;
    }
    ~MyQueue()
    {
        delete[] data;
    }
    MyQueue(const MyQueue &) = delete;
    MyQueue &operator=(const MyQueue &) = delete;

    void enqueue(T value)
    {
        if (rear < capacity - 1)
            data[++rear] = value;
    }
    void dequeue()
    {
        if (front <= rear)
            front++;
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
    int N = readInt("Enter number of elements (N) to push/pop: ");

    // Custom Stack Benchmark
    auto start = high_resolution_clock::now();
    MyStack<int> myStack(N);
    for (int i = 0; i < N; i++)
        myStack.push(i);
    for (int i = 0; i < N; i++)
        myStack.pop();
    auto end = high_resolution_clock::now();
    auto customStackTime = duration_cast<microseconds>(end - start);

    // STL Stack Benchmark
    start = high_resolution_clock::now();
    stack<int> stlStack;
    for (int i = 0; i < N; i++)
        stlStack.push(i);
    for (int i = 0; i < N; i++)
        stlStack.pop();
    end = high_resolution_clock::now();
    auto stlStackTime = duration_cast<microseconds>(end - start);

    // Custom Queue Benchmark
    start = high_resolution_clock::now();
    MyQueue<int> myQueue(N);
    for (int i = 0; i < N; i++)
        myQueue.enqueue(i);
    for (int i = 0; i < N; i++)
        myQueue.dequeue();
    end = high_resolution_clock::now();
    auto customQueueTime = duration_cast<microseconds>(end - start);

    // STL Queue Benchmark
    start = high_resolution_clock::now();
    queue<int> stlQueue;
    for (int i = 0; i < N; i++)
        stlQueue.push(i);
    for (int i = 0; i < N; i++)
        stlQueue.pop();
    end = high_resolution_clock::now();
    auto stlQueueTime = duration_cast<microseconds>(end - start);

    cout << "\nResults for N = " << N << endl;
    cout << "Custom Stack Time: " << customStackTime.count() << " microseconds" << endl;
    cout << "STL Stack Time: " << stlStackTime.count() << " microseconds" << endl;
    cout << "Custom Queue Time: " << customQueueTime.count() << " microseconds" << endl;
    cout << "STL Queue Time: " << stlQueueTime.count() << " microseconds" << endl;
    return 0;
}
