#pragma once

class Stack
{
private:
    int stack[100], size, top;
public:
    Stack();
    void push(int x);
    int pop();
    int plus();
    int minus();
    int greater();
    int less();
    int equal();
    int xequal();
    void dup();
    int dump();
};
