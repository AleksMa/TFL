//
// Created by alexey on 22.12.2019.
//

#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H


#include "bits/stdc++.h"

using namespace std;



//https://ariya.io/2012/07/most-popular-javascript-tokens

enum token_type {
    // REMOVABLE
    COMMENT,
    NEWLINE,

    // DEFINITE TOKENS
    BREAK,
    CONTINUE,
    RETURN,
    FUNCTION,
    FOR,
    WHILE,
    IF,
    ELSE,
    VAR,
    LET,
    CONST,

    // STORABLE TOKENS
    STRING,
    BOOLEAN,
    NUMERIC,
    REGEXP,
    IDENTIFIER,
    OP_DOUBLED,
    OP_BINARY,
    OP_ASSIGN,
    OP_ADDITIVE,

    // DEFINITE TOKENS
    OP_EQUAL,
    OP_EXCLAMATION,     // восклицательный знак !
    NULL_LITERAL,
    SEMICOLON,          // точка с запятой ;
    POINT,
    COMMA,
    QUESTION,
    COLON,              // двоеточие :
    LEFT_ROUND,
    RIGHT_ROUND,
    LEFT_SQUARE,
    RIGHT_SQUARE,
    LEFT_CURLY,
    RIGHT_CURLY,

    UNKNOWN
};


class Token {
private:
    token_type type;
    string value;
    int pos;
    int col;
    int row;
    int table_index;

public:
    token_type get_type() const;

    string get_value() const;

    int get_line() const;
    int get_column() const;

    bool equalsClass(token_type type);

    string to_str() const;
    string to_str_extended() const;

    Token();
    Token(token_type type, string value);
    Token(token_type type, string value, int pos, int col, int row);
    Token(token_type type, string value, int pos, int col, int row, int table_value);

    static map<token_type, string> token_types;
};


#endif //LAB5_TOKEN_H
