#include <bits/stdc++.h>

using namespace std;

class graph {
  int cost[10][10];

public:
  int cities;
  graph() {
    cout << "Enter the number of cities: ";
    cin >> cities;

    for (int i = 0; i < cities; i++) {
      for (int j = 0; j < cities; j++) {
        cost[i][j] = 999;
      }
    }
  }
  void create();
  void display();
  int prims_algo(int st);
};

void graph::create() {
  char ch;

  for (int i = 0; i < cities; i++) {
    for (int j = i + 1; j < cities; j++) {
      cout << "Is there a connection between " << i << " and " << j
           << "? (y/n): ";
      cin >> ch;
      if (ch == 'y') {
        cout << "Enter the cost of edge: ";
        cin >> cost[i][j];
        cost[j][i] = cost[i][j];
      }
    }
  }
}

void graph::display() {
  cout << "Adjacency Matrix:\n";
  for (int i = 0; i < cities; i++) {
    for (int j = 0; j < cities; j++) {
      if (cost[i][j] == 999)
        cout << " ∞ "; // printing infinity for non-connected vertices
      else
        cout << " " << cost[i][j] << " ";
    }
    cout << endl;
  }
}

int graph::prims_algo(int st) {
  int min = 999, min_idx;
  int weight = 0;
  int vertex = st;
  bool visited[cities];
  for (int i = 0; i < cities; i++)
    visited[i] = false;

  visited[st] = true;
  min_idx = st;
  bool visitedAll = false;

  while (!visitedAll) {
    visitedAll = true;
    for (int i = 0; i < cities; i++) {
      if (visited[i] == false && cost[vertex][i] < min) {
        min = cost[vertex][i];
        min_idx = i;
        visitedAll = false;
      }
    }
    vertex = min_idx;
    visited[vertex] = true;
    if (!visitedAll)
      weight += min;
    min = 999;
    /*cout << vertex << " -> " << min_idx << " (" << min << ")" << endl;*/
  }

  return weight;
}

int main() {
  graph g;
  int choice, st;

  do {
    cout << "\nMenu:\n";
    cout << "1. Create Graph\n";
    cout << "2. Display Graph\n";
    cout << "3. Find Minimum Spanning Tree (Prim’s Algorithm)\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      g.create();
      break;
    case 2:
      g.display();
      break;
    case 3:
      cout << "Enter the starting vertex (0 to " << g.cities - 1 << "): ";
      cin >> st;
      if (st < 0 || st >= g.cities)
        cout << "Error: Invalid vertex.\n";
      else
        cout << g.prims_algo(st);
      break;
    case 4:
      cout << "Exiting the program.\n";
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 4);

  return 0;
}
