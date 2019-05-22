#include <iostream>
#include <string>
#include "lexer.h"

using namespace std;


Lexer::Lexer(Source& s): source(s) {}

TokenType Lexer::alphanum_token_type(const string& keyword)
{
    if (keyword == "int") return INT_TOKEN;
    else if (keyword == "float") return FLOAT_TOKEN;
    else if (keyword == "string") return STRING_TOKEN;
    else if (keyword == "void") return VOID_TOKEN;
    else if (keyword == "in") return IN_TOKEN;
    else if (keyword == "if") return IF_TOKEN;
    else if (keyword == "elseif") return ELSEIF_TOKEN;
    else if (keyword == "else") return ELSE_TOKEN;
    else if (keyword == "for") return FOR_TOKEN;
    else if (keyword == "return") return RETURN_TOKEN;
    else if (keyword == "DataFrame") return DATAFRAME_TOKEN;
    else if (keyword == "Algorithm") return ALGORITHM_TOKEN;
    else if (keyword == "DecisionTree") return DECISIONTREE_TOKEN;
    else if (keyword == "PROGRAM") return PROGRAM_TOKEN;
    else if (keyword == "FUNCTIONS") return FUNCTIONS_TOKEN;
    else if (keyword == "BEGIN") return BEGIN_TOKEN;
    else if (keyword == "END") return END_TOKEN;
    else return IDENTIFIER_TOKEN;
}

Token Lexer::get_token()
{
    string s;
    char ch = source.get_current_char();

    while (isspace(ch)) {
        source.consume_char();
        ch = source.get_current_char();
    }

    if (ch == EOF) {
        return Token(EOF_TOKEN, "eof", 0, 0);
    }

    s = ch;
    unsigned int line = source.get_line();
    unsigned int column = source.get_column();

    if (ch == '+') {
        source.consume_char();
        return Token(PLUS_TOKEN, s, line, column);
    }
    else if (ch == '-') {
        source.consume_char();
        return Token(MINUS_TOKEN, s, line, column);
    }
    else if (ch == '*') {
        source.consume_char();
        return Token(MULT_TOKEN, s, line, column);
    }
    else if (ch == '/') {
        source.consume_char();
        return Token(DIV_TOKEN, s, line, column);
    }
    else if (ch == '%') {
        source.consume_char();
        return Token(MOD_TOKEN, s, line, column);
    }
    else if (ch == '(') {
        source.consume_char();
        return Token(LEFT_PAREN_TOKEN, s, line, column);
    }
    else if (ch == ')') {
        source.consume_char();
        return Token(RIGHT_PAREN_TOKEN, s, line, column);
    }
    else if (ch == '{') {
        source.consume_char();
        return Token(LEFT_BRACE_TOKEN, s, line, column);
    }
    else if (ch == '}') {
        source.consume_char();
        return Token(RIGHT_BRACE_TOKEN, s, line, column);
    }
    else if (ch == ':') {
        source.consume_char();
        return Token(SEQUENCE_TOKEN, s, line, column);
    }
    else if (ch == ';') {
        source.consume_char();
        return Token(SEMICOLON_TOKEN, s, line, column);
    }
    else if (ch == '.') {
        source.consume_char();
        return Token(DOT_TOKEN, s, line, column);
    }
    else if (ch == ',') {
        source.consume_char();
        return Token(COMMA_TOKEN, s, line, column);
    }

    else if (ch == '=')
    {
        source.consume_char();
        if (source.get_current_char() == '=')
        {
            s += source.get_current_char();
            source.consume_char();
            return Token(EQUALS_TOKEN, s, line, column);
        }
        else
        {
            source.consume_char();
            return Token(ASSIGN_TOKEN, s, line, column);
        }
    }

    else if (ch == '<')
    {
        source.consume_char();
        if (source.get_current_char() == '=')
        {
            s += source.get_current_char();
            source.consume_char();
            return Token(LESS_EQ_TOKEN, s, line, column);
        }
        else
        {
            source.consume_char();
            return Token(LESS_TOKEN, s, line, column);
        }
    }

    else if (ch == '>')
    {
        source.consume_char();
        if (source.get_current_char() == '=')
        {
            s += source.get_current_char();
            source.consume_char();
            return Token(GREATER_EQ_TOKEN, s, line, column);
        }
        else
        {
            source.consume_char();
            return Token(GREATER_TOKEN, s, line, column);
        }
    }

    else if (ch == '!')
    {
        source.consume_char();
        if (source.get_current_char() == '=')
        {
            s += source.get_current_char();
            source.consume_char();
            return Token(NOT_EQUAL_TOKEN, s, line, column);
        }
        else
        {
            source.consume_char();
            return Token(ERROR_TOKEN, s, line, column);
        }
    }

    else if (isalpha(ch))
    {
        source.consume_char();
        while (isalnum(source.get_current_char()))
        {
            s += source.get_current_char();
            source.consume_char();
        }
        return Token(alphanum_token_type(s), s, line, column);
    }

    else if (isdigit(ch))
    {
        source.consume_char();
        while (isdigit(source.get_current_char()))
        {
            s += source.get_current_char();
            source.consume_char();
        }
        if (source.get_current_char() == '.')
        {
            s += source.get_current_char();
            source.consume_char();
            while (isdigit(source.get_current_char()))
            {
                s += source.get_current_char();
                source.consume_char();
            }
        }
        return Token(NUMBER_TOKEN, s, line, column);
    }

    else
    {
        source.consume_char();
        return Token(ERROR_TOKEN, "undefined token", line, column);
    }

}
