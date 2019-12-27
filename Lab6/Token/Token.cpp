//
// Created by alexey on 22.12.2019.
//

#include "Token.h"

Token::Token(token_type type, string value) : type(type), value(value) {}

Token::Token() {}

string Token::to_str() const {
    return "{" + token_types[type] +
           (STRING <= type && type <= OP_ADDITIVE ? ", " + to_string(table_index) : "") +
           ", " + to_string(row) + ":" + to_string(col) + "}";
}

string Token::to_str_extended() const {
    return "{" + token_types[type] +
           (STRING <= type && type <= OP_ADDITIVE ? ", index: " + to_string(table_index) : "") +
           ", pos: " + to_string(row) + ":" + to_string(col) + "}";
}

void Token::set_position(int lineNumber, int columnNumber, int posNumber) {
    pos = lineNumber + 1;
    col = columnNumber + 1;
    row = pos;
}


token_type Token::get_type() const {
    return type;
}

string Token::get_value() const {
    return value;
}

int Token::get_line() const {
    return row;
}

int Token::get_column() const {
    return col;
}

int Token::start() const {
    return pos;
}

int Token::end() const {
    return pos + value.size();
}

Token::Token(token_type type, string value, int pos, int col, int row) :
        type(type), value(value), pos(pos), col(col + 1), row(row + 1) {}

Token::Token(token_type type, string value, int pos, int col, int row, int table_value) : type(type),
                                                                                                 value(value),
                                                                                                 pos(pos), col(col + 1),
                                                                                                 row(row + 1),
                                                                                                 table_index(
                                                                                                         table_value) {}

bool Token::equalsClass(token_type type) {
    return this->type == type;
}

bool Token::equals(string value) {
    return this->value == value;
}


map<token_type, string> Token::token_types = {
        // REMOVABLE TOKENS
        {COMMENT,        "COMMENT"},
        {NEWLINE,        "NEWLINE"},

        // STORABLE TOKENS
        {STRING,         "STRING"},
        {BOOLEAN,        "BOOLEAN"},
        {NUMERIC,        "NUMERIC"},
        {REGEXP,         "REGEXP"},
        {IDENTIFIER,     "IDENTIFIER"},
        {OP_DOUBLED,     "OP_DOUBLED"},
        {OP_ADDITIVE,    "OP_ADDITIVE"},
        {OP_BINARY,      "OP_BINARY"},
        {OP_ASSIGN,      "OP_ASSIGN"},

        // DEFINITE TOKENS
        {OP_EQUAL,       "OP_EQUAL"},
        {OP_EXCLAMATION, "OP_EXCLAMATION"},     // восклицательный знак !
        {NULL_LITERAL,   "NULL_LITERAL"},
        {SEMICOLON,      "SEMICOLON"},          // точка с запятой ;
        {POINT,          "POINT"},
        {COMMA,          "COMMA"},
        {QUESTION,       "QUESTION"},
        {COLON,          "COLON"},              // двоеточие :
        {LEFT_ROUND,     "LEFT_ROUND"},
        {RIGHT_ROUND,    "RIGHT_ROUND"},
        {LEFT_SQUARE,    "LEFT_SQUARE"},
        {RIGHT_SQUARE,   "RIGHT_SQUARE"},
        {LEFT_CURLY,     "LEFT_CURLY"},
        {RIGHT_CURLY,    "RIGHT_CURLY"},
        {BREAK,          "BREAK"},
        {CONTINUE,       "CONTINUE"},
        {RETURN,         "RETURN"},
        {FUNCTION,       "FUNCTION"},
        {FOR,            "FOR"},
        {WHILE,          "WHILE"},
        {IF,             "IF"},
        {ELSE,           "ELSE"},
        {VAR,            "VAR"},
        {LET,            "LET"},
        {CONST,          "CONST"},
        {UNKNOWN,        "UNKNOWN"}
};