/*
    Nmae: Chirag Bhalotia
    PRN: 1032232301
    Panel: F
    Roll: 48
    Problem: Write a program to convert infix expression to postfix and prefix using stack.
*/

#include <stdio.h>
#include <stdlib.h>
// #include <ctype.h>
#include <string.h>

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

int precedence(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '^')
    {
        return 3;
    }
    return 0;
}

void reverse(char *exp)
{
    int length = strlen(exp);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = exp[i];
        exp[i] = exp[length - i - 1];
        exp[length - i - 1] = temp;
    }
}

void replaceParentheses(char *exp)
{
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(')
        {
            exp[i] = ')';
        }
        else if (exp[i] == ')')
        {
            exp[i] = '(';
        }
    }
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char *infix, char *postfix)
{
    int i, j = 0;
    char c;
    for (i = 0; infix[i] != '\0'; i++)
    {
        char _c = infix[i];

        char *c = (char *)malloc(2 * sizeof(char));
        c[0] = _c;
        c[1] = '\0';
        if (c[0] == '(')
        {
            push(stack, c);
        }
        else if (c[0] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop(stack);
            }
            pop(stack); // Remove '(' from stack
        }
        else if (isOperator(c[0]))
        {
            while (top != -1 && precedence(stack[top]) >= precedence(c[0]))
            {
                postfix[j++] = pop(stack);
            }
            push(c, stack);
        }
        else
            postfix[j++] = c[0];
    }
    while (top != -1)
    {
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0';
}

void infixToPrefix(char *infix, char *prefix)
{
    char reversedInfix[STACK_SIZE], postfix[STACK_SIZE];
    strcpy(reversedInfix, infix);
    reverse(reversedInfix);
    replaceParentheses(reversedInfix);
    infixToPostfix(reversedInfix, postfix);
    reverse(postfix);
    strcpy(prefix, postfix);
}

int main()
{
    char infix[STACK_SIZE], postfix[STACK_SIZE], prefix[STACK_SIZE];
    int choice;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Convert Infix to Prefix\n");
        printf("3. Push\n");
        printf("4. Pop\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter infix expression: ");
            scanf("%s", infix);
            infixToPostfix(infix, postfix);
            printf("Postfix expression: %s\n", postfix);
            break;
        case 2:
            printf("Enter infix expression: ");
            scanf("%s", infix);
            infixToPrefix(infix, prefix);
            printf("Prefix expression: %s\n", prefix);
            break;
        case 3:
            printf("Enter the element to be pushed: ");
            char c;
            scanf(" %c", &c);
            push(stack, c);
            break;
        case 4:
            char ch = pop(stack);
            printf("Popped element: %c\n", ch);
            break;
        case 5:
            display(stack);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}