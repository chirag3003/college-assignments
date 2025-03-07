#include <string>
#include <iostream>

using namespace std;

class complex
{
    float real;
    float imag;

public:
    complex() {}
    complex(float x, float y)
    {
        real = x;
        imag = y;
    }
    friend complex operator+(complex c1, complex c2);
    void display(void);
};

// void display(complex ca)
// {
//     cout << ca.real << " + j " << ca.imag << " \n";
// }

complex operator+(complex ca, complex cb)
{
    complex tmp;
    tmp.real = ca.real + cb.real;
    tmp.imag = ca.imag + cb.imag;
    return tmp;
}

void complex::display(void)
{
    cout << real << " + imag " << imag << " \n";
}

int main()
{
    complex c1(2.5, 3.5), c2(1.6, 2.7), c3;
    c3 = c1 + c2;
    cout << "c1 = ";
    c1.display();
    cout << "c2 = ";
    c2.display();
    cout << "c3 = ";
    c3.display();
    return 0;
}