//
// Created by alexey on 21.12.2019.
//

#include "Lexer.h"

void Lexer::makeKeywords() {
    keywords = {
            "break", "do", "instanceof",
            "typeof", "case", "else",
            "var", "catch", "finally",
            "void", "continue", "for",
            "switch", "while", "debugger",
            "function", "this", "with",
            "default", "if", "throw",
            "delete", "in", "try",
            "new", "return"
    };
}

void Lexer::makeRegex() {
    //tokensExpressions.push_back(regex("\"(/*.**/)|(//.*?\r?\n)\""));
    tokensExpressions.push_back(regex("^(/\\*.*?\\*/)|(//.*?\r?\n)"));
}

Lexer::Lexer(const string &source) : source(source) {
    TokenType t = COMMENT;
    cout << t << endl;
    makeRegex();
    makeKeywords();
    string str = "aa/* lol */a";
    cout << regex_search(str.begin()+1, str.end(), tokensExpressions[0]) << endl;
    cout << tokensExpressions.size() << endl;
}
