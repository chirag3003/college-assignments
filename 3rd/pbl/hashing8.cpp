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
  HashTable(int size) : size(size), inUse(0) {
    table.resize(size);
  }

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
    int tried  = 0;
    while (table[index] != NULL && tried != size){
      index = (index + 1) % size;
      tried++;
    }
    // Inserting the key and value
    table[index] = new HashTableValue(key, value);
  }

  HashTableValue* search(int key) {
    int index = key % size;
    int tried = 0;
    while(table[index] == NULL || (table[index]->key != key && tried != size)){
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
      cout << "(" << table[i]->key << ", " << table[i]->value << ") ";
    }
    cout << endl;
  }

private:
  int size;
  int inUse;
  vector<HashTableValue*> table;
};

int main() {
  HashTable ht(10);
  ht.insert(1, 10);
  ht.insert(11, 20);
  ht.insert(31, 30);
  ht.insert(12, 40);
  ht.insert(23, 50);
  ht.insert(43, 60);
  ht.insert(32, 70);
  ht.insert(8, 80);
  ht.insert(9, 90);
  ht.insert(10, 100);
  ht.insert(12, 100);
  ht.print();
  if(ht.search(10) != NULL) {
    cout << ht.search(10)->value << endl;
  }
  return 0;
}

