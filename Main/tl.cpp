#include <iostream>
#include <string>
#include <vector>
#include "stack.h"
#include "lexer.h"

enum OPS
{
    PUSH,
    PLUS,
    MINUS,
    EQUAL,
    DUMP
};

struct OP
{
    int id;
    int param;
};

OP push(int x)
{
    //int* rt = new int[2]{0, x};
    return { 0, x};
}

OP plus()
{
    //int* rt = new int[2]{1, };
    return { 1, };
}

OP minus()
{
    //int* rt = new int[2]{2, };
    return { 2, };
}

OP equal()
{
    //int* rt = new int[2]{3, };
    return { 3, };
}

OP dump()
{
    //int* rt = new int[2]{4, };
    return { 4, };
}

void compile_program(OP program[100], int size)
{
    Stack stack;
    int a, b;

    for (int i{0}; i < size; ++i)
    {
        switch (program[i].id)
        {
            case PUSH: // PUSH
                std::cout << "PUSH\n";
                stack.push(program[i].param);
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
    OP program[100]{};
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

    std::cout << ind << '\n';

    compile_program(program, ind+1);
}

int main(int argc, char** argv)
{
    //int* program[]{ push(1), push(5), dump(), plus(), dump(), push(8), minus(), dump(), push(1), equal(), dump() };
    //compile_program(program, sizeof(program)/sizeof(program[0]));

    parse_tokens(argv[1]);
}
