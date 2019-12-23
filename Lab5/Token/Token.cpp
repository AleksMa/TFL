//
// Created by alexey on 22.12.2019.
//

#include "Token.h"

map<TokenType, string> Token::tokenTypes = {
        {COMMENT,        "COMMENT"}, // 0
        {NEWLINE,        "NEWLINE"}, // 1
        {STRING,         "STRING"}, // 2
        {NULL_LITERAL,   "NULL_LITERAL"}, // 3
        {BOOLEAN,        "BOOLEAN"},// 4
        {NUMERIC,        "NUMERIC"}, // 5
        {REGEXP,         "REGEXP"}, // 6
        {IDENTIFICATION, "IDENTIFICATION"}, // 7
        {PUNCTUATION,    "PUNCTUATION"}, // 8
        {KEYWORD,        "KEYWORD"}, // 9
        {UNKNOWN,        "UNKNOWN"} // 10
};

Token::Token(TokenType type, string value) : type(type), value(value) {}

Token::Token() {}

string Token::toString() const {
    //return "{token: " + value + ", type: " + tokenTypes[type] + ", position: " + to_string(row) + ":" + to_string(col) + "}";
    return "{type: " + tokenTypes[type] +
           (type != NEWLINE && type != NULL_LITERAL ? ", index: " + to_string(tableValue) : "") +
           ", position: " + to_string(row) + ":" + to_string(col) + "}";
}

void Token::setPosition(int lineNumber, int columnNumber, int posNumber) {
    pos = lineNumber + 1;
    col = columnNumber + 1;
    row = posNumber;
}


TokenType Token::getType() const {
    return type;
}

const string &Token::getValue() const {
    return value;
}

int Token::getLine() const {
    return pos;
}

int Token::getColumn() const {
    return col;
}

int Token::start() const {
    return row;
}

int Token::end() const {
    return row + value.size();
}

Token::Token(TokenType type, string value, int pos, int col, int row) :
        type(type), value(value), pos(pos), col(col + 1), row(row + 1) {}

Token::Token(TokenType type, const string &value, int pos, int col, int row, int tableValue) : type(type), value(value),
                                                                                               pos(pos), col(col + 1),
                                                                                               row(row + 1),
                                                                                               tableValue(tableValue) {}
