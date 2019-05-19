#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "nodes.h"
#include <list>

class Parser {

private:
    Lexer& lexer;
    Token token;
    Token buffer;
    bool is_buffered;
    std::list<TokenType> simple_type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN};
    std::list<TokenType> var_type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, DATAFRAME_TOKEN, ALGORITHM_TOKEN, DECISIONTREE_TOKEN};
    std::list<TokenType> function_return_token = {IDENTIFIER_TOKEN, NUMBER_TOKEN};
    std::list<TokenType> value_token = {IDENTIFIER_TOKEN, NUMBER_TOKEN};
    std::list<TokenType> arithm_operator_token = {PLUS_TOKEN, MINUS_TOKEN, MULT_TOKEN, DIV_TOKEN, MOD_TOKEN};

public:
    explicit Parser(Lexer& l);
    ProgramNode* program();
    FunctionNode* function();
    void set_function_parameters(FunctionNode* node);
    Node* statement();
    LoopNode* loop();
    DecisionNode* decision();
    DeclarationNode* declaration();
    AssignmentNode* assignment();
    FunctionCallNode* function_call();
    bool token_included(std::list<TokenType> token_type_list);
    void read_to_buffer();
    void accept(TokenType token_type);
    void accept(TokenType token_type, Node* node);
    void accept(std::list<TokenType> token_type_list);
    void accept(std::list<TokenType> token_type_list, Node* node);
    void create_node(Node *node);
};

#endif
