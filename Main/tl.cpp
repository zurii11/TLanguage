#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include "lexer.h"

// TODO: Move from int* to structs in program[]

enum OPS
{
    PUSH,
    PLUS,
    MINUS,
    EQUAL,
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

int* equal()
{
    int* rt = new int[2]{3, };
    return rt;
}

int* dump()
{
    int* rt = new int[2]{4, };
    return rt;
}

void compile_program(int* program[], int size)
{
    Stack stack;
    int a, b;

    for (int i{0}; i < size; ++i)
    {
        switch (program[i][0])
        {
            case PUSH: // PUSH
                std::cout << "PUSH\n";
                stack.push(program[i][1]);
                break;
            case PLUS: // PLUS
                std::cout << "PLUS\n";
                stack.plus();
                break;
            case MINUS: // MINUS
                std::cout << "MINUS\n";
                stack.minus();
                break;
            case EQUAL:
                std::cout << "EQUAL\n";
                stack.equal();
                break;
            case DUMP: // DUMP
                std::cout << "DUMP\n";
                stack.dump();
                break;
            default:
                std::cout << "Error: undefined operation\n";
        }
    }
}

void parse_tokens(std::string filepath)
{
    std::vector<Token> tokens = lex_file(filepath);
    int* program[100]{};
    int ind{};

    for (int i{0}; i < tokens.size(); i++)
    {
        std::string token = tokens[i].token;

        if (token == "+")
        {
            program[i] = plus();
        }
        else if (token == "-")
        {
            program[i] = minus();
        }
        else if (token == "=")
        {
            program[i] = equal();
        }
        else if (token == ".")
        {
            program[i] = dump();
        }
        else
        {
            program[i] = push(std::stoi(token));
        }

        ind = i;
    }

    compile_program(program, ind+1);
}

int main(int argc, char** argv)
{
    //int* program[]{ push(1), push(5), dump(), plus(), dump(), push(8), minus(), dump(), push(1), equal(), dump() };
    //compile_program(program, sizeof(program)/sizeof(program[0]));

    parse_tokens(argv[1]);
}
