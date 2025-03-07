using namespace std;
class Node
{
public:
    int data;
    Node *left, *right;
    Node(int x)
    {
        data = x;
        left = right = nullptr;
    }
};

// Iterative method to find height of Binary Tree
void printLevelOrder(Node *root)
{
    if (root == nullptr)
        return;

    // Create an empty queue for level order traversal
    queue<Node *> q;

    // Enqueue Root
    q.push(root);

    while (q.empty() == false)
    {

        // Print front of queue and remove it from queue
        Node *node = q.front();
        cout << node->data << " ";
        q.pop();

        // Enqueue left child
        if (node->left != nullptr)
            q.push(node->left);

        // Enqueue right child
        if (node->right != nullptr)
            q.push(node->right);
    }
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    printLevelOrder(root);
    return 0;
}