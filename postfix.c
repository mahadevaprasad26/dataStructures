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
void inToPost(char[], char[]);
void print(char[]);
int precedence(char);
int isoperand(char);
float post_eval(char[]);

void inToPost(char infix[], char postfix[])
{
    S.top = -1;
    int i, j = 0;
    char symbol; // for storing symbol of infix expression
    char next;

    for (i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];
        switch (symbol)
        {
        case '(': // Push '(' onto the stack
            push(symbol);
            break;
        case ')': // Pop till '(' encountered
            while ((next = pop()) != '(')
                postfix[j++] = next;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '$':
            // Handle operators with precedence
            // For '^', right-associative, so we compare precedence with strict inequality
            while (!isEmpty() && (precedence(S.stack[S.top]) > precedence(symbol) ||
                                  (precedence(S.stack[S.top]) == precedence(symbol) && symbol != '^')))
            {
                postfix[j++] = pop();
            }
            push(symbol);
            break;
        default: // If it's an operand
            postfix[j++] = symbol;
        }
    }

    // Pop remaining operators from the stack
    while (!isEmpty())
        postfix[j++] = pop();

    postfix[j] = '\0'; // Null-terminate the postfix expression
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

void print(char postfix[])
{
    int i = 0;
    printf("Postfix expression is: ");
    while (postfix[i])
    {
        printf("%c", postfix[i++]);
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

float post_eval(char postfix[])
{
    S2.top = -1;
    char ch;
    int i;
    float a, b;

    for (i = 0; i < strlen(postfix); i++)
    {
        ch = postfix[i];
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
            switch (postfix[i])
            {
            case '+':
                push2(b + a);
                break;
            case '-':
                push2(b - a);
                break;
            case '*':
                push2(b * a);
                break;
            case '/':
                push2(b / a);
                break;
            case '$':
            case '^':
                push2(pow(b, a));
                break;
            }
        }
    }
    return pop2();
}

void main()
{
    char infix[MAX], postfix[MAX];
    int choice;
    float result;
    printf("Menu\n1.Enter Infix Expression\n2.Convert to Postfix\n3.Evaluate Postfix\n4.Exit\n");
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
            inToPost(infix, postfix);
            print(postfix);
            break;
        case 3:
            printf("Enter the postfix expression in character form:");
            scanf("%s", postfix);
            result = post_eval(postfix);
            printf("Postfix evaluation result: %f\n", result);
            break;
        case 4:
            printf("!! THANK YOU !!\n");
            exit(0);
        default:
            printf("Invalid Choice\n");
        }
    }
}