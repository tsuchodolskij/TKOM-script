#include <utility>

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <map>
#include "nodes.h"
#include "parser.h"

enum VarType {
    INT, BOOL
};

struct MemoryElement
{
    VarType varType;
    std::string value;

    MemoryElement() = default;

    MemoryElement(VarType varType1, std::string value1) : varType(varType1), value(std::move(value1))
    {}
};

struct SymbolDesc
{
    std::string type;
    std::string value;

    SymbolDesc() = default;

    SymbolDesc(std::string t) : type(t)
    {}

    SymbolDesc(std::string t, std::string v) : type(t), value(v)
    {}
};

struct FunctionDesc
{
    std::string type;
    std::vector<Parameter> parameters;
    std::vector<Node*> statements;

    FunctionDesc() = default;

    FunctionDesc(std::string t, std::vector<Parameter> p, std::vector<Node*> s) : type(t), parameters(p), statements(s)
    {}
};

class Interpreter {

    Parser& parser;
    ProgramNode* root;

    std::map<std::string, FunctionDesc> functions; // key: function->id, value: FunctionDesc
    std::vector<std::map<std::string, SymbolDesc>> symbols;


public:
    explicit Interpreter(Parser &p);

    void execute();

    void process_function(FunctionNode *pNode);

    void add_function_desc(FunctionNode *pNode);

    void process_statement(Node *pNode);

    void process_loop(LoopNode *pNode);

    void process_decision(DecisionNode *pNode);

    void process_declaration(DeclarationNode *pNode);

    void process_assignment(AssignmentNode *pNode);

    void process_function_call(FunctionCallNode *pNode);

    MemoryElement* getExpressionValue(Node *pNode);

    void call_function(FunctionCallNode *pNode);

    void run_printer(FunctionCallNode *pNode);

    MemoryElement* call_int_function(FunctionCallNode* node);
};


#endif //INTERPRETER_H
