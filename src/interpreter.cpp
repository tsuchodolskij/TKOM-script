#include "interpreter.h"

Interpreter::Interpreter(Parser &p) : parser(p) {
    root = parser.program();
    std::map<std::string, SymbolDesc> rootMap;
    symbols.push_back(rootMap);
}

void Interpreter::execute() {
    root->to_string("");

    for (auto & function : root->functions) {
        process_function(function);
    }

    for (auto & statement : root->statements) {
        process_statement(statement);
    }
}

void Interpreter::process_function(FunctionNode *pNode) {
    add_function_desc(pNode);

    if (pNode->type == "void") {
        for (auto & statement : pNode->statements) {
            if (statement->node_type == RETURN_NODE) {
                std::cout << "void + return statement" << std::endl;
            }
        }
    }
}

void Interpreter::add_function_desc(FunctionNode *pNode) {
    functions[pNode->id] = FunctionDesc(pNode->type, pNode->parameters, pNode->statements);
    // TODO
    //symbols_array.push_back(emb_symbols_array);
}

void Interpreter::process_statement(Node *pNode) {
    switch(pNode->node_type)
    {
        case LOOP_NODE:
            process_loop((LoopNode*) pNode);
            break;
        case DECISION_NODE:
            process_decision((DecisionNode*) pNode);
            break;
        case DECLARATION_NODE:
            process_declaration((DeclarationNode*) pNode);
            break;
        case ASSIGNMENT_NODE:
            process_assignment((AssignmentNode*) pNode);
            break;
        case FUNCTION_CALL_NODE:
            process_function_call((FunctionCallNode*) pNode);
            break;
        default:
            break;
    }
}

void Interpreter::process_loop(LoopNode *pNode) {
    std::map<std::string, SymbolDesc> newScope;
    symbols.push_back(newScope);

    symbols.back()[pNode->id] = SymbolDesc("int");

    for (int i = pNode->from; i <= pNode->to; i++) {
        symbols.back().find(pNode->id)->second.value = std::to_string(i);
        for (auto & statement : pNode->statements) {
            process_statement(statement);
        }
    }

    symbols.pop_back();
}

void Interpreter::process_decision(DecisionNode *pNode) {
    std::map<std::string, SymbolDesc> newScope;
    symbols.push_back(newScope);

    if (std::stoi(getExpressionValue(pNode->condition)->value) == 1) {
        for (auto & statement : pNode->if_statements) {
            process_statement(statement);
        }
    }
    else {
        for (auto & statement : pNode->else_statements) {
            process_statement(statement);
        }
    }

    symbols.pop_back();
}

void Interpreter::process_declaration(DeclarationNode *pNode) {
    if (symbols.back().count(pNode->id) != 0) {
        std::cout << "jest juz taka zmienna" << std::endl;
    }
    else {
        symbols.back()[pNode->id] = SymbolDesc(pNode->type);
    }
}

void Interpreter::process_assignment(AssignmentNode *pNode) {
    int mapIndex = symbols.size() - 1;
    while (mapIndex >= 0) {
        if (symbols[mapIndex].count(pNode->id) != 0) break;
        mapIndex--;
    }
    if (mapIndex == -1) std::cout << "nie ma takiej zmiennej" << std::endl;
    else {
        MemoryElement* element = getExpressionValue(pNode->expression);
        symbols[mapIndex].find(pNode->id)->second.value = element->value;
    }
}

void Interpreter::process_function_call(FunctionCallNode *pNode) {
    if (pNode->id == "print") {
        run_printer(pNode);
        return;
    }

    if (functions.count(pNode->id) == 0) {
        std::cout << "funkcja nie istnieje" << std::endl;
        return;
    }

    if (functions.find(pNode->id)->second.type != "void") {
        std::cout << "funkcja nie jest void" << std::endl;
        return;
    }

    if (pNode->arguments.size() != functions.find(pNode->id)->second.parameters.size()) {
        std::cout << "nieodpowiednia liczba argumentow" << std::endl;
        return;
    }

    call_function(pNode);
}

void Interpreter::call_function(FunctionCallNode *pNode) {
    std::map<std::string, SymbolDesc> newScope;
    symbols.push_back(newScope);

    for (int i = 0; i < pNode->arguments.size(); i++) {
        MemoryElement* elem = getExpressionValue(pNode->arguments[i]);
        symbols.back()[functions.find(pNode->id)->second.parameters[i].id] =
                SymbolDesc("int", elem->value);
    }

    for (auto & statement : functions.find(pNode->id)->second.statements) {
        process_statement(statement);
    }

    symbols.pop_back();
}

