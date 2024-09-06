#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Function to print menu
void printMenu()
{
    cout << "1. Add Student" << endl;
    cout << "2. Display Student" << endl;
    cout << "3. Exit" << endl;
}

// Student class
class Student
{
private:
    string name;
    int rollNumber;
    string studentClass;
    char division;
    string dateOfBirth;
    string aadharNumber;
    string bloodGroup;
    string contactAddress;
    string telephoneNumber;

    static int count;

public:
    // Constructor to initialize student data
    Student(string n, int roll, string cls, char div, string dob, string aadhar, string blood, string address, string phone)
    {
        name = n;
        rollNumber = roll;
        studentClass = cls;
        division = div;
        dateOfBirth = dob;
        aadharNumber = aadhar;
        bloodGroup = blood;
        contactAddress = address;
        telephoneNumber = phone;
        count++;
    }

    // Destructor
    ~Student()
    {
        count--;
    }

    // Static function to display student information
    static void displayStudentInfo(Student student)
    {
        cout << "Name: " << student.name << endl;
        cout << "Roll Number: " << student.rollNumber << endl;
        cout << "Class: " << student.studentClass << endl;
        cout << "Division: " << student.division << endl;
        cout << "Date of Birth: " << student.dateOfBirth << endl;
        cout << "Aadhar Number: " << student.aadharNumber << endl;
        cout << "Blood Group: " << student.bloodGroup << endl;
        cout << "Contact Address: " << student.contactAddress << endl;
        cout << "Telephone Number: " << student.telephoneNumber << endl;
    }
    // Static function to get the count of students
    static int getCount()
    {
        return count;
    }
};

// Initialize static member
int Student::count = 0;

int main()
{
    // Creating student objects
    Student student1("John Doe", 1, "10th", 'A', "01-01-2005", "123456789012", "O+", "123 Main St", "1234567890");
    Student student2("Jane Smith", 2, "10th", 'B', "02-02-2005", "987654321098", "A+", "456 Elm St", "0987654321");

    // Display student information
    cout << "Student 1 Information:" << endl;
    Student::displayStudentInfo(student1);
    cout << endl;

    cout << "Student 2 Information:" << endl;
    Student::displayStudentInfo(student2);
    cout << endl;

    // Display the count of students
    cout << "Total number of students: " << Student::getCount() << endl;

    // variables to accept user input
    Student *student;
    string name;
    int rollNumber;
    string studentClass;
    char division;
    string dateOfBirth;
    string aadharNumber;
    string bloodGroup;
    string contactAddress;
    string telephoneNumber;
    while (1)
    {
        int choice;
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            // Accepting user input
            cout << "Accepting Student" << endl;

            cout << "Enter name: ";
            cin >> name;
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter class: ";
            cin >> studentClass;
            cout << "Enter division: ";
            cin >> division;
            cout << "Enter date of birth: ";
            cin >> dateOfBirth;
            cout << "Enter aadhar number: ";
            cin >> aadharNumber;
            cout << "Enter blood group: ";
            cin >> bloodGroup;
            cout << "Enter contact address: ";
            cin >> contactAddress;
            cout << "Enter telephone number: ";
            cin >> telephoneNumber;

            student = new Student(name, rollNumber, studentClass, division, dateOfBirth, aadharNumber, bloodGroup, contactAddress, telephoneNumber);
            break;
        case 2:
            cout << "\n\nDisplaying Student:\n"
                 << endl;
            if (student != NULL)
            {
                Student::displayStudentInfo(*student);
                cout << " \n\n"
                     << endl;
            }
            else
            {
                cout << "No student data available" << endl;
            }
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
