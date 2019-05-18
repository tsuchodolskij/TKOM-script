#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <list>

class Parser {

private:
    Lexer& lexer;
    Token token;
    std::list<TokenType> simple_type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN};
    std::list<TokenType> var_type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, DATAFRAME_TOKEN, ALGORITHM_TOKEN, DECISIONTREE_TOKEN};
    std::list<TokenType> function_return_token = {IDENTIFIER_TOKEN, NUMBER_TOKEN};
    std::list<TokenType> begin_statement_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, IF_TOKEN, FOR_TOKEN, DATAFRAME_TOKEN,
                                                  ALGORITHM_TOKEN, DECISIONTREE_TOKEN, IDENTIFIER_TOKEN};
    std::list<TokenType> end_statement_token = {SEMICOLON_TOKEN, RIGHT_BRACE_TOKEN};
    std::list<TokenType> value_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, IDENTIFIER_TOKEN, NUMBER_TOKEN};
    std::list<TokenType> arithm_operator_token = {PLUS_TOKEN, MINUS_TOKEN, MULT_TOKEN, DIV_TOKEN, MOD_TOKEN};

public:
    explicit Parser(Lexer& l);
    void parse_file();
    void functions();
    void function_arguments();
    void function_statements();
    void program_statements();
    void statement();
    void loop();
    void decision();
    void declaration();
    void assignment();
    void function_call();
    void analyze_algorithm_object();
    bool token_included(std::list<TokenType> token_type_list);
    void accept(TokenType token_type);
    void accept(std::list<TokenType> token_type_list);
};

#endif
