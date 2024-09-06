#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

char* stack[STACK_SIZE];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == STACK_SIZE - 1;
}

void push(char* stack[], char* item)
{
    if (isFull())
    {
        printf("Stack is full\n");
    }
    else
    {
        top++;
        stack[top] = item;
    }
}

char* pop(char* stack[])
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return NULL;
    }
    else
    {
        return stack[top--];
    }
}

void display(char* stack[])
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
            printf("%s\n", stack[i]);
        }
    }
}

char* postfixToInfix(char* postfix)
{
    int length = strlen(postfix);

    for (int i = 0; i < length; i++)
    {
        if (isalnum(postfix[i]))
        {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
        else
        {
            char* operand2 = pop(stack);
            char* operand1 = pop(stack);

            char* expr = (char*)malloc(strlen(operand1) + strlen(operand2) + 4);
            sprintf(expr, "(%s%c%s)", operand1, postfix[i], operand2);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

int main()
{
    char postfix[] = "ABC/-AK/L-*";
    char* infix = postfixToInfix(postfix);
    printf("Infix expression: %s\n", infix);
    free(infix);
    return 0;
}