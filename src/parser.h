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
    std::list<TokenType> var_type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, DATAFRAME_TOKEN, ALGORITHM_TOKEN, DECISIONTREE_TOKEN};
    std::list<TokenType> type_token = {INT_TOKEN, FLOAT_TOKEN, STRING_TOKEN, VOID_TOKEN, DATAFRAME_TOKEN, ALGORITHM_TOKEN, DECISIONTREE_TOKEN};
    std::list<TokenType> operator_token = {PLUS_TOKEN, MINUS_TOKEN, MULT_TOKEN, DIV_TOKEN, MOD_TOKEN,
                                           GREATER_TOKEN, LESS_TOKEN, EQUALS_TOKEN, GREATER_EQ_TOKEN, LESS_EQ_TOKEN, NOT_EQUAL_TOKEN};
    std::list<TokenType> prioritized_operator_token = {MULT_TOKEN, DIV_TOKEN, MOD_TOKEN, GREATER_TOKEN, LESS_TOKEN,
                                                       EQUALS_TOKEN, GREATER_EQ_TOKEN, LESS_EQ_TOKEN, NOT_EQUAL_TOKEN};
    std::list<TokenType> non_prioritized_operator_token = {PLUS_TOKEN, MINUS_TOKEN};

public:
    explicit Parser(Lexer& l);
    ProgramNode* program();
    FunctionNode* function();
    void set_function_parameters(FunctionNode* node);
    Node* statement();
    Node* prioritized_extension();
    Node* non_prioritized_extension();
    ExpressionNode* extend(Node* node);
    ReturnNode* function_return();
    LoopNode* loop();
    DecisionNode* decision();
    DeclarationNode* declaration();
    AssignmentNode* assignment();
    FunctionCallNode* function_call();
    IdentifierNode* identifier();
    NumberNode* number();
    Node* lexical_atom();
    Node* expression();
    Node* paren_expression();
    bool token_included(std::list<TokenType> token_type_list);
    void read_to_buffer();
    void accept(TokenType token_type);
    void accept(TokenType token_type, Node* node);
    void accept(std::list<TokenType> token_type_list);
    void accept(std::list<TokenType> token_type_list, Node* node);
    void create_node(Node *node);
};

#endif
