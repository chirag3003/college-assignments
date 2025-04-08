#include <iostream>

using namespace std;

// Class to store information about each item
class ItemInfo {
public:
  int weight;
  int profit;

private:
  friend class Knapsack;
};

// Class to implement the Knapsack problem
class Knapsack {
public:
  ItemInfo items[100]; // Array to store items
  int profitTable[100][100]; // DP table to store maximum profit
  int selectedItems[100]; // Array to store selected items
  int capacity; // Capacity of the knapsack

  // Function to accept input for items and knapsack capacity
  void acceptInput(int itemCount) {
    cout << "Please enter the capacity of the knapsack:" << endl;
    cin >> capacity;
    for (int i = 0; i < itemCount; i++) {
      cout << "Please enter the profit and the weight of the " << i
           << "th item:" << endl;
      cin >> items[i].profit >> items[i].weight;
    }
  }

  // Function to calculate the maximum profit using dynamic programming
  int calculateMaxProfit(int itemCount) {
    // Initialize the profit table
    for (int w = 0; w <= capacity; w++) {
      profitTable[0][w] = 0;
    }
    for (int i = 1; i <= itemCount; i++) {
      profitTable[i][0] = 0;
    }

    // Fill the profit table
    for (int i = 1; i <= itemCount; i++) {
      for (int w = 0; w <= capacity; w++) {
        if (items[i - 1].weight <= w) {
          profitTable[i][w] = max(items[i - 1].profit + profitTable[i - 1][w - items[i - 1].weight], profitTable[i - 1][w]);
        } else {
          profitTable[i][w] = profitTable[i - 1][w];
        }
      }
    }
    return profitTable[itemCount][capacity];
  }

  // Function to backtrack and find the selected items
  int *findSelectedItems(int itemCount) {
    for (int i = 0; i < itemCount; i++) {
      selectedItems[i] = 0;
    }
    int remainingCapacity = capacity;
    for (int i = itemCount; i > 0; i--) {
      if (profitTable[i][remainingCapacity] != profitTable[i - 1][remainingCapacity]) {
        selectedItems[i - 1] = 1;
        remainingCapacity -= items[i - 1].weight;
      }
    }
    return selectedItems;
  }
};

int main() {
  int itemCount;
  cout << "Please enter the number of items:";
  cin >> itemCount;
  Knapsack knapsack;
  knapsack.acceptInput(itemCount);
  cout << "Maximum Profit: " << knapsack.calculateMaxProfit(itemCount) << endl;
  int *selectedItems = knapsack.findSelectedItems(itemCount);
  cout << "Selected Items: [";
  for (int i = 0; i < itemCount; i++) {
    if (i != itemCount - 1) {
      cout << "w" << i << ",";
    } else {
      cout << "w" << i;
    }
  }
  cout << "] = [";
  for (int i = 0; i < itemCount; i++) {
    if (i != itemCount - 1) {
      cout << selectedItems[i] << ",";
    } else {
      cout << selectedItems[i];
    }
  }
  cout << "]";
}

