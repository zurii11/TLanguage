#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "lexer.h"

// TODO: Rewrite this to c-style strings to use pointer arithmetic for getting token column

std::string chop_delim(std::string* line, char delim)
{
    int size = line->size();
    int i{0};

    while (i < size && line->at(i) != delim)
    {
        ++i;
    }

    return line->substr(0, i);
}

std::string trim_left(std::string* line)
{
    int size = line->size();
    int i{0};

    while (i < size && std::isspace(line->at(i)))
    {
        ++i;
    }

    return line->substr(i);
}

std::string trim_right(std::string* line)
{
    int size = line->size();
    int i{0};

    while (i < size && std::isspace(line->at(size - 1 - i)))
    {
        ++i;
    }

    return line->substr(0, size - i);
}

std::vector<Token> lex_line(std::string* line, std::string* filepath, std::vector<Token>* tokens, int line_number)
{
    int col{};
    std::string source = trim_left(line);
    col = line->size() - source.size();
    std::string token{};

    while (source.size() > 0)
    {
        token = chop_delim(&source, ' ');
        std::cout << token << " " << col << " In lex line!\n";
        tokens->push_back({ *filepath, token, line_number, col });
        source = source.substr(token.size());
        source = trim_left(&source);
        col = line->size() - source.size();
    }

    return *tokens;
}

std::vector<Token> lex_file(std::string filepath)
{
    std::fstream file;
    std::vector<Token> tokens;
    int line_number{};

    file.open(filepath, std::ios::in);

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            lex_line(&line, &filepath, &tokens, line_number);
            //std::cout << tokens.at(0).filepath;
            //std::cout << tokens[line_number].filepath << "; " << tokens[line_number].token << "; " << tokens[line_number].line << "; " << tokens[0].column << "; \n";
            ++line_number;
        }
        file.close();
    }

    return tokens;
}
