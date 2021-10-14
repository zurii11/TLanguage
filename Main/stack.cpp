#include <iostream>
#include "stack.h"

Stack::Stack()
{
    size = 100;
    top = -1;
}

void Stack::push(int x)
{
    if (top >= size-1)
            std::cout << "Stack Overflow!\n";
    else
    {
        ++top;
        stack[top] = x;
    }
}

int Stack::pop()
{
    if (top <= -1)
        std::cout << "Stack Underflow!\n";
    else
    {
        int poppedValue = stack[top];
        stack[top] = 0;
        --top;
        return poppedValue;
    }

    return 1;
}

int Stack::plus()
{
    int a = pop();
    int b = pop();

    push(a+b);

    return stack[top];
}

int Stack::minus()
{
    int a = pop();
    int b = pop();
    
    push(a-b);

    return stack[top];
}

int Stack::equal()
{
    int a = pop();
    int b = pop();

    if (a == b)
    {
        push(1);
        return 1;
    }
    else
    {
        push(0);
        return 0;
    }
}

int Stack::dump()
{
    if (top >= size-1)
        std::cout << "Stack Overflow\n";
    else
    {
        std::cout << "Stack top is: " << stack[top] << '\n';
        return stack[top];
    }

    return 1;
}



