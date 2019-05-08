#include <string>
#include "token_type.h"

#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

class Token
{

private:
    TokenType type;
    string value;
    unsigned int line;
    unsigned int column;

public:
    Token();
    Token(TokenType type, string value, unsigned int line, unsigned int column);
    TokenType get_type();
    string get_value();
    unsigned int get_line();
    unsigned int get_column();
};

#endif
