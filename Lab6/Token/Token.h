//
// Created by alexey on 22.12.2019.
//

#ifndef LAB5_TOKEN_H
#define LAB5_TOKEN_H


#include "bits/stdc++.h"

using namespace std;

enum token_type {
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
    int start() const;
    int end() const;

    string to_str() const;
    string to_str_extended() const;

    void set_position(int lineNumber, int columnNumber, int pos);

    Token();

    Token(token_type type, string value);

    Token(token_type type, string value, int pos, int col, int row);

    Token(token_type type, const string &value, int pos, int col, int row, int table_value);

    static map<token_type, string> token_types;
};


#endif //LAB5_TOKEN_H
