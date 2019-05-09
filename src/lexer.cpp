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

void Lexer::process_file()
{
    Token t;

    while (t.get_type() != EOF_TOKEN)
    {
        t = get_token();

        switch (t.get_type())
        {

        case INT_TOKEN:
            cout << "INT_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case FLOAT_TOKEN:
            cout << "FLOAT_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case STRING_TOKEN:
            cout << "STRING_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case NUMBER_TOKEN:
            cout << "NUMBER_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case IN_TOKEN:
            cout << "IN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case IF_TOKEN:
            cout << "IF_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case ELSEIF_TOKEN:
            cout << "ELSEIF_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case ELSE_TOKEN:
            cout << "ELSE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case FOR_TOKEN:
            cout << "FOR_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case RETURN_TOKEN:
            cout << "RETURN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case DATAFRAME_TOKEN:
            cout << "DATAFRAME_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case ALGORITHM_TOKEN:
            cout << "ALGORITHM_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case DECISIONTREE_TOKEN:
            cout << "DECISIONTREE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case PROGRAM_TOKEN:
            cout << "PROGRAM_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case FUNCTIONS_TOKEN:
            cout << "FUNCTIONS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case BEGIN_TOKEN:
            cout << "BEGIN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case END_TOKEN:
            cout << "END_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case IDENTIFIER_TOKEN:
            cout << "IDENTIFIER_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;

        case PLUS_TOKEN:
            cout << "PLUS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case MINUS_TOKEN:
            cout << "MINUS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case MULT_TOKEN:
            cout << "MULT_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case DIV_TOKEN:
            cout << "DIV_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case MOD_TOKEN:
            cout << "MOD_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;

        case ASSIGN_TOKEN:
            cout << "ASSIGN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;

        case GREATER_TOKEN:
            cout << "GREATER_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case LESS_TOKEN:
            cout << "LESS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case EQUALS_TOKEN:
            cout << "EQUALS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case GREATER_EQ_TOKEN:
            cout << "GREATER_EQ_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case LESS_EQ_TOKEN:
            cout << "LESS_EQ_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case NOT_EQUAL_TOKEN:
            cout << "NOT_EQUAL_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;

        case DOT_TOKEN:
            cout << "DOT_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case LEFT_PAREN_TOKEN:
            cout << "LEFT_PAREN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case RIGHT_PAREN_TOKEN:
            cout << "RIGHT_PAREN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case LEFT_BRACE_TOKEN:
            cout << "LEFT_BRACE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case RIGHT_BRACE_TOKEN:
            cout << "RIGHT_BRACE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case SEQUENCE_TOKEN:
            cout << "SEQUENCE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case SEMICOLON_TOKEN:
            cout << "SEMICOLON_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case EOF_TOKEN:
            cout << "EOF_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case ERROR_TOKEN:
            cout << "ERROR_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        default:
            cout << "UNRECOGNIZED TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;

        }
    }
}



