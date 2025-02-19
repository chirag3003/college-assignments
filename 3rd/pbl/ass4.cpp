#include "iostream"

using namespace std;

class Node {
public:
  int key = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  int height = 1;
  Node(int key) {
    this->key = key;
    this->height = 1;
  }
};

int height(Node *root) {
  if (root == nullptr) {
    return 0;
  }
  return root->height;
}

Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = 1 + max(height(y->left), height(y->right));
  x->height = 1 + max(height(x->left), height(x->right));

  // Return new root
  return x;
}

Node *leftRotate(Node *y) {
  Node *x = y->right;
  Node *T2 = x->left;

  // Perform rotation
  x->left = y;
  y->right = T2;

  // Update heights
  y->height = 1 + max(height(y->left), height(y->right));
  x->height = 1 + max(height(x->left), height(x->right));

  // Return new root
  return x;
}

int getBalance(Node *N) {
  if (N == nullptr)
    return 0;
  return height(N->left) - height(N->right);
}

Node *insert(Node *root, int key) {
  if (root == nullptr) {
    root = new Node(key);
  } else {
    if (key < root->key) {
      root->left = insert(root->left, key);
    } else if (key > root->key) {
      root->right = insert(root->right, key);
    } else {
      return root;
    }
  }
  root->height = 1 + max(height(root->left),
                           height(root->right)); 

  int balance = getBalance(root);

  if (balance > 1 && key < root->left->key)
    return rightRotate(root);

  // Right Right Case
  if (balance < -1 && key > root->right->key)
    return leftRotate(root);

  // Left Right Case
  if (balance > 1 && key > root->left->key) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // Right Left Case
  if (balance < -1 && key < root->right->key) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void preOrder(Node *root) { 
    if (root != nullptr) { 
        cout << root->key << " "; 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

// Driver Code 
int main() { 
    Node *root = nullptr; 
    
    // Constructing tree given in the above figure 
    root = insert(root, 10); 
    root = insert(root, 20); 
    root = insert(root, 30); 
    root = insert(root, 40); 
    root = insert(root, 50); 
    root = insert(root, 25); 
    
    /* The constructed AVL Tree would be 
              30 
            /   \ 
          20     40 
         /  \      \ 
       10   25     50 
    */
    cout << "Preorder traversal : \n"; 
    preOrder(root); 
    
    return 0; 
}
