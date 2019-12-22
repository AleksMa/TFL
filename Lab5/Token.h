//
// Created by alexey on 22.12.2019.
//

#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H

#include "bits/stdc++.h"
#include "Lexer.h"

using namespace std;

enum TokenType {
    COMMENT, // 0
    NEWLINE, // 1
    STRING_LITERAL, // 2
    NULL_LITERAL, // 3
    BOOLEAN_LITERAL, // 4
    NUMERIC_LITERAL, // 5
    REGEXP_LITERAL, // 6
    IDENTIFIER, // 7
    PUNCTUATOR, // 8
    KEYWORD, // 9
    UNKNOWN // 10
};

class Token {
private:
    TokenType type;
    string value;
    int raw;
    int col;
    int pos;
public:
    TokenType getType() const;

    const string &getValue() const;

    int getLine() const;

    int getColumn() const;

    int start() const;

    int end() const;

    string toString() const;

    void setPosition(int lineNumber, int columnNumber, int pos);

    Token();

    Token(TokenType type, const string &value);
};


#endif //LAB5_TOKEN_H
