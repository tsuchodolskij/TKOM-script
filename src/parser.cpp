#include <utility>

#include <utility>

#include <iostream>
#include <algorithm>
#include "parser.h"

Parser::Parser(Lexer& l): lexer(l) {
    token = lexer.get_token();
    is_buffered = false;
}

bool Parser::token_included(std::list<TokenType> token_type_list)
{
    auto it = std::find(token_type_list.begin(), token_type_list.end(), token.get_type());
    return it != token_type_list.end();
}

void Parser::read_to_buffer() {
    buffer = lexer.get_token();
    is_buffered = true;
}

void Parser::accept(TokenType token_type) {
    if (token.get_type() == token_type) {
        cout << ">> Otrzymalem oczekiwany token: " << token.get_type() << endl;
        if (is_buffered) {
            token = buffer;
            is_buffered = false;
        }
        else {
            token = lexer.get_token();
        }
    }
    else {
        cout << "ERROR: Oczekiwalem na: " << token_type << ", a otrzymalem: " << token.get_type() << endl;
    }
}

void Parser::accept(TokenType token_type, Node* node) {
    if(token.get_type() == token_type) {
        create_node(node);
        if(is_buffered) {
            token = buffer;
            is_buffered = false;
        }
        else {
            token = lexer.get_token();
        }
    }
    else {
        cout << "ERROR: Oczekiwalem na: " << token_type << ", a otrzymalem: " << token.get_type() << endl;
    }
}

void Parser::accept(std::list<TokenType> token_type_list) {
    if(token_included(std::move(token_type_list))) {
        accept(token.get_type());
    }
    else {
        cout << "ERROR: Otrzymalem: " << token.get_type();
    }
}

void Parser::accept(std::list<TokenType> token_type_list, Node* node) {
    if(token_included(std::move(token_type_list))) {
        accept(token.get_type(), node);
    }
    else {
        cout << "ERROR: Otrzymalem: " << token.get_type();
    }
}

ProgramNode* Parser::program() {

    auto* node = new ProgramNode();

    accept(PROGRAM_TOKEN);
    accept(IDENTIFIER_TOKEN, node);
    accept(FUNCTIONS_TOKEN);

    while (token.get_type() != BEGIN_TOKEN) {
        node->functions.push_back(function());
    }

    accept(BEGIN_TOKEN);

    while (token.get_type() != END_TOKEN) {
        node->statements.push_back(statement());
    }

    accept(END_TOKEN);
    accept(EOF_TOKEN);

    return node;
}

FunctionNode* Parser::function() {

    auto* node = new FunctionNode();

    accept(var_type_token, node);
    accept(IDENTIFIER_TOKEN, node);
    accept(LEFT_PAREN_TOKEN);

    set_function_parameters(node);

    accept(RIGHT_PAREN_TOKEN);
    accept(LEFT_BRACE_TOKEN);

    while (token.get_type() != RETURN_TOKEN) {
        node->statements.push_back(statement());
    }

    accept(RETURN_TOKEN);
    accept(function_return_token);
    accept(SEMICOLON_TOKEN);
    accept(RIGHT_BRACE_TOKEN);

    return node;
}

void Parser::set_function_parameters(FunctionNode* node) {
    if (token.get_type() != RIGHT_PAREN_TOKEN) {
        accept(var_type_token, node);
        accept(IDENTIFIER_TOKEN, node);
        if (token.get_type() == COMMA_TOKEN) {
            while (token.get_type() != RIGHT_PAREN_TOKEN) {
                accept(COMMA_TOKEN);
                accept(var_type_token, node);
                accept(IDENTIFIER_TOKEN, node);
            }
        }
    }
}

Node* Parser::statement() {

    Node *node = nullptr;

    if (token.get_type() == FOR_TOKEN) {
        node = loop();
    }
    else if (token.get_type() == IF_TOKEN) {
        node = decision();
    }
    else if (token_included(simple_type_token)) {
        node = declaration();
        accept(SEMICOLON_TOKEN);
    }
    else if (token.get_type() == DATAFRAME_TOKEN) {
//            assignment();
    }
    else if (token.get_type() == DECISIONTREE_TOKEN) {
//            function_call();
    }
    else if (token.get_type() == ALGORITHM_TOKEN) {
//            ...
    }
    else if (token.get_type() == IDENTIFIER_TOKEN) {
        read_to_buffer();
        if (buffer.get_type() == ASSIGN_TOKEN) {
            node = assignment();
            accept(SEMICOLON_TOKEN);
        }
        else if (buffer.get_type() == LEFT_PAREN_TOKEN) {
            node = function_call();
            accept(SEMICOLON_TOKEN);
        }
    }

    return node;
}

