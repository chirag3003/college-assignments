#include <stdio.h>

const int STACK_SIZE = 5;
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == STACK_SIZE - 1;
}

void push(int stack[], int n)
{
    // Check if stack is full before pushing
    if (isFull())
    {
        printf("Stack is full\n");
    }
    else
    {
        top++;
        stack[top] = n;
    }
}

void pop(int stack[])
{
    // Check if stack is empty before popping
    if (isEmpty())
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Popped element is %d\n", stack[top]);
        top--;
    }
}

void display(int stack[])
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Stack elements are: \n");
        for (int i = 0; i <= top; i++)
        {
            printf("%d \n", stack[i]);
        }
    }
}

void printMenu()
{
    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Display\n");
    printf("4. Exit\n");
}

int main()
{
    int stack[STACK_SIZE];
    int choice;
    while (1)
    {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            if (isFull())
            {
                printf("Stack is full\n");
            }
            else
            {
                int n;
                printf("Enter the element to be pushed: ");
                scanf("%d", &n);
                push(stack, n);
            }
            break;
        case 2:
            pop(stack);
            break;
        case 3:
            display(stack);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
