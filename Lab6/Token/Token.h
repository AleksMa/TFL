//
// Created by alexey on 22.12.2019.
//

#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H


#include "bits/stdc++.h"

using namespace std;

enum TokenType {
    COMMENT, // 0
    NEWLINE, // 1
    STRING, // 2
    NULL_LITERAL, // 3
    BOOLEAN, // 4
    NUMERIC, // 5
    REGEXP, // 6
    IDENTIFICATION, // 7
    PUNCTUATION, // 8
    KEYWORD, // 9
    UNKNOWN // 10
};

class Token {
private:
    TokenType type;
    string value;
    int pos;
    int col;
    int row;
    int tableValue;

public:
    TokenType getType() const;

    string getValue() const;

    int getLine() const;
    int getColumn() const;
    int start() const;
    int end() const;

    string toString() const;

    void setPosition(int lineNumber, int columnNumber, int pos);

    Token();

    Token(TokenType type, string value);

    Token(TokenType type, string value, int pos, int col, int row);

    Token(TokenType type, const string &value, int pos, int col, int row, int tableValue);

    static map<TokenType, string> tokenTypes;
};


#endif //LAB5_TOKEN_H
