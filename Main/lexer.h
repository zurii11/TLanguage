#pragma once
#include <string>
#include <vector>

struct Token
{
    std::string filepath;
    std::string token;
    int line;
    int column;
};

std::vector<Token> lex_file(std::string);
std::string trim_left(std::string* line);
std::string trim_right(std::string* line);
