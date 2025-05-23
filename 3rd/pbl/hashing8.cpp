#include <iostream>
#include <vector>

using namespace std;

#include <iostream>
#include <vector>

using namespace std;

class HashTableValue {
public:
  int key;
  int value;
  HashTableValue(int k, int v) : key(k), value(v) {}
};

class HashTable {
public:
  HashTable(int size) : size(size), inUse(0) { table.resize(size); }

  void insert(int key, int value) {
    // Checking if the table is full
    if (inUse == size) {
      cout << "Table is full" << endl;
      cout << "Error when inserting " << key << " " << value << endl;
      return;
    }

    // Finding the index of the key
    int index = key % size;
    inUse++;
    int tried = 0;
    while (table[index] != NULL && tried != size) {
      index = (index + 1) % size;
      tried++;
    }
    // Inserting the key and value
    table[index] = new HashTableValue(key, value);
  }

  HashTableValue *search(int key) {
    int index = key % size;
    int tried = 0;
    while (table[index] == NULL ||
           (table[index]->key != key && tried != size)) {
      tried++;
      index = (index + 1) % size;
    }
    if (table[index]->key == key) {
      return table[index];
    }
    return NULL; // or some indication that the key was not found
  }

  void print() {
    for (int i = 0; i < size; i++) {
      if (table[i] != NULL)
        cout << "(" << table[i]->key << ", " << table[i]->value << ") ";
    }
    cout << endl;
  }

private:
  int size;
  int inUse;
  vector<HashTableValue *> table;
};

int main() {
  HashTable ht(10);
  int choice, key, value;
  do {
    cout << "Menu:\n1. Insert\n2. Search\n3. Print\n4. Exit\nEnter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1:
        cout << "Enter key and value to insert: ";
        cin >> key >> value;
        ht.insert(key, value);
        break;
      case 2:
        cout << "Enter key to search: ";
        cin >> key;
        if (ht.search(key) != NULL) {
          cout << "Value: " << ht.search(key)->value << endl;
        } else {
          cout << "Key not found" << endl;
        }
        break;
      case 3:
        ht.print();
        break;
      case 4:
        cout << "Exiting..." << endl;
        break;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 4);
  return 0;
}
