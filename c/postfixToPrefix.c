#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

char *stack[STACK_SIZE];
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
        stack[top] = item;
    }
}

char *pop(char *stack[])
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

void display(char *stack[])
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

char *postfixToPrefix(char *prefix)
{
    int length = strlen(prefix);

    for (int i = 0 ; i < length; i++)
    {
        if (isalnum(prefix[i]))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = prefix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
        else
        {
            char *operand1 = pop(stack);
            char *operand2 = pop(stack);

            char *expr = (char *)malloc(strlen(operand1) + strlen(operand2) + 2);
            sprintf(expr, "%c%s%s", prefix[i], operand2, operand1);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

int main()
{
    char prefix[] = "ABC/-AK/L-*";
    char *postfix = postfixToPrefix(prefix);
    printf("Postfix expression: %s\n", postfix);
    free(postfix);
    return 0;
}