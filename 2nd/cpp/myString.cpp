#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class MyString
{
    string myString = "";

public:
    MyString(string str)
    {
        myString = str;
    }
    void operator~()
    {
        reverse(myString.begin(), myString.end());
    }
    MyString operator/(int d)
    {
        MyString mS("");
        int l = myString.size() / d;
        mS.myString = myString.substr(0, l);
        return (mS);
    }
    void display()
    {
        cout << myString << endl;
    }
};

int main()
{
    string str = "Hello World";
    MyString mS(str);
    MyString mS2 = mS / 2;
    mS2.display();

    cout << "Reversing the string" << endl;
    ~mS;
    mS.display();

    return 0;
}