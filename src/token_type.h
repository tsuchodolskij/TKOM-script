#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H


enum TokenType {

// alpha
    INT_TOKEN, // 0
    FLOAT_TOKEN, // 1
    STRING_TOKEN, // 2
    IN_TOKEN, // 3
    IF_TOKEN, // 4
    ELSEIF_TOKEN, // 5
    ELSE_TOKEN, // 6
    FOR_TOKEN, // 7
    RETURN_TOKEN, // 8
    DATAFRAME_TOKEN, // 9
    ALGORITHM_TOKEN, // 10
    DECISIONTREE_TOKEN, // 11
    PROGRAM_TOKEN, // 12
    FUNCTIONS_TOKEN, // 13
    BEGIN_TOKEN, // 14
    END_TOKEN, // 15
    IDENTIFIER_TOKEN, // 16

// number
    NUMBER_TOKEN, // 17

// arithmetic operators
    PLUS_TOKEN, // 18
    MINUS_TOKEN, // 19
    MULT_TOKEN, // 20
    DIV_TOKEN, // 21
    MOD_TOKEN, // 22

// assigment operator
    ASSIGN_TOKEN, // 23

// logical operators
    GREATER_TOKEN, // 24
    LESS_TOKEN, // 25
    EQUALS_TOKEN, // 26
    GREATER_EQ_TOKEN, // 27
    LESS_EQ_TOKEN, // 28
    NOT_EQUAL_TOKEN, // 29

// other
    DOT_TOKEN, // 30
    COMMA_TOKEN, // 31
    LEFT_PAREN_TOKEN, // 32
    RIGHT_PAREN_TOKEN, // 33
    LEFT_BRACE_TOKEN, // 34
    RIGHT_BRACE_TOKEN, // 35
    SEQUENCE_TOKEN, // 36
    SEMICOLON_TOKEN, // 37
    EOF_TOKEN, // 38
    ERROR_TOKEN // 39
};

#endif
