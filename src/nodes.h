#ifndef NODES_H
#define NODES_H

#include <vector>
#include <string>


enum NodeType
{
    PROGRAM_NODE, FUNCTION_NODE, STATEMENT_NODE, LOOP_NODE, DECISION_NODE, DECLARATION_NODE, ASSIGNMENT_NODE, FUNCTION_CALL_NODE, EXPRESSION_NODE
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
};

struct ExpressionNode : Node
{
    std::string operation;
    Node* left = nullptr;
    Node* right = nullptr;

    ExpressionNode() : Node() {
        node_type = EXPRESSION_NODE;
    }
};

struct FunctionCallNode: Node
{
    std::string id;
    std::vector<Node*> arguments;

    FunctionCallNode() : Node() {
        node_type = FUNCTION_CALL_NODE;
    }
};

struct AssignmentNode: Node
{
    std::string id;
    std::string value;

    AssignmentNode() : Node() {
        node_type = ASSIGNMENT_NODE;
    }
};

struct DeclarationNode: Node
{
    std::string type;
    std::string id;

    DeclarationNode() : Node() {
        node_type = DECLARATION_NODE;
    }
};

struct DecisionNode: Node
{
    Node* condition;
    std::vector<Node*> statements;


    DecisionNode() : Node() {
        node_type = DECISION_NODE;
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
};

struct StatementNode : Node
{
    StatementNode() : Node() {
        node_type = STATEMENT_NODE;
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
};

struct ProgramNode : Node
{
    string program_name;
    std::vector<FunctionNode*> functions;
    std::vector<Node*> statements;

    ProgramNode() : Node() {
        node_type = PROGRAM_NODE;
    }
};

#endif //NODES_H
