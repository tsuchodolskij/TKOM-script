#include "token.h"

using namespace std;

Token::Token() {}

Token::Token(TokenType t, string s, unsigned int l, unsigned int c) :
    type(t), value(s), line(l), column(c) {}

TokenType Token::get_type()
{
    return this->type;
}

string Token::get_value()
{
    return this->value;
}

unsigned int Token::get_line()
{
    return this->line;
}

unsigned int Token::get_column()
{
    return this->column;
}
