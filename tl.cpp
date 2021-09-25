#include <iostream>

enum OPS
{
    PUSH,
    PLUS,
    MINUS,
    DUMP
};

int* push(int x)
{
    int* rt = new int[2]{0, x};
    return rt;
}

int* plus()
{
    int* rt = new int[2]{1, };
    return rt;
}

int* minus()
{
    int* rt = new int[2]{2, };
    return rt;
}

void compile_program(int* program[], int size)
{
    int stack[100]{};
    int stackIndex{0};
    int a, b;

    for (int i{0}; i < size; ++i)
    {
        switch (program[i][0])
        {
            case PUSH: // PUSH
                std::cout << "PUSH\n";
                stack[stackIndex] = program[i][1]; 
                ++stackIndex;
                break;
            case PLUS: // PLUS
                std::cout << "PLUS\n";
                a = stack[stackIndex-1];
                b = stack[stackIndex-2];
                stack[stackIndex] = a + b;
                std::cout << "PLUS RESULT: " << stack[stackIndex] << '\n';
                ++stackIndex;
                break;
            case MINUS: // MINUS
                std::cout << "MINUS\n";
                a = stack[stackIndex-1];
                b = stack[stackIndex-2];
                stack[stackIndex] = a - b;
                std::cout << "MINUS RESULT: " << stack[stackIndex] << '\n';
                ++stackIndex;
                break;
            case DUMP: // DUMP
                std::cout << "DUMP\n";
                break;
            default:
                std::cout << "Error: undefined operation\n";
        }
    }
}

int main()
{
   int* program[]{ push(1), push(5), plus(), minus() };
   compile_program(program, sizeof(program)/sizeof(program[0]));
}
