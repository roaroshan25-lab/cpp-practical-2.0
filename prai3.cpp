#include <iostream>
#include <cassert>
using namespace std;

class Matrix
{
private:
    int data[2][2];

public:
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0)
    {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    // Operator +
    Matrix operator+(const Matrix &m)
    {
        Matrix result;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + m.data[i][j];
        return result;
    }

    // Operator *
    Matrix operator*(const Matrix &m)
    {
        Matrix result;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                result.data[i][j] = 0;
                for (int k = 0; k < 2; k++)
                    result.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
        return result;
    }

    // Operator []
    int *operator[](int index)
    {
        return data[index];
    }

    // Operator <<
    friend ostream &operator<<(ostream &out, const Matrix &m)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                out << m.data[i][j] << " ";
            out << endl;
        }
        return out;
    }

    // Operator >>  (reads 4 integers, row by row)
    friend istream &operator>>(istream &in, Matrix &m)
    {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                in >> m.data[i][j];
        return in;
    }
};

int main()
{
    Matrix A, B;

    cout << "Enter 4 elements of Matrix A (row by row): ";
    if (!(cin >> A))
    {
        cout << "Invalid input. Please enter integers only." << endl;
        return 1;
    }

    cout << "Enter 4 elements of Matrix B (row by row): ";
    if (!(cin >> B))
    {
        cout << "Invalid input. Please enter integers only." << endl;
        return 1;
    }

    Matrix sum = A + B;
    Matrix product = A * B;

    // Unit Tests (expected values are worked out directly from the input)
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            assert(sum[i][j] == A[i][j] + B[i][j]);

    assert(product[0][0] == A[0][0] * B[0][0] + A[0][1] * B[1][0]);
    assert(product[0][1] == A[0][0] * B[0][1] + A[0][1] * B[1][1]);
    assert(product[1][0] == A[1][0] * B[0][0] + A[1][1] * B[1][0]);
    assert(product[1][1] == A[1][0] * B[0][1] + A[1][1] * B[1][1]);

    cout << "\nMatrix A:" << endl;
    cout << A;
    cout << "Matrix B:" << endl;
    cout << B;
    cout << "Addition of Matrices:" << endl;
    cout << sum;
    cout << "Multiplication of Matrices:" << endl;
    cout << product;
    cout << "All unit tests passed successfully." << endl;
    return 0;
}