MemoryElement* Interpreter::getExpressionValue(Node *pNode) {
    switch(pNode->node_type) {

        case FUNCTION_CALL_NODE: {
            auto node = (FunctionCallNode *) pNode;

            if (functions.count(node->id) == 0) {
                std::cout << "funkcja nie istnieje" << std::endl;
                return new MemoryElement(VarType::INT, "0");
            }

            if (functions.find(node->id)->second.type != "int") {
                std::cout << "funkcja nie jest int" << std::endl;
                return new MemoryElement(VarType::INT, "0");
            }

            if (node->arguments.size() != functions.find(node->id)->second.parameters.size()) {
                std::cout << "nieodpowiednia liczba argumentow" << std::endl;
                return new MemoryElement(VarType::INT, "0");
            }

            return call_int_function(node);
        }

        case EXPRESSION_NODE: {
            auto node = (ExpressionNode *) pNode;
            int value = 0;
            MemoryElement* leftElement = getExpressionValue(node->left);
            MemoryElement* rightElement = getExpressionValue(node->right);
            if (node->operation == "+") {
                value = std::stoi(leftElement->value) + std::stoi(rightElement->value);
                return new MemoryElement(VarType::INT, std::to_string(value));
            }
            if (node->operation == "-") {
                value = std::stoi(leftElement->value) - std::stoi(rightElement->value);
                return new MemoryElement(VarType::INT, std::to_string(value));
            }
            if (node->operation == "/") {
                value = std::stoi(leftElement->value) / std::stoi(rightElement->value);
                return new MemoryElement(VarType::INT, std::to_string(value));
            }
            if (node->operation == "*") {
                value = std::stoi(leftElement->value) * std::stoi(rightElement->value);
                return new MemoryElement(VarType::INT, std::to_string(value));
            }
            if (node->operation == "%") {
                value = std::stoi(leftElement->value) % std::stoi(rightElement->value);
                return new MemoryElement(VarType::INT, std::to_string(value));
            }
            if (node->operation == "==") {
                value = std::stoi(leftElement->value) == std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
            if (node->operation == "!=") {
                value = std::stoi(leftElement->value) != std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
            if (node->operation == "<") {
                value = std::stoi(leftElement->value) < std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
            if (node->operation == ">") {
                value = std::stoi(leftElement->value) > std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
            if (node->operation == "<=") {
                value = std::stoi(leftElement->value) <= std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
            if (node->operation == ">=") {
                value = std::stoi(leftElement->value) >= std::stoi(rightElement->value) ? 1 : 0;
                return new MemoryElement(VarType::BOOL, std::to_string(value));
            }
        }

        case NUMBER_NODE: {
            auto node = (NumberNode *) pNode;
            std::string element_value;
            if (node->negative) element_value += "-";
            element_value += node->value;
            return new MemoryElement(VarType::INT, element_value);
        }

        case IDENTIFIER_NODE: {
            auto node = (IdentifierNode *) pNode;
            int mapIndex = symbols.size() - 1;
            while (mapIndex >= 0) {
                if (symbols[mapIndex].count(node->id) != 0) break;
                mapIndex--;
            }
            if (mapIndex == -1) std::cout << "nie ma takiej zmiennej" << std::endl;
            else {
                if (symbols[mapIndex].find(node->id)->second.type == "int") {
                    return new MemoryElement(VarType::INT, symbols[mapIndex].find(node->id)->second.value);
                }
                else {
                    std::cout << "niepoprawny typ zmiennej" << std::endl;
                }
            }
        }

        case RETURN_NODE: {
            auto node = (ReturnNode *) pNode;
            MemoryElement* elem = getExpressionValue(node->expression);
            return elem;
        }

        default:
            break;
    }
    return nullptr;
}

MemoryElement *Interpreter::call_int_function(FunctionCallNode* node) {
    std::map<std::string, SymbolDesc> newScope;
    symbols.push_back(newScope);
    bool flag = false;

    for (int i = 0; i < node->arguments.size(); i++) {
        MemoryElement* elem = getExpressionValue(node->arguments[i]);
        symbols.back()[functions.find(node->id)->second.parameters[i].id] =
                SymbolDesc("int", elem->value);
    }

    MemoryElement* element;
    for (auto statement : functions.find(node->id)->second.statements) {
        if (statement->node_type == RETURN_NODE) {
            element = getExpressionValue(statement);
            flag = true;
        }
        if (flag) break;
        process_statement(statement);
    }

    symbols.pop_back();

    if (flag) return element;
    else {
        return new MemoryElement(VarType::INT, "0");
    }
}

void Interpreter::run_printer(FunctionCallNode *pNode) {
    if (pNode->arguments.empty()) {
        std::cout << "niepoprawna ilosc argumentow w print" << std::endl;
        return;
    }
    std::cout << ">> " << getExpressionValue(pNode->arguments[0])->value << endl;
}

