#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int STACK_SIZE = 100;
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == STACK_SIZE - 1;
}

void push(char *stack[], char *item)
{
    if (isFull())
    {
        printf("Stack is full\n");
    }
    else
    {
        top++;
        printf("top: %d\n", top);
        char str[STACK_SIZE];
        strcpy(str, item);
        stack[top] = str;
        // strcpy(stack[top],item);
    }
}

void pop(char *stack[])
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
    }
    else
    {
        stack[top--];
    }
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void prefixToInfix(char *prefix)
{
    printf("hello\n");
    int l = strlen(prefix);
    printf("l: %d\n", l);
    char *stack[STACK_SIZE];
    printf("here\n");
    for (int i = l - 1; i >= 0; i--)
    {
        printf("i: %d\n", i);
        printf("stack[top]: %s\n", stack[top]);
        char c = prefix[i];
        char str[2] = "\0";
        str[0] = c;
        str[1] = '\0';
        char endB[] = {')', '\0'};
        printf("c: %s\n", str);
        if (isOperator(c))
        {
            char res[STACK_SIZE];
            res[0] = '(';
            res[1] = '\0';
            printf("stack: %s\n", stack[top]);
            printf("stack: %s\n", stack[top-1]);
            strcat(res, stack[top--]);
            strcat(res, str);
            strcat(res, stack[top--]);
            strcat(res, endB);
            printf("res: %s\n", res);
            push(stack, res);
        }
        else
        {
            printf("str is \n");
            // printf("str: %s\n", str);
            push(stack, str);
            printf("stack[top]: %s\n", stack[top]);
        }
    }
    printf("Infix expression is: %s\n", stack[top]);
}

int main()
{
    char prefix[] = "*-A/BC-/AKL";
    prefixToInfix(prefix);
    return 0;
}