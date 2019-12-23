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
    vector<regex> tokensExpressions;
    string source;
    string normalizedSource;
    set<string> keywords;

    vector<vector<string>> tables;

    vector<string> commentsTable;
    vector<string> stringsTable;
    vector<string> boolTable;
    vector<string> numericTable;
    vector<string> regexTable;
    vector<string> identificatorTable;
    vector<string> keywordTable;
    vector<string> punctuationTable;

    void makeRegex();
    void makeKeywords();

public:

    Lexer(string source);
};


#endif //LAB5_LEXER_H
