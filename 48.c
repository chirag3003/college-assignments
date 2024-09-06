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

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c)
{
    if (top == MAX - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop()
{
    if (top == -1)
    {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

void display()
{
    if (top == -1)
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements are: \n");
    for (int i = 0; i <= top; i++)
    {
        printf("%c \n", stack[i]);
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
        c = infix[i];
        if (c == '(')
        {
            push(c);
        }
        else if (c == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop();
            }
            pop(); // Remove '(' from stack
        }
        else if (isOperator(c))
        {
            while (top != -1 && precedence(stack[top]) >= precedence(c))
            {
                postfix[j++] = pop();
            }
            push(c);
        }
        else
            postfix[j++] = c;
    }
    while (top != -1)
    {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void infixToPrefix(char *infix, char *prefix)
{
    char reversedInfix[MAX], postfix[MAX];
    strcpy(reversedInfix, infix);
    reverse(reversedInfix);
    replaceParentheses(reversedInfix);
    infixToPostfix(reversedInfix, postfix);
    reverse(postfix);
    strcpy(prefix, postfix);
}

int main()
{
    char infix[MAX], postfix[MAX], prefix[MAX];
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
            push(c);
            break;
        case 4:
            char ch = pop();
            printf("Popped element: %c\n", ch);
            break;
        case 5:
            display();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}