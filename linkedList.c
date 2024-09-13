#include <stdio.h>
#include <stdlib.h>
// #include <ctype.h>
#include <string.h>

struct node
{
    int prn;
    char name[20];
    struct node *next;
};

void printMenu()
{
    printf("\nMenu:\n");
    printf("1. Create\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Find length\n");
    printf("5. Insert\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}
int length(struct node *headNode);

void create(struct node *headNode)

{
    int prn;
    char name[20];
    printf("Enter PRN: ");
    scanf("%d", &prn);
    printf("Enter name: \n");
    // fgets(name, 20, stdin);
    // gets(name);
    scanf("%s", name);
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    struct node *temp = headNode;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}
void insert(struct node *headNode)
{
    int prn;
    char name[20];
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    int l = length(headNode);
    if (index > l)
    {
        printf("Invalid index\n");
        return;
    }
    printf("Enter PRN: ");
    scanf("%d", &prn);
    printf("Enter name: ");
    scanf("%s", name);
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    struct node *temp = headNode;
    int count = 0;
    while (temp->next != NULL)
    {
        if (count == index)
        {
            newNode->next = temp->next;
            temp->next = newNode;
            break;
        }
        temp = temp->next;
        count++;
    }
    temp->next = newNode;
}

void delete(struct node *headNode)
{
    int prn;
    printf("Enter PRN to delete: ");
    scanf("%d", &prn);
    struct node *temp = headNode;
    while (temp->next != NULL)
    {
        if (temp->next->prn == prn)
        {
            temp->next = temp->next->next;
            break;
        }
        temp = temp->next;
    }
}

void display(struct node *headNode)
{
    struct node *temp = headNode->next;
    while (temp != NULL)
    {
        printf("PRN: %d,\nName: %s\n\n", temp->prn, temp->name);
        temp = temp->next;
    }
}

int length(struct node *headNode)
{
    int count = 0;
    struct node *temp = headNode->next;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int main()
{
    struct node headNode;

    int choice;
    int prn;
    char name[20];
    while (1)
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create(&headNode);
            break;
        case 2:
            printf("Enter PRN to delete: ");
            scanf("%d", &prn);
            delete (&headNode);
            break;
        case 3:
            display(&headNode);
            break;
        case 4:
            printf("Length of the list: %d\n", length(&headNode));
            break;
        case 5:
            insert(&headNode);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }

    return 0;
}