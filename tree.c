#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode
{
    char data[10];
    struct treeNode *left;
    struct treeNode *right;
};

struct treeNode *createNode(char *data)
{
    struct treeNode *newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printMenu()
{
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Insert custom\n");
    printf("3. Display InOrder\n");
    printf("4. Display PreOrder\n");
    printf("5. Display PostOrder\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void printInsertMenu()
{
    printf("\nMenu:\n");
    printf("1. Insert Left\n");
    printf("2. Insert Right\n");
    printf("Enter your choice: ");
}

void insert(struct treeNode *root, char *data)
{
    if (strcmp(data, root->data) < 0)
    {
        if (root->left == NULL)
        {
            root->left = createNode(data);
        }
        else
        {
            insert(root->left, data);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = createNode(data);
        }
        else
        {
            insert(root->right, data);
        }
    }
}

void insertCustom(struct treeNode *root)
{
    printf("Current Value: %s\n", root->data);
    printInsertMenu();
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        if (root->left == NULL)
        {
            char data[10];
            printf("Enter data: ");
            scanf("%s", data);
            root->left = createNode(data);
        }
        else
        {
            insertCustom(root->left);
        }

        break;
    case 2:
        if (root->right == NULL)
        {
            char data[10];
            printf("Enter data: ");
            scanf("%s", data);
            root->right = createNode(data);
        }
        else
        {
            insertCustom(root->right);
        }
        break;
    default:
        break;
    }
}

void traverseInOrder(struct treeNode *root)
{
    if (root == NULL)
        return;
    traverseInOrder(root->left);
    printf("%s ", root->data);
    traverseInOrder(root->right);
}

void traversePreOrder(struct treeNode *root)
{
    if (root == NULL)
        return;
    printf("%s ", root->data);
    traversePreOrder(root->left);
    traversePreOrder(root->right);
}

void traversePostOrder(struct treeNode *root)
{
    if (root == NULL)
        return;
    traversePostOrder(root->left);
    traversePostOrder(root->right);
    printf("%s ", root->data);
}

int main()
{
    struct treeNode root;
    root.data[0] = '\0';
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
            if (root.data[0] == '\0')
            {
                printf("Enter data: ");
                scanf("%s", root.data);
            }
            else
            {
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
            traverseInOrder(&root);
            break;
        case 4:
            traversePreOrder(&root);
            break;
        case 5:
            traversePostOrder(&root);
            break;
        case 6:
            exit(0);
        default:
            exit(0);
        }
    }
    return 0;
}