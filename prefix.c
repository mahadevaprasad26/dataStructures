#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50

struct stack
{
    int stack[MAX];
    int top;
} S;

struct stack2
{
    float stack2[MAX];
    int top;
} S2;

// Declarations
void push(int);
int pop();
int isEmpty();
void inToPre(char[], char[]);
void print(char[]);
int precedence(char);
int isoperand(char);
float pre_eval(char[]);
void reverse(char[]);

void reverse(char str[])
{
    int i = 0, j = strlen(str) - 1;
    while (i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void inToPre(char infix[], char prefix[])
{
    S.top = -1;
    int i, j = 0;
    char symbol; // for storing symbol of infix expression
    char next;

    reverse(infix);
    for (i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];
        switch (symbol)
        {
        case ')': // Push ')' onto the stack
            push(symbol);
            break;
        case '(': // Pop till '(' encountered
            while ((next = pop()) != ')')
                prefix[j++] = next;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '$':
            // In left to right associavity (if precedence of oprs. are equal) push
            // If right to left associavity (if precedence of oprs. are equal) pop
            while (!isEmpty() && (precedence(S.stack[S.top]) > precedence(symbol) ||
                                  (precedence(S.stack[S.top]) == precedence(symbol) && symbol == '^')))
            {
                prefix[j++] = pop();
            }
            push(symbol);
            break;
        default: // If it's an operand
            prefix[j++] = symbol;
        }
    }

    // Pop remaining operators from the stack
    while (!isEmpty())
        prefix[j++] = pop();

    prefix[j] = '\0';
    reverse(prefix); // Null-terminate the prefix expression
}

int isoperand(char ch)
{
    switch (ch)
    {
    case '$':
    case '^':
    case '/':
    case '*':
    case '+':
    case '-':
    case '%':
    case '(':
    case ')':
        return 0;
    default:
        return 1;
    }
}

int precedence(char symbol)
{
    switch (symbol)
    {
    case '$':
    case '^':
        return 3;
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void print(char prefix[])
{
    int i = 0;
    printf("Prefix expression is: ");
    while (prefix[i])
    {
        printf("%c", prefix[i++]);
    }
    printf("\n");
}

void push(int c)
{
    if (S.top == MAX - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    S.top++;
    S.stack[S.top] = c;
}

int pop()
{
    int c;
    if (S.top == -1)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    c = S.stack[S.top];
    S.top = S.top - 1;
    return c;
}

void push2(float c)
{
    if (S2.top == MAX - 1)
    {
        printf("Stack overflow\n");
        return;
    }
    S2.top++;
    S2.stack2[S2.top] = c;
}

float pop2()
{
    float c;
    if (S2.top == -1)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    c = S2.stack2[S2.top];
    S2.top = S2.top - 1;
    return c;
}

int isEmpty()
{
    return S.top == -1;
}

float pre_eval(char prefix[])
{
    S2.top = -1;
    char ch;
    int i;
    float a, b;
    reverse(prefix);
    for (i = 0; i < strlen(prefix); i++)
    {
        ch = prefix[i];
        if (isoperand(ch))
        {
            float item;
            printf("Enter the value of %c=", ch);
            scanf("%f", &item);
            push2(item); // Push the number (operand) onto the stack
        }
        else
        {
            a = pop2(); // Pop two operands and apply the operator
            b = pop2();
            switch (prefix[i])
            {
            case '+':
                push2(a + b);
                break;
            case '-':
                push2(a - b);
                break;
            case '*':
                push2(a * b);
                break;
            case '/':
                push2(a / b);
                break;
            case '$':
            case '^':
                push2(pow(a, b));
                break;
            }
        }
    }
    return pop2();
}

void main()
{
    char infix[MAX], prefix[MAX];
    int choice;
    float result;
    printf("Menu\n1.Enter Infix Expression\n2.Convert to Prefix\n3.Evaluate Prefix\n4.Exit\n");
    for (;;)
    {
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the Infix Expression: ");
            scanf("%s", infix);
            break;
        case 2:
            inToPre(infix, prefix);
            print(prefix);
            break;
        case 3:
            printf("Enter the prefix expression in character form:");
            scanf("%s", prefix);
            result = pre_eval(prefix);
            printf("Prefix evaluation result: %f\n", result);
            break;
        case 4:
            printf("!! THANK YOU !!\n");
            exit(0);
        default:
            printf("Invalid Choice\n");
        }
    }
}