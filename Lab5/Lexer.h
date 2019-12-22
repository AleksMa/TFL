//
// Created by alexey on 21.12.2019.
//

#ifndef LAB5_LEXER_H
#define LAB5_LEXER_H


#include "bits/stdc++.h"
#include "Token.h"

using namespace std;


class Lexer {
private:
    vector<class Token> tokens;
    vector<regex> tokensExpressions;
    string source;

    void makeRegex();
    void makeKeywords();

public:
    set<string> keywords;

    Lexer(const string &source);

};


#endif //LAB5_LEXER_H
