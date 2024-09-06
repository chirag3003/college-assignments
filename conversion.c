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

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

char *infixToPostfix(char *infix)
{
    char *postfix = (char *)malloc(strlen(infix) + 1);
    int k = 0;
    for (int i = 0; i < strlen(infix); i++)
    {
        if (isalnum(infix[i]))
        {
            postfix[k++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            char *op = (char *)malloc(2 * sizeof(char));
            op[0] = infix[i];
            op[1] = '\0';
            push(stack, op);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty() && stack[top][0] != '(')
            {
                postfix[k++] = pop(stack)[0];
            }
            pop(stack); // Remove '(' from stack
        }
        else if (isOperator(infix[i]))
        {
            while (!isEmpty() && precedence(stack[top][0]) >= precedence(infix[i]))
            {
                postfix[k++] = pop(stack)[0];
            }
            char *op = (char *)malloc(2 * sizeof(char));
            op[0] = infix[i];
            op[1] = '\0';
            push(stack, op);
        }
    }
    while (!isEmpty())
    {
        postfix[k++] = pop(stack)[0];
    }
    postfix[k] = '\0';
    return postfix;
}

char *infixToPrefix(char *infix)
{
    int length = strlen(infix);
    char *reversedInfix = (char *)malloc(length + 1);
    char *reversedPrefix = (char *)malloc(length + 1);

    // Reverse the infix expression
    for (int i = 0; i < length; i++)
    {
        if (infix[i] == '(')
        {
            reversedInfix[length - i - 1] = ')';
        }
        else if (infix[i] == ')')
        {
            reversedInfix[length - i - 1] = '(';
        }
        else
        {
            reversedInfix[length - i - 1] = infix[i];
        }
    }
    reversedInfix[length] = '\0';

    // Convert reversed infix to postfix
    char *reversedPostfix = infixToPostfix(reversedInfix);

    // Reverse the postfix expression to get the prefix expression
    for (int i = 0; i < length; i++)
    {
        reversedPrefix[i] = reversedPostfix[length - i - 1];
    }
    reversedPrefix[length] = '\0';

    free(reversedInfix);
    free(reversedPostfix);

    return reversedPrefix;
}

char *postfixToPrefix(char *postfix)
{
    int length = strlen(postfix);

    for (int i = 0; i < length; i++)
    {
        if (isalnum(postfix[i]))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
        else
        {
            char *operand1 = pop(stack);
            char *operand2 = pop(stack);

            char *expr = (char *)malloc(strlen(operand1) + strlen(operand2) + 2);
            sprintf(expr, "%c%s%s", postfix[i], operand2, operand1);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

char *prefixToPostfix(char *prefix)
{
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--)
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
            sprintf(expr, "%s%s%c", operand1, operand2, prefix[i]);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

char *postfixToInfix(char *postfix)
{
    int length = strlen(postfix);

    for (int i = 0; i < length; i++)
    {
        if (isalnum(postfix[i]))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(stack, operand);
        }
        else
        {
            char *operand2 = pop(stack);
            char *operand1 = pop(stack);

            char *expr = (char *)malloc(strlen(operand1) + strlen(operand2) + 4);
            sprintf(expr, "(%s%c%s)", operand1, postfix[i], operand2);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

char *prefixToInfix(char *prefix)
{
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--)
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

            char *expr = (char *)malloc(strlen(operand1) + strlen(operand2) + 4);
            sprintf(expr, "(%s%c%s)", operand1, prefix[i], operand2);

            push(stack, expr);

            free(operand1);
            free(operand2);
        }
    }

    return pop(stack);
}

void displayMenu()
{
    printf("1. Prefix to Postfix\n");
    printf("2. Postfix to Prefix\n");
    printf("3. Prefix to Infix\n");
    printf("4. Postfix to Infix\n");
    printf("5. Infix to Postfix\n");
    printf("6. Infix to Prefix\n");
    printf("7. Display\n");
    printf("8. Exit\n");
}

int main()
{
    while (1)
    {
        printf("Enter expression:\n");
        char input[100];
        scanf("%s", input);
        displayMenu();
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        char *result;
        switch (choice)
        {
        case 1:
            result = prefixToPostfix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 2:
            result = postfixToPrefix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 3:
            result = prefixToInfix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 4:
            result = postfixToInfix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 5:
            result = infixToPostfix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 6:
            result = infixToPrefix(input);
            printf("Result expression: %s\n", result);
            free(result);
            break;
        case 7:
            display(stack);
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}