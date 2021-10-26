#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "stack.h"
#include "lexer.h"

// TODO: Improve error handling.

enum OPS
{
    PUSH,
    PLUS,
    MINUS,
    EQUAL,
    DUMP,
    IF,
    ELSE,
    END,
};

struct OP
{
    int id;
    int param;
};

OP push(int x)
{
    //int* rt = new int[2]{0, x};
    return { PUSH, x};
}

OP plus()
{
    //int* rt = new int[2]{1, };
    return { PLUS, };
}

OP minus()
{
    //int* rt = new int[2]{2, };
    return { MINUS, };
}

OP equal()
{
    //int* rt = new int[2]{3, };
    return { EQUAL, };
}

OP dump()
{
    //int* rt = new int[2]{4, };
    return { DUMP, };
}

OP iff()
{
    return { IF, };
}

OP elze()
{
    return { ELSE, };
}

OP end()
{
    return { END, };
}

void error(int line, int col, std::string filepath, std::string token, std::string msg)
{
    std::cerr << "Error at " << filepath << "; line - " << line << "; column - " << col << "; token - \"" << token << "\": " << msg << '\n';
    std::exit(1);
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
            case EQUAL: // EQUAL
                std::cout << "EQUAL\n";
                stack.equal();
                break;
            case DUMP: // DUMP
                std::cout << "DUMP\n";
                stack.dump();
                break;
            case IF: // IF
                a = stack.pop();
                if (a)
                    continue;
                else    
                    i = program[i].param-1;
                break;
            case ELSE: // ELSE
                i = program[i].param-1;
            case END: // END
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
    Stack blocks;
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
        else if (token == "if")
        {
            program[i] = iff();
            blocks.push(i);
        }
        else if (token == "else")
        {
            program[i] = elze();
            int block_ind = blocks.pop();

            assert(program[block_ind].id == IF && "Else can only close 'if' blocks");
            program[block_ind].param = i + 1;
            blocks.push(i);
        }
        else if (token == "end")
        {
            program[i] = end();
            int block_ind = blocks.pop();

            assert((program[block_ind].id == IF || program[block_ind].id == ELSE) && "End can only close 'if' and 'else' blocks");
            program[block_ind].param = i + 1;
        }
        else
        {
            try
            {
                program[i] = push(std::stoi(token));
            }
            catch (std::exception &err)
            {
                error(tokens[i].line, tokens[i].column, tokens[i].filepath, token, "Expected int.");
            }
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
