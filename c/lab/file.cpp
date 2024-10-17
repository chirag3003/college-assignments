#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printMenu();

class File
{
    string filename;
    fstream file;

public:
    File(string filename) : filename(filename)
    {
        file.open(filename, ios::in | ios::out | ios::app);
        if (!file.is_open())
        {
            cerr << "Unable to open file " << filename << endl;
        }
    }
    ~File()
    {
        file.close();
    }
    void write(string line)
    {
        file.clear();            // Clear any error flags
        file.seekp(0, ios::end); // Move the cursor to the end of the file
        file.write(line.c_str(), line.size());
        file.flush(); // Ensure the data is written to the file
    }
    void read()
    {
        file.clear();            // Clear any error flags
        file.seekg(0, ios::beg); // Move the cursor to the beginning of the file
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
    void copyToFile(string filename2)
    {
        fstream file2(filename2, ios::out | ios::app);

        file.clear();            // Clear any error flags
        file.seekg(0, ios::beg); // Move the cursor to the beginning of the file
        string line;
        file2.seekp(0, ios::end); // Move the cursor to the end of the file
        while (getline(file, line))
        {
            line += '\n';
            file2.write(line.c_str(), line.size());
            file2.flush();
        }
        file2.close();
    }
    void read(int pos)
    {
        file.clear();
        file.seekg(pos, ios::beg);
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }
    void deleteFile()
    {
        file.close();
        remove(filename.c_str());
    }
};

int main()
{
    string userFilename;
    cout << "Enter the filename: ";
    cin >> userFilename;
    File file(userFilename);
    // file.read();
    // file.write("\nHello2 World");
    // file.read();
    // file.copyToFile("file2.txt");
    // file.deleteFile();
    while (true)
    {
        printMenu();
        int choice;
        cin >> choice;
        string line;
        string filename2;
        int pos;
        switch (choice)
        {
        case 1:
            file.read();
            break;
        case 2:
            cout << "Enter the line to write: ";
            cin.ignore(); 
            getline(cin, line);
            file.write(line);
            break;
        case 3:
            cout << "Enter the filename to copy to: ";
            cin >> filename2;
            file.copyToFile(filename2);
            break;
        case 4:
            cout << "Enter the position to read from: ";
            cin >> pos;
            file.read(pos);
            break;
        case 5:
            file.deleteFile();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
    return 0;
}

void printMenu()
{
    cout << "1. Read file" << endl;
    cout << "2. Write to file" << endl;
    cout << "3. Copy to file" << endl;
    cout << "4. Read from position" << endl;
    cout << "5. Delete file" << endl;
    cout << "6. Exit" << endl;
}
