//
// Created by alexey on 22.12.2019.
//

#include "Token.h"

map<TokenType, string> Token::tokenTypes = {
        {COMMENT,        "COMMENT"},
        {NEWLINE,        "NEWLINE"},
        {STRING,         "STRING"},
        {NULL_LITERAL,   "NULL_LITERAL"},
        {BOOLEAN,        "BOOLEAN"},
        {NUMERIC,        "NUMERIC"},
        {REGEXP,         "REGEXP"},
        {IDENTIFICATION, "IDENTIFICATION"},
        {PUNCTUATION,    "PUNCTUATION"},
        {KEYWORD,        "KEYWORD"},
        {UNKNOWN,        "UNKNOWN"}
};

Token::Token(TokenType type, string value) : type(type), value(value) {}

Token::Token() {}

string Token::toString() const {
    //return "{token: " + value + ", type: " + tokenTypes[type] + ", position: " + to_string(row) + ":" + to_string(col) + "}";
    return "{" + tokenTypes[type] +
           (type != NEWLINE && type != NULL_LITERAL ? ", idx: " + to_string(tableValue) : "") +
           ", pos: " + to_string(row) + ":" + to_string(col) + "}";
}

void Token::setPosition(int lineNumber, int columnNumber, int posNumber) {
    pos = lineNumber + 1;
    col = columnNumber + 1;
    row = posNumber;
}


TokenType Token::getType() const {
    return type;
}

string Token::getValue() const {
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
