#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Rectangle

{
    int length, breadth;

public:
    Rectangle()
    {
        length = 0;
        breadth = 0;
    }
    Rectangle(int l, int b)
    {
        length = l;
        breadth = b;
    }
    Rectangle operator+(Rectangle rec)
    {
        Rectangle R;
        R.length = length + rec.length;
        R.breadth = breadth + rec.breadth;

        return (R);
    }
    void display(void);
};
void Rectangle ::display(void)
{
    cout << "\n Length = " << length;
    cout << "\n Breadth = " << breadth;
    cout << endl;
}


int main()
{
    Rectangle R1, R2, R3;
    R1 = Rectangle(2, 5);
    R2 = Rectangle(3, 4);
    R3 = R1 + R2;

    cout << "\n Rectangle:1 : ";
    R1.display();
    cout
        << "\n Rectangle:2 : ";
    R2.display();
    cout
        << "\n Rectangle:3 : ";
    R3.display();
    cout << endl;
}