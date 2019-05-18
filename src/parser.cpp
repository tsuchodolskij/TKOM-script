#include <iostream>
#include <algorithm>
#include "parser.h"

Parser::Parser(Lexer& l): lexer(l) {
    token = lexer.get_token();
}

bool Parser::token_included(std::list<TokenType> token_type_list)
{
    auto it = std::find(token_type_list.begin(), token_type_list.end(), token.get_type());
    return it != token_type_list.end();
}

void Parser::accept(TokenType token_type) {
    if (token.get_type() == token_type) {
        cout << ">> Otrzymalem oczekiwany token: " << token.get_type() << endl;
    }
    else {
        cout << "ERROR: Oczekiwalem na: " << token_type << ", a otrzymalem: " << token.get_type() << endl;
    }
    token = lexer.get_token();
}

void Parser::accept(std::list<TokenType> token_type_list) {
    if(token_included(token_type_list)) {
        accept(token.get_type());
    }
    else {
        cout << "ERROR: Otrzymalem: " << token.get_type();
    }
}

void Parser::parse_file() {

    accept(PROGRAM_TOKEN);
    accept(IDENTIFIER_TOKEN);
    accept(FUNCTIONS_TOKEN);

    functions();

    accept(BEGIN_TOKEN);

    program_statements();

    accept(END_TOKEN);
    accept(EOF_TOKEN);
}

void Parser::functions() {

    while (token.get_type() != BEGIN_TOKEN) {
        accept(var_type_token);
        accept(IDENTIFIER_TOKEN);
        accept(LEFT_PAREN_TOKEN);

        function_arguments();

        accept(RIGHT_PAREN_TOKEN);
        accept(LEFT_BRACE_TOKEN);

        function_statements();

        accept(RETURN_TOKEN);
        accept(function_return_token);
        accept(SEMICOLON_TOKEN);
        accept(RIGHT_BRACE_TOKEN);
    }
}

// TODO dać wiele argumentów (dodać COMMA_TOKEN)
void Parser::function_arguments() {
    while (token.get_type() != RIGHT_PAREN_TOKEN) {
        accept(var_type_token);
        accept(IDENTIFIER_TOKEN);
    }
}

void Parser::function_statements() {
    while (token.get_type() != RETURN_TOKEN) {
        if (token_included(begin_statement_token)) statement();
    }
}

void Parser::program_statements() {
    while (token.get_type() != END_TOKEN) {
        while (token_included(begin_statement_token)) statement();
    }
}

void Parser::statement() {

    while (!token_included(end_statement_token)) {
        if (token.get_type() == FOR_TOKEN) {
            loop();
        }
        else if (token.get_type() == IF_TOKEN) {
            decision();
        }
        else if (token_included(simple_type_token)) {
            declaration();
        }
        else if (token.get_type() == DATAFRAME_TOKEN) {
            assignment();
        }
        else if (token.get_type() == DECISIONTREE_TOKEN) {
            function_call();
        }
        else if (token.get_type() == ALGORITHM_TOKEN) {
            analyze_algorithm_object();
        }
        else if (token.get_type() == IDENTIFIER_TOKEN) {
            accept(IDENTIFIER_TOKEN);
            if (token.get_type() == ASSIGN_TOKEN) {
                assignment();
            }
            else if (token.get_type() == LEFT_PAREN_TOKEN) {
                function_call();
            }
        }
    }
    accept(SEMICOLON_TOKEN);
}

void Parser::loop() {
    accept(FOR_TOKEN);
    accept(IDENTIFIER_TOKEN);
    accept(IN_TOKEN);
    accept(NUMBER_TOKEN);
    accept(SEQUENCE_TOKEN);
    accept(NUMBER_TOKEN);
    accept(LEFT_BRACE_TOKEN);
    while (token.get_type() != RIGHT_BRACE_TOKEN) {
        if (token_included(begin_statement_token)) statement();
    }
    accept(RIGHT_BRACE_TOKEN);
}

// TODO elseif else
void Parser::decision() {
    accept(IF_TOKEN);
    accept(LEFT_PAREN_TOKEN);
    /* LOGICAL_EXPRESSION = (IDENTIFIER, INT_NUMBER), LOGICAL_OPERATOR, (IDENTIFIER, INT_NUMBER) */
    accept(RIGHT_PAREN_TOKEN);
}

void Parser::declaration() {
    accept(simple_type_token);
    accept(IDENTIFIER_TOKEN);
}

// TODO przypisanie do pol obiektow
// TODO arithmetic operation
void Parser::assignment() {
    accept(IDENTIFIER_TOKEN);
    accept(ASSIGN_TOKEN);
    accept(value_token);
}

// TODO wiecej niz 1 arg
void Parser::function_call() {
    accept(IDENTIFIER_TOKEN);
    accept(LEFT_PAREN_TOKEN);
    if (token.get_type() != RIGHT_PAREN_TOKEN) {
        accept(value_token);
    }
    while (token.get_type() != RIGHT_PAREN_TOKEN) {
        // wiecej niz 1 arg
    }
    accept(RIGHT_PAREN_TOKEN);
}

void Parser::analyze_algorithm_object() {
    accept(ALGORITHM_TOKEN);
    accept(DOT_TOKEN);

}







/*
Token t;

while (t.get_type() != EOF_TOKEN) {
    t = lexer.get_token();

    switch (t.get_type()) {

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
            cout << "DATAFRAME_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case ALGORITHM_TOKEN:
            cout << "ALGORITHM_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case DECISIONTREE_TOKEN:
            cout << "DECISIONTREE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case PROGRAM_TOKEN:
            cout << "PROGRAM_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case FUNCTIONS_TOKEN:
            cout << "FUNCTIONS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case BEGIN_TOKEN:
            cout << "BEGIN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case END_TOKEN:
            cout << "END_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case IDENTIFIER_TOKEN:
            cout << "IDENTIFIER_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
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
            cout << "GREATER_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case LESS_TOKEN:
            cout << "LESS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case EQUALS_TOKEN:
            cout << "EQUALS_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case GREATER_EQ_TOKEN:
            cout << "GREATER_EQ_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case LESS_EQ_TOKEN:
            cout << "LESS_EQ_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case NOT_EQUAL_TOKEN:
            cout << "NOT_EQUAL_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;

        case DOT_TOKEN:
            cout << "DOT_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case LEFT_PAREN_TOKEN:
            cout << "LEFT_PAREN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case RIGHT_PAREN_TOKEN:
            cout << "RIGHT_PAREN_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case LEFT_BRACE_TOKEN:
            cout << "LEFT_BRACE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case RIGHT_BRACE_TOKEN:
            cout << "RIGHT_BRACE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case SEQUENCE_TOKEN:
            cout << "SEQUENCE_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case SEMICOLON_TOKEN:
            cout << "SEMICOLON_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;
        case EOF_TOKEN:
            cout << "EOF_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        case ERROR_TOKEN:
            cout << "ERROR_TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column() << endl;
            break;
        default:
            cout << "UNRECOGNIZED TOKEN : " << t.get_value() << "\t\t\t" << t.get_line() << ":" << t.get_column()
                 << endl;
            break;

    }
}*/
