#include <iostream>

using namespace std;

class Overload
{
public:
    void print(int i)
    {
        cout << "Printing int: " << i << endl;
    }
    void print(int i, int j)
    {
        cout << "Printing float: " << i + j << endl;
    }
    void print(float f)
    {
        cout << "Printing float: " << f << endl;
    }
};

int main()
{
    Overload overload;
    overload.print(5);
    overload.print(5, 6);
    overload.print(5.6f);
    return 0;
}