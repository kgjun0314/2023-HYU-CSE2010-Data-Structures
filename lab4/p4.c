#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

Stack* CreateStack(int max)
{
    Stack* S = (Stack*)malloc(sizeof(Stack));
    S -> key = (int*)malloc(sizeof(int) * max);
    S -> max_stack_size = max;
    S -> top = -1;

    return S;
}

void Push(Stack* s, int x)
{
    if(IsFull(s))
    {
        printf("Full stack\n");
        exit(0);
    }
    else
        s -> key[++(s -> top)] = x;
}

int Pop(Stack* s)
{
    int ret = Top(s);
    (s -> top)--;
    return ret;
}

int Top(Stack* s)
{
    if(IsEmpty(s))
    {
        printf("Empty stack\n");
        exit(0);
    }
    else
        return s -> key[s -> top];
}

void DeleteStack(Stack* s)
{
    free(s -> key);
    free(s);
}

int IsEmpty(Stack* s)
{
    if(s -> top == -1)
        return 1;
    else
        return 0;
}

int IsFull(Stack* s)
{
    if(s -> top == s -> max_stack_size - 1)
        return 1;
    else
        return 0;
}

void Postfix(Stack* s, char input_str)
{
    if(input_str == '+')
    {
        int num1 = Pop(s);
        int num2 = Pop(s);
        Push(s, num2 + num1);
    }
    else if(input_str == '-')
    {
        int num1 = Pop(s);
        int num2 = Pop(s);
        Push(s, num2 - num1);
    }
    else if(input_str == '*')
    {
        int num1 = Pop(s);
        int num2 = Pop(s);
        Push(s, num2 * num1);
    }
    else if(input_str == '/')
    {
        int num1 = Pop(s);
        int num2 = Pop(s);
        Push(s, num2 / num1);
    }
    else if(input_str == '%')
    {
        int num1 = Pop(s);
        int num2 = Pop(s);
        Push(s, num2 % num1);
    }
    else
    {
        Push(s, atoi(&input_str));
    }
}

void main(int argc, char* argv[])
{
    FILE* fi = fopen(argv[1], "r");

    Stack* stack = CreateStack(10);
    
    char c;
    printf("Top numbers: ");
    while(1)
    {
        fscanf(fi, "%c", &c);
        if(c == '#')
            break;

        Postfix(stack, c);
        printf("%d ", Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Top(stack));

    fclose(fi);
    DeleteStack(stack);
}