/*
    PRN: 1032232301
    Name: Chirag Bhalotia
    Program: Circular Queue
*/

#include <stdio.h>

const int queue_size = 4;
int front = 0, rear = 0;

int isEmpty()
{
    return front == rear;
}

int isFull()
{
    return (rear + 1 == front) || (front == 0 && rear == queue_size - 1);
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
        if (front == queue_size)
        {
            front = 0;
        }
        printf("Deleted element is %d\n", queue[front]);
    }
}

void insertQ(int queue[], int n)
{
    if (isFull())
    {
        printf("Queue is full\n");
    }
    else
    {
        rear++;
        if (rear == queue_size)
        {
            rear = 0;
        }
        queue[rear] = n;
    }
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
        int r = rear;
        int f = front;
        while (f != r)
        {
            f++;
            if (f == queue_size)
            {
                f = 0;
            }
            printf("%d \n", queue[f]);
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