//
// Created by alexey on 22.12.2019.
//

#include "Token.h"


map<token_type, string> Token::token_types = {
        {COMMENT,      "COM"},
        {NEWLINE,      "NL"},
        {STRING,       "STR"},
        {NULL_LITERAL, "NULL"},
        {BOOLEAN,      "BOOL"},
        {NUMERIC,      "NUM"},
        {REGEXP,       "RE"},
        {IDENTIFIER,   "IDENT"},
        {PUNCTUATOR,   "PUNCT"},
        {KEYWORD,      "KW"},
        {UNKNOWN,      "UNKNOWN"}
};

//map<token_type, string> Token::token_types = {
//        {COMMENT,        "COMMENT"},
//        {NEWLINE,        "NEWLINE"},
//        {STRING,         "STRING"},
//        {NULL_LITERAL,   "NULL_LITERAL"},
//        {BOOLEAN,        "BOOLEAN"},
//        {NUMERIC,        "NUMERIC"},
//        {REGEXP,         "REGEXP"},
//        {IDENTIFIER, "IDENTIFIER"},
//        {PUNCTUATOR,    "PUNCTUATOR"},
//        {KEYWORD,        "KEYWORD"},
//        {UNKNOWN,        "UNKNOWN"}
//};

Token::Token(token_type type, string value) : type(type), value(value) {}

Token::Token() {}

string Token::to_str() const {
           return "{" + token_types[type] +
                  (type != NEWLINE && type != NULL_LITERAL ? ", " + to_string(table_index) : "") +
                  ", " + to_string(row) + ":" + to_string(col) + "}";
}

string Token::to_str_extended() const {
    return "{" + token_types[type] +
           (type != NEWLINE && type != NULL_LITERAL ? ", index: " + to_string(table_index) : "") +
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

Token::Token(token_type type, const string &value, int pos, int col, int row, int table_value) : type(type), value(value),
                                                                                                 pos(pos), col(col + 1),
                                                                                                 row(row + 1),
                                                                                                 table_index(table_value) {}

bool Token::equalsClass(token_type type) {
    return this->type == type;
}

bool Token::equals(string value) {
    return this->value == value;
}
