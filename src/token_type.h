#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H


enum TokenType {

// alpha
    INT_TOKEN, // 0
    FLOAT_TOKEN, // 1
    STRING_TOKEN, // 2
    VOID_TOKEN, //3
    IN_TOKEN, // 4
    IF_TOKEN, // 5
    ELSEIF_TOKEN, // 6
    ELSE_TOKEN, // 7
    FOR_TOKEN, // 8
    RETURN_TOKEN, // 9
    DATAFRAME_TOKEN, // 10
    ALGORITHM_TOKEN, // 12
    DECISIONTREE_TOKEN, // 12
    PROGRAM_TOKEN, // 13
    FUNCTIONS_TOKEN, // 14
    BEGIN_TOKEN, // 15
    END_TOKEN, // 16
    IDENTIFIER_TOKEN, // 17

// number
    NUMBER_TOKEN, // 18

// arithmetic operators
    PLUS_TOKEN, // 19
    MINUS_TOKEN, // 20
    MULT_TOKEN, // 21
    DIV_TOKEN, // 22
    MOD_TOKEN, // 23

// assigment operator
    ASSIGN_TOKEN, // 24

// logical operators
    GREATER_TOKEN, // 25
    LESS_TOKEN, // 26
    EQUALS_TOKEN, // 27
    GREATER_EQ_TOKEN, // 28
    LESS_EQ_TOKEN, // 29
    NOT_EQUAL_TOKEN, // 30

// other
    DOT_TOKEN, // 31
    COMMA_TOKEN, // 32
    LEFT_PAREN_TOKEN, // 33
    RIGHT_PAREN_TOKEN, // 34
    LEFT_BRACE_TOKEN, // 35
    RIGHT_BRACE_TOKEN, // 36
    SEQUENCE_TOKEN, // 37
    SEMICOLON_TOKEN, // 38
    EOF_TOKEN, // 39
    ERROR_TOKEN // 40
};

#endif
