#include <fstream>
#include "token.h"
#include "token_type.h"
#include "source.h"

#ifndef LEXER_H
#define LEXER_H

using namespace std;

class Lexer
{

private:
    Source& source;
    static TokenType alphanum_token_type(const string& keyword);

public:
    explicit Lexer(Source& s);
    Token get_token();
};

#endif
