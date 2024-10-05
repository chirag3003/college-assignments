/*
    PRN: 1032232301
    Name: Chirag Bhalotia
    Program: Linear Queue
*/

#include <stdio.h>

const int queue_size = 100;
int front = -1, rear = -1;

int isEmpty()
{
    return front == rear;
}

void deleteQ(int queue[])
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
    }
    else
    {
        front++;
        printf("Deleted element is %d\n", queue[front]);
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
    }
}

void insertQ(int queue[], int n)
{
    if (rear == queue_size - 1)
    {
        printf("Queue is full\n");
    }
    else
    {
        rear++;
        queue[rear] = n;
    }
}

int isFull()
{
    return rear == queue_size - 1;
}

void display(int queue[])
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("Queue elements are: \n");
        for (int i = front + 1; i <= rear; i++)
        {
            printf("%d \n", queue[i]);
        }
        printf("\n");
    }
}

int main()
{
    int queue[queue_size];
    int choice, n;
    while (1)
    {
        printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted: ");
            scanf("%d", &n);
            insertQ(queue, n);
            break;
        case 2:
            deleteQ(queue);
            break;
        case 3:
            display(queue);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice\n");
        }
        printf("\n");
    }
    return 0;
}