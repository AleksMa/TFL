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
            "new", "return", "let", "const"
    };
}

void Lexer::makeRegex() {
    tokensExpressions = {
            regex(R"(^((/\*(.|\n)*?\*/)|(//[^\n]*)))"),   // comments
            regex("^\n"),                           // newline
            regex(R"(^(("([^"\\]|\\.)*")|('([^'\\]|\\.)*')))"),           // string literal
            regex("^null"),                         // null
            regex("^(true|false)"),                 // bool literal
            regex("^((0[xb][a-fA-F0-9]+)|([0-9]+((\\.[0-9]+)([eE][+\\-]?[0-9]+)?)?))"), // numeric literal
            regex("^(/.*/[gimsuy]*)"),           // regex literal
            regex("^([a-zA-Z_][\\w]*)"),              // IDENTIFICATION
            regex(R"(^((===)|(!==)|(<=)|(>=)|(==)|(!=)|(\+{2})|(--)|(<<)|(>>)|(&&)|([|]{2})|(\+=)|(-=)|(\*=)|(%=)|(&=)|([|]=)|(\^=)|[.;,<>+\-*/%&|^!~?:={}()\[\]]))")
    };
}

Lexer::Lexer(string source) : source(source) {
    tables = vector<vector<string>>(11);
    makeRegex();
    makeKeywords();

    // Normalization
    regex spaceRegex("[ \t]+");
    regex curSpaceRegex("^([ \t]+)");
    smatch spaceMatch;
    normalizedSource = regex_replace(source, spaceRegex, " ");

    cout << source << endl;

    for (char c : source) {
        cout << +c << endl;
    }

    char cc = '\n';
    cout << "\\n: " <<  +cc << endl;

    int pos = 0, col = 0, row = 0;


    while (pos < source.size()) {
        string curSource = source.substr(pos);
        smatch curSpaceMatch;

        if (regex_search(curSource, curSpaceMatch, curSpaceRegex)) {
            pos += curSpaceMatch[0].length();
            continue;
        }

        bool found = false;
        smatch match;

        for (int i = 0; i < tokensExpressions.size(); ++i) {
            if (regex_search(curSource, match, tokensExpressions[i])) {
                if (i == IDENTIFICATION && keywords.find(match[0]) != keywords.end()) {
                    i = KEYWORD;
                }
                if (i != NEWLINE && i != NULL_LITERAL) {
                    tokens.emplace_back(static_cast<TokenType>(i), match[0], pos, col, row, tables[i].size());
                    tables[i].push_back(match[0]);
                }
                tokens.emplace_back(static_cast<TokenType>(i), match[0], pos, col, row);
                pos += match[0].length();
                if (i == NEWLINE) {
                    col = 0;
                    row++;
                } else {
                    col += match[0].length();
                }

                found = true;
                break;
            }
        }
        if (!found) {
            string res = curSource.substr(0, 1);
            tokens.emplace_back(UNKNOWN, res, pos, col, row, tables[UNKNOWN].size());
            tables[UNKNOWN].push_back(res);
            pos++;
            col++;
        }
    }

    for (const auto& token : tokens) {
        cout << token.toString() << endl;
    }

    cout << endl << endl;

    for (int i = 0; i < 11; i++) {
        if (i == NEWLINE || i == NULL_LITERAL)
            continue;
        cout << Token::tokenTypes[static_cast<TokenType>(i)] << endl;
        for (int j = 0; j < tables[i].size(); j++) {
            cout << j << ": " << tables[i][j] << endl;
        }
        cout << endl;
    }

}
