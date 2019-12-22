//
// Created by alexey on 22.12.2019.
//

#include "Token.h"

Token::Token(TokenType type, const string &value) : type(type), value(value) {}

Token::Token() {}

string Token::toString() const {
    return "{token: " + value + ", type: " + to_string(type) + ", position: " + to_string(raw) + ":" + to_string(col) +
           "}";
}

void Token::setPosition(int lineNumber, int columnNumber, int posNumber) {
    raw = lineNumber + 1;
    col = columnNumber + 1;
    pos = posNumber;
}


TokenType Token::getType() const {
    return type;
}

const string &Token::getValue() const {
    return value;
}

int Token::getLine() const {
    return raw;
}

int Token::getColumn() const {
    return col;
}

int Token::start() const {
    return pos;
}

int Token::end() const {
    return pos + value.size();
}