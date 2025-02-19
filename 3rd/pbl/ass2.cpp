/*
*  Name: Chirag Bhalotia
*  PRN: 1032232301
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

class node 
{
    string name;
    int id;
    node* next;
    friend class graph;
};

class graph 
{
    node* head[20]; // Array of adjacency lists
    int n;          // Number of vertices

public:
    graph();
    void createGraph();
    void displayGraph();
    void recursiveDFS(int start, bool visited[]);
    void nonRecursiveDFS(int start);
};

// Constructor to initialize the graph
graph::graph() 
{
    n = 0;
    for (int i = 0; i < 20; i++) 
    {
        head[i] = nullptr;
    }
}

// Function to create a graph
void graph::createGraph() 
{
    cout << "Enter the number of vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++) 
    {
        head[i] = new node;
        cout << "Enter the name for vertex " << i << ": ";
        cin >> head[i]->name;
        head[i]->id = i;
        head[i]->next = nullptr;

        int edges;
        cout << "Enter the number of edges for vertex " << head[i]->name << ": ";
        cin >> edges;

        node* temp = head[i];
        for (int j = 0; j < edges; j++) 
        {
            node* newNode = new node;
            cout << "Enter the name of the connected vertex: ";
            cin >> newNode->name;
            cout << "Enter the ID of the connected vertex: ";
            cin >> newNode->id;
            newNode->next = nullptr;
            temp->next = newNode;
            temp = newNode;
        }
    }
}

// Function to display the graph
void graph::displayGraph() 
{
    cout << "\nAdjacency List Representation of the Graph:\n";
    for (int i = 0; i < n; i++) 
    {
        node* temp = head[i];
        cout << temp->name << " (" << temp->id << ") -> ";
        temp = temp->next;
        while (temp != nullptr) 
        {
            cout << temp->name << " (" << temp->id << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

// Recursive DFS function
void graph::recursiveDFS(int start, bool visited[]) 
{
    cout << head[start]->name << " -> ";
    visited[start] = true;

    node* temp = head[start]->next;
    while (temp != nullptr) 
    {
        if (!visited[temp->id]) 
        {
            recursiveDFS(temp->id, visited);
        }
        temp = temp->next;
    }
}

// Non-recursive DFS function
void graph::nonRecursiveDFS(int start) 
{
    bool visited[20] = { false };
    stack<int> s;

    s.push(start);
    while (!s.empty()) 
    {
        int current = s.top();
        s.pop();

        if (!visited[current]) 
        {
            cout << head[current]->name << " -> ";
            visited[current] = true;
        }

        node* temp = head[current]->next;
        while (temp != nullptr) 
        {
            if (!visited[temp->id]) 
            {
                s.push(temp->id);
            }
            temp = temp->next;
        }
    }
}

int main() 
{
    graph g;
    int choice;

    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Graph\n";
        cout << "3. Recursive DFS\n";
        cout << "4. Non-Recursive DFS\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            g.createGraph();
            break;

        case 2:
            g.displayGraph();
            break;

        case 3: 
            {
            bool visited[20] = { false };
            int startVertex;
            cout << "Enter the starting vertex ID for recursive DFS: ";
            cin >> startVertex;
            cout << "Recursive DFS Traversal:\n";
            g.recursiveDFS(startVertex, visited);
            cout << endl;
            break;
        }

        case 4: 
            {
            int startVertex;
            cout << "Enter the starting vertex ID for non-recursive DFS: ";
            cin >> startVertex;
            cout << "Non-Recursive DFS Traversal:\n";
            g.nonRecursiveDFS(startVertex);
            cout << endl;
            break;
        }

        case 5:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
