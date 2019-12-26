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
    int pos, col, row;

    string source;
    string normalized_source;

    vector<regex> tokens_expressions;
    set<string> keywords;

    vector<class Token> tokens;
    vector<vector<string>> tables;

    bool correct;
    Token incorrect;

    void make_regex();

    string input_prefix = "/home/alexey/TFL/Lab6/lexer_output/";

    void write_table(int code, string path);
    void write_tables(string path);
    void write_tokens(string path);
    void write_tokens_ordered(string path);

public:

    Lexer(string source);

    void normalize();
    void lexical_analyse();
    void full_lexical_analyse();

    vector<Token> getTokens();
};


#endif //LAB5_LEXER_H
