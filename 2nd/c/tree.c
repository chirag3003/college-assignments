/*
    Nmae: Chirag Bhalotia
    PRN: 1032232301
    Panel: F
    Roll: 48
    Problem: Implement trees and its functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode {
  char data[10];
  struct treeNode *left;
  struct treeNode *right;
};

struct treeNode *stack[100];
int top = -1;

struct treeNode *queue[100];
int front = -1;
int rear = -1;

void push(struct treeNode *node) { stack[++top] = node; }

struct treeNode *pop() { return stack[top--]; }

struct treeNode *createNode(char *data) {
  struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
  strcpy(newNode->data, data);
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void printMenu() {
  printf("\nMenu:\n");
  printf("1. Insert\n");
  printf("2. Insert custom\n");
  printf("3. Display InOrder\n");
  printf("4. Display PreOrder\n");
  printf("5. Display PostOrder\n");
  printf("6. Delete Node\n");
  printf("7. Exit\n");
  printf("Enter your choice: ");
}

void printInsertMenu() {
  printf("\nMenu:\n");
  printf("1. Insert Left\n");
  printf("2. Insert Right\n");
  printf("Enter your choice: ");
}

void insert(struct treeNode *root, char *data) {
  if (strcmp(data, root->data) < 0) {
    if (root->left == NULL) {
      root->left = createNode(data);
    } else {
      insert(root->left, data);
    }
  } else {
    if (root->right == NULL) {
      root->right = createNode(data);
    } else {
      insert(root->right, data);
    }
  }
}

void deleteNode(struct treeNode *root) {
  printf("Enter node to be deleted");
  char data[10];
  scanf("%s", data);
  struct treeNode *current = root;
  struct treeNode *prev = NULL;
  while (current != NULL) {
    int cmp = strcmp(data, current->data);
    if (cmp < 0) {
      prev = current;
      current = current->left;
    } else if (cmp > 0) {
      prev = current;
      current = current->right;
    } else {
      break;
    }
  }
  if (current == NULL) {
    printf("Node not found\n");
    return;
  }
  if (current->left == NULL && current->right != NULL) {
    if (prev->left == current) {
      prev->left = current->right;
    } else {
      prev->right = current->right;
    }
    free(current);
  } else if (current->left != NULL && current->right == NULL) {
    if (prev->left == current) {
      prev->left = current->left;
    } else {
      prev->right = current->right;
    }
    free(current);
  } else if (current->left == NULL && current->right == NULL) {
    if (prev->left == current) {
      prev->left = NULL;
    } else {
      prev->right = NULL;
    }
    free(current);
  } else {
    struct treeNode *temp = current->right;
    while (temp->left != NULL) {
      temp = temp->left;
    }
    temp->left = current->left;
    if (prev->left == current) {
      prev->left = current->right;
    } else {
      prev->right = current->right;
    }
    free(current);
  }
}

void insertCustom(struct treeNode *root) {
  printf("Current Value: %s\n", root->data);
  printInsertMenu();
  int choice;
  scanf("%d", &choice);
  switch (choice) {
  case 1:
    if (root->left == NULL) {
      char data[10];
      printf("Enter data: ");
      scanf("%s", data);
      root->left = createNode(data);
    } else {
      insertCustom(root->left);
    }

    break;
  case 2:
    if (root->right == NULL) {
      char data[10];
      printf("Enter data: ");
      scanf("%s", data);
      root->right = createNode(data);
    } else {
      insertCustom(root->right);
    }
    break;
  default:
    break;
  }
}

void traverseInOrder(struct treeNode *root) {
  if (root == NULL)
    return;
  traverseInOrder(root->left);
  printf("%s ", root->data);
  traverseInOrder(root->right);
}

void inOrder(struct treeNode *root) {
  top = -1;
  struct treeNode *current = root;
  while (1) {
    while (current != NULL) {
      push(current);
      current = current->left;
    }
    if (top == -1)
      break;
    current = pop();
    printf("%s ", current->data);
    current = current->right;
  }
}

void traversePreOrder(struct treeNode *root) {
  if (root == NULL)
    return;
  printf("%s ", root->data);
  traversePreOrder(root->left);
  traversePreOrder(root->right);
}

void preOrder(struct treeNode *root) {
  top = -1;
  struct treeNode *current = root;
  while (1) {
    while (current != NULL) {
      printf("%s ", current->data);
      push(current);
      current = current->left;
    }
    if (top == -1)
      break;
    current = pop();
    current = current->right;
  }
}

void traversePostOrder(struct treeNode *root) {
  if (root == NULL)
    return;
  traversePostOrder(root->left);
  traversePostOrder(root->right);
  printf("%s ", root->data);
}

void postOrder(struct treeNode *root) {
  top = -1;
  struct treeNode *current = root;
  struct treeNode *prev = NULL;
  do {
    while (current != NULL) {
      push(current);
      current = current->left;
    }
    while (current == NULL && top != -1) {
      current = pop();
      if (current->right == NULL || current->right == prev) {
        printf("%s ", current->data);
        prev = current;
        current = NULL;
      } else {
        push(current);
        current = current->right;
      }
    }
  } while (top != -1);
}

void depthFirst(struct treeNode *root) {
  top = -1;
  struct treeNode *current = root;
  while (1) {
    while (current != NULL) {
      push(current);
      current = current->left;
    }
    if (top == -1)
      break;
    current = pop();
    printf("%s ", current->data);
    current = current->right;
  }
}

void breadthFirst(struct treeNode *root) {
  struct treeNode *current = root;
  queue[++rear] = current;
  while (rear != front) {
    current = queue[++front];
    printf("%s ", current->data);
    if (current->left != NULL) {
      queue[++rear] = current->left;
    }
    if (current->right != NULL) {
      queue[++rear] = current->right;
    }
  }
}

int main() {
  struct treeNode root;
  root.data[0] = '\0';
  root.left = NULL;
  root.right = NULL;
  while (1) {
    printMenu();
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      if (root.data[0] == '\0') {
        printf("Enter data: ");
        scanf("%s", root.data);
      } else {
        char data[10];
        printf("Enter data: ");
        scanf("%s", data);
        insert(&root, data);
      }
      break;
    case 2:
      insertCustom(&root);
      break;
    case 3:
      inOrder(&root);
      break;
    case 4:
      preOrder(&root);
      break;
    case 5:
      postOrder(&root);
      break;
    case 6:
      deleteNode(&root);
    case 7:
      exit(0);
      break;
    case 8:
      depthFirst(&root);
      break;
    case 9:
      breadthFirst(&root);
      break;
    default:
      exit(0);
    }
  }

  return 0;
}
