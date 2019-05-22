#ifndef NODES_H
#define NODES_H

#include <vector>
#include <string>


enum NodeType
{
    PROGRAM_NODE, FUNCTION_NODE, LOOP_NODE, DECISION_NODE,
    DECLARATION_NODE, ASSIGNMENT_NODE, FUNCTION_CALL_NODE, EXPRESSION_NODE,
    RETURN_NODE, NUMBER_NODE, IDENTIFIER_NODE
};

struct Parameter
{
    std::string type;
    std::string id;

    Parameter(std::string type, std::string id)
    {
        this->type = std::move(type);
        this->id = std::move(id);
    }
};

struct Node
{
    NodeType node_type;

    virtual void to_string(std::string tabs)=0;
};

struct IdentifierNode : Node
{
    std::string id;

    IdentifierNode() : Node() {
        node_type = IDENTIFIER_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"IdentifierNode {"<<std::endl;
        std::cout<<tabs+" id: "<< id <<std::endl;
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct NumberNode : Node
{
    std::string value;
    bool negative;

    NumberNode() : Node() {
        node_type = NUMBER_NODE;
        negative = false;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"NumberNode {"<<std::endl;
        std::cout<<tabs+" negative: "<< negative <<std::endl;
        std::cout<<tabs+" value: "<< value <<std::endl;
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct ExpressionNode : Node
{
    std::string operation;
    Node* left = nullptr;
    Node* right = nullptr;

    ExpressionNode() : Node() {
        node_type = EXPRESSION_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"ExpressionNode {"<<std::endl;
        std::cout<<tabs+" operation: "<< operation <<std::endl;
        left->to_string(tabs+"\t");
        right->to_string(tabs+"\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct FunctionCallNode: Node
{
    std::string id;
    std::vector<Node*> arguments;

    FunctionCallNode() : Node() {
        node_type = FUNCTION_CALL_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"FunctionCallNode {"<<std::endl;
        std::cout<<tabs+" id: "<< id <<std::endl;
        for (auto &arg : arguments)
            arg->to_string(tabs+"\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct AssignmentNode: Node
{
    std::string id;
    Node* expression{};

    AssignmentNode() : Node() {
        node_type = ASSIGNMENT_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"AssignmentNode {"<<std::endl;
        std::cout<<tabs+" id: "<< id <<std::endl;
        expression->to_string(tabs + "\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct DeclarationNode: Node
{
    std::string type;
    std::string id;

    DeclarationNode() : Node() {
        node_type = DECLARATION_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"DeclarationNode {"<<std::endl;
        std::cout<<tabs+" type: "<< type <<std::endl;
        std::cout<<tabs+" id: "<< id <<std::endl;
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct DecisionNode: Node
{
    Node* condition{};
    std::vector<Node*> statements;

    DecisionNode() : Node() {
        node_type = DECISION_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"DecisionNode {"<<std::endl;
        condition->to_string(tabs + "\t");
        for (auto &st : statements)
            st->to_string(tabs+"\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct LoopNode : Node
{
    std::string id;
    std::vector<Node*> statements;
    int from;
    int to;

    LoopNode() : Node() {
        node_type = LOOP_NODE;
        from = -1;
        to = -1;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"LoopNode {"<<std::endl;
        std::cout<<tabs+" id: "<< id <<std::endl;
        std::cout<<tabs+" from: "<< from <<std::endl;
        std::cout<<tabs+" to: "<< to <<std::endl;
        for (auto &st : statements)
            st->to_string(tabs+"\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};


struct ReturnNode : Node
{
    Node* expression{};

    ReturnNode() : Node() {
        node_type = RETURN_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"ReturnNode {"<<std::endl;
        expression->to_string(tabs+"\t");
        std::cout<<tabs+"}"<<std::endl;
    }
};

struct FunctionNode : Node
{
    std::string type;
    std::string id;
    std::vector<Parameter> parameters;
    std::vector<Node*> statements;
    std::string param_type;

    FunctionNode() : Node() {
        node_type = FUNCTION_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<tabs+"FunctionNode {"<<std::endl;
        std::cout<<tabs+" type: "<<type<<std::endl;
        std::cout<<tabs+" id: "<<id<<std::endl;
        std::cout<<tabs+"Parameters: "<<std::endl;
        for (auto &par : parameters)
            std::cout<<tabs+" "<< par.type<<" "<<par.id<<std::endl;
        std::cout<<tabs+"Statements: "<<std::endl;
        for (auto &st : statements)
            st->to_string(tabs+"\t");

        std::cout<<tabs+"}"<<std::endl;
    }
};

struct ProgramNode : Node
{
    string program_name;
    std::vector<FunctionNode*> functions;
    std::vector<Node*> statements;

    ProgramNode() : Node() {
        node_type = PROGRAM_NODE;
    }

    void to_string(std::string tabs) override
    {
        std::cout<<"ProgramNode {"<<std::endl;
        std::cout<<tabs+" program_name: "<<program_name<<std::endl;
        std::cout<<tabs+"Functions: "<<std::endl;
        for (auto &fun : functions)
            fun->to_string(tabs + "\t");
        std::cout<<tabs+"Statements: "<<std::endl;
        for (auto &st : statements)
            st->to_string(tabs + "\t");
        std::cout<<"}"<<std::endl;
    }
};

#endif //NODES_H
