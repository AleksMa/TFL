//
// Created by alexey on 21.12.2019.
//

#ifndef LAB5_LEXER_H
#define LAB5_LEXER_H


#include "bits/stdc++.h"
#include "../Token/Token.h"

using namespace std;


class Lexer {
private:
    vector<class Token> tokens;
    vector<regex> tokens_expressions;
    string source;
    string normalized_source;
    set<string> keywords;

    bool correct;
    Token incorrect;

    vector<vector<string>> tables;

    void make_regex();
    void make_keywords();

public:

    Lexer(string source);
    void write_tokens();
};


#endif //LAB5_LEXER_H
