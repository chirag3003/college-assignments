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

struct treeNode
{
    char key[10];
    char value[100];
    struct treeNode *left;
    struct treeNode *right;
};

struct treeNode *stack[100];
int top = -1;

void push(struct treeNode *node)
{
    stack[++top] = node;
}

struct treeNode *pop()
{
    return stack[top--];
}

struct treeNode *createNode(char *key, char *value)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printMenu()
{
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Display InOrder\n");
    printf("3. Display PreOrder\n");
    printf("4. Display PostOrder\n");
    printf("5. Delete Node\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void insert(struct treeNode *root, char *key, char *value)
{
    if (strcmp(key, root->key) < 0)
    {
        if (root->left == NULL)
        {
            root->left = createNode(key, value);
        }
        else
        {
            insert(root->left, key, value);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = createNode(key, value);
        }
        else
        {
            insert(root->right, key, value);
        }
    }
}

void traverseInOrder(struct treeNode *root)
{
    if (root == NULL)
        return;
    traverseInOrder(root->left);
    printf("%s: ", root->key);
    printf("%s\n", root->value);
    traverseInOrder(root->right);
}

void traversePreOrder(struct treeNode *root)
{
    if (root == NULL)
        return;
    printf("%s: ", root->key);
    printf("%s\n", root->value);
    traversePreOrder(root->left);
    traversePreOrder(root->right);
}
void traversePostOrer(struct treeNode *root)
{
    if (root == NULL)
        return;
    traversePostOrer(root->left);
    traversePostOrer(root->right);
    printf("%s: ", root->key);
    printf("%s\n", root->value);
}

void deleteNode(struct treeNode *root)
{
    printf("Enter key to be deleted");
    char key[10];
    scanf("%s", key);
    struct treeNode *current = root;
    struct treeNode *prev = NULL;
    while (current != NULL)
    {
        int cmp = strcmp(key, current->key);
        if (cmp < 0)
        {
            prev = current;
            current = current->left;
        }
        else if (cmp > 0)
        {
            prev = current;
            current = current->right;
        }
        else
        {
            break;
        }
    }
    if (current == NULL)
    {
        printf("Node not found\n");
        return;
    }
    if (current->left == NULL && current->right != NULL)
    {
        if (prev->left == current)
        {
            prev->left = current->right;
        }
        else
        {
            prev->right = current->right;
        }
        free(current);
    }
    else if (current->left != NULL && current->right == NULL)
    {
        if (prev->left == current)
        {
            prev->left = current->left;
        }
        else
        {
            prev->right = current->right;
        }
        free(current);
    }
    else if (current->left == NULL && current->right == NULL)
    {
        if (prev->left == current)
        {
            prev->left = NULL;
        }
        else
        {
            prev->right = NULL;
        }
        free(current);
    }
    else
    {
        struct treeNode *temp = current->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        temp->left = current->left;
        if (prev->left == current)
        {
            prev->left = current->right;
        }
        else
        {
            prev->right = current->right;
        }
        free(current);
    }
}

int main()
{
    struct treeNode root;
    root.key[0] = '\0';
    root.value[0] = '\0';
    root.left = NULL;
    root.right = NULL;
    while (1)
    {
        printMenu();
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            char key[10];
            char value[100];
            printf("Enter key: ");
            scanf("%s", key);
            printf("Enter value: ");
            scanf("%s", value);
            insert(&root, key, value);
            break;
        case 2:
            traverseInOrder(&root);
            break;
        case 3:
            traversePreOrder(&root);
            break;
        case 4:
            traversePostOrer(&root);
            break;
        case 5:
            deleteNode(&root);
        case 6:
            exit(0);
        default:
            exit(0);
        }
    }
    return 0;
}