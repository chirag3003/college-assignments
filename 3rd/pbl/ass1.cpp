/*
* Name: Chirag Bhalotia
* PRN: 1032232301
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_USERS = 10; 

struct MobileUser {
    long int mobileno;
    string name;
    long int billamount;

    bool operator<(const MobileUser& other) const {
        return mobileno < other.mobileno;
    }
};

class Records {
private:
    MobileUser M[MAX_USERS];
    int n;

public:
    Records(int n1) : n(n1) {}

    void accept();
    void display();
    int linearSearch(long int key);
    int binarySearchRecursive(long int key, int low, int high);
    int binarySearchIterative(long int key);
    void heapsort();
    void quickSortRecursive(int low, int high);
    void quickSortIterative();

private:
    void adjust(int n, int i);
    int partition(int low, int high);
};

void Records::accept() {
    cout << "Enter mob no, name, bill amount for " << n << " users" << endl;
    for (int i = 0; i < n; i++) {
        cin >> M[i].mobileno >> M[i].name >> M[i].billamount;
    }
}

void Records::display() {
    for (int i = 0; i < n; i++) {
        cout << "Mobile no:" << M[i].mobileno << endl;
        cout << "Name:" << M[i].name << endl;
        cout << "Bill amount:" << M[i].billamount << endl;
        cout << endl;
    }
}

int Records::linearSearch(long int key) {
    for (int i = 0; i < n; i++) {
        if (M[i].mobileno == key) {
            return i;
        }
    }
    return -1; 
}

int Records::binarySearchRecursive(long int key, int low, int high) {
    if (low > high) {
        return -1; 
    }

    int mid = low + (high - low) / 2;

    if (M[mid].mobileno == key) {
        return mid;
    } else if (M[mid].mobileno < key) {
        return binarySearchRecursive(key, mid + 1, high);
    } else {
        return binarySearchRecursive(key, low, mid - 1);
    }
}

int Records::binarySearchIterative(long int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (M[mid].mobileno == key) {
            return mid;
        } else if (M[mid].mobileno < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; 
}

void Records::adjust(int n, int i) {
    while (2 * i + 1 <= n - 1) {
        int j = 2 * i + 1;
        if ((j + 1 <= n - 1) && (M[j + 1].mobileno > M[j].mobileno)) {
            j = j + 1;
        }
        if (M[i].mobileno >= M[j].mobileno) {
            break;
        } else {
            swap(M[i], M[j]);
            i = j;
        }
    }
}

void Records::heapsort() {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        adjust(n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(M[0], M[i]);
        adjust(i, 0);
    }
}

int Records::partition(int low, int high) {
    MobileUser pivot = M[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (M[j] < pivot) {
            i++;
            swap(M[i], M[j]);
        }
    }
    swap(M[i + 1], M[high]);
    return (i + 1);
}

void Records::quickSortRecursive(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortRecursive(low, pi - 1);
        quickSortRecursive(pi + 1, high);
    }
}

void Records::quickSortIterative() {
    int stack[MAX_USERS * 2]; 
    int top = -1;

    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int high = stack[--top];
        int low = stack[--top];

        if (low < high) { 
            int pi = partition(low, high);

            if (pi - 1 > low) {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }

            if (pi + 1 < high) {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the value of n (users) " << endl;
    cin >> n;

    if (n > MAX_USERS) {
        cout << "Maximum number of users allowed is " << MAX_USERS << "." << endl;
        return 1;
    }

    Records R(n);
    R.accept();
    R.display();

    cout << "\nAfter Heap Sort:" << endl;
    R.heapsort();
    R.display();

    cout << "\nAfter Quick Sort (Recursive):" << endl;
    R.quickSortRecursive(0, n - 1);
    R.display();

    cout << "\nAfter Quick Sort (Iterative):" << endl;
    R.quickSortIterative();
    R.display();

    long int searchKey;
    cout << "Enter the mobile number to search: ";
    cin >> searchKey;

    int linearIndex = R.linearSearch(searchKey);
    if (linearIndex != -1) {
        cout << "Mobile number found at index: " << linearIndex << " (Linear Search)" << endl;
    } else {
        cout << "Mobile number not found (Linear Search)" << endl;
    }

    int binaryIndexRecursive = R.binarySearchRecursive(searchKey, 0, n - 1);
    if (binaryIndexRecursive != -1) {
        cout << "Mobile number found at index: " << binaryIndexRecursive << " (Recursive Binary Search)" << endl;
    } else {
        cout << "Mobile number not found (Recursive Binary Search)" << endl;
    }

    int binaryIndexIterative = R.binarySearchIterative(searchKey);
    if (binaryIndexIterative != -1) {
        cout << "Mobile number found at index: " << binaryIndexIterative << " (Iterative Binary Search)" << endl;
    } else {
        cout << "Mobile number not found (Iterative Binary Search)" << endl;
    }

    return 0;
}