LoopNode* Parser::loop() {

    auto* node = new LoopNode();

    accept(FOR_TOKEN);
    accept(IDENTIFIER_TOKEN, node);
    accept(IN_TOKEN);
    accept(NUMBER_TOKEN, node);
    accept(SEQUENCE_TOKEN);
    accept(NUMBER_TOKEN, node);
    accept(LEFT_BRACE_TOKEN);

    while (token.get_type() != RIGHT_BRACE_TOKEN) {
        node->statements.push_back(statement());
    }

    accept(RIGHT_BRACE_TOKEN);
    return node;
}

// TODO elseif else, logical expression
DecisionNode* Parser::decision() {

    auto* node = new DecisionNode();

    accept(IF_TOKEN);
    accept(LEFT_PAREN_TOKEN);
    /* LOGICAL_EXPRESSION = (IDENTIFIER, INT_NUMBER), LOGICAL_OPERATOR, (IDENTIFIER, INT_NUMBER) */
    //node->condition = expression();
    accept(RIGHT_PAREN_TOKEN);
    accept(LEFT_BRACE_TOKEN);

    while (token.get_type() != RIGHT_BRACE_TOKEN) {
        node->statements.push_back(statement());
    }

    accept(RIGHT_BRACE_TOKEN);

    return node;
}

DeclarationNode* Parser::declaration() {

    auto* node = new DeclarationNode();

    accept(simple_type_token, node);
    accept(IDENTIFIER_TOKEN, node);

    return node;
}

// TODO przypisanie do pol obiektow, expression
AssignmentNode* Parser::assignment() {

    auto* node = new AssignmentNode();

    accept(IDENTIFIER_TOKEN, node);
    accept(ASSIGN_TOKEN);
    accept(value_token, node);

    return node;
}

// TODO dac expression do value_token
FunctionCallNode* Parser::function_call() {

    auto* node = new FunctionCallNode();

    accept(IDENTIFIER_TOKEN, node);
    accept(LEFT_PAREN_TOKEN);
    if (token.get_type() != RIGHT_PAREN_TOKEN) {
        accept(value_token, node);
        if(token.get_type() == COMMA_TOKEN) {
            while (token.get_type() != RIGHT_PAREN_TOKEN) {
                accept(COMMA_TOKEN);
                accept(value_token, node);
            }
        }
    }
    accept(RIGHT_PAREN_TOKEN);

    return node;
}

void Parser::create_node(Node *node) {

    switch (node->node_type) {
        case PROGRAM_NODE: {
            auto* theNode = (ProgramNode*) node;
            if (theNode->program_name.empty()) theNode -> program_name = token.get_value();
            break;
        }
        case FUNCTION_NODE: {
            auto* theNode = (FunctionNode*) node;
            if (theNode->type.empty()) theNode->type = token.get_value();
            else if (theNode->id.empty()) theNode->id = token.get_value();
            else if (theNode->param_type.empty()) theNode->param_type = token.get_value();
            else {
                theNode->parameters.emplace_back(theNode->param_type, token.get_value());
                theNode->param_type.clear();
            }
        }
        case STATEMENT_NODE: {
            break;
        }
        case LOOP_NODE: {
            auto* theNode = (LoopNode*) node;
            if (theNode->id.empty()) theNode->id = token.get_value();
            else if (theNode->from == -1) theNode->from = stoi(token.get_value());
            else if (theNode->to == -1) theNode->from = stoi(token.get_value());
        }
        case DECISION_NODE: {
            break;
        }
        case DECLARATION_NODE: {
            auto* theNode = (DeclarationNode*) node;
            if (theNode->type.empty()) theNode->type = token.get_value();
            else if (theNode->id.empty()) theNode->id = token.get_value();
            break;
        }
        case ASSIGNMENT_NODE: {
            auto* theNode = (AssignmentNode*) node;
            if (theNode->id.empty()) theNode->id = token.get_value();
            else if (theNode->value.empty()) theNode->value = token.get_value();
            break;
        }
        case FUNCTION_CALL_NODE: {
            auto* theNode = (FunctionCallNode*) node;
            if (theNode->id.empty()) theNode->id = token.get_value();
            break;
        }
    }
    cout << ">> CREATE_NODE value assigned: " << token.get_value() << std::endl;
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
