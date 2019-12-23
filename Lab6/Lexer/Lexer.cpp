//
// Created by alexey on 21.12.2019.
//

#include "Lexer.h"

void write_tables(const string header, const vector<string> &table) {
    string filename = header;
    transform(filename.begin(), filename.end(), filename.begin(),
              [](unsigned char c) { return std::tolower(c); });
    cout << filename << endl;
    ofstream output_stream("/home/alexey/TFL/Lab6/dest/" + filename + ".csv");
    output_stream << header << endl << endl;
    for (int i = 0; i < table.size(); i++) {
        output_stream << i << ", " << table[i] << endl;
    }
    output_stream.close();
}

void Lexer::write_tokens() {
    ofstream output_stream("/home/alexey/TFL/Lab6/dest/TOKENS.txt");
    if (!correct) {
        output_stream << "UNEXPECTED TOKEN {" << incorrect.get_value() << "} ON " << incorrect.get_column() << ":"
                      << incorrect.get_line();
        output_stream.close();
        return;
    }

    for (int i = 0; i < tokens.size(); i++) {
        output_stream << tokens[i].to_str_extended() << endl;

        if (tokens[i].get_type() == NEWLINE)
            output_stream << endl;
    }
    output_stream.close();


    ofstream output_stream_ordered("/home/alexey/TFL/Lab6/dest/TOKENS_ORDERED.txt");
    int k = 1;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].get_type() == COMMENT || tokens[i].get_type() == NEWLINE)
            continue;
        if (tokens[i].get_line() != k) {
            output_stream_ordered << endl;
            i--;
            k++;
        }
        else
            output_stream_ordered << tokens[i].to_str() << " ";
    }
    output_stream_ordered.close();

}


void Lexer::make_keywords() {
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

void Lexer::make_regex() {
    tokens_expressions = {
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
    correct = true;
    tables = vector<vector<string>>(11);
    make_regex();
    make_keywords();

    // Normalization
    regex space_regex("([ \t]+)|((/\\*(.|\\n)*?\\*/)|(//[^\\n]*))");
    regex cur_space_regex("^([ \t]+)");
    smatch space_match;
    normalized_source = regex_replace(source, space_regex, " ");

    cout << source << endl;

    int pos = 0, col = 0, row = 0;


    while (pos < source.size()) {
        string cur_source = source.substr(pos);
        smatch cur_space_match;

        if (regex_search(cur_source, cur_space_match, cur_space_regex)) {
            pos += cur_space_match[0].length();
            continue;
        }

        bool found = false;
        smatch match;

        for (int i = 0; i < tokens_expressions.size(); ++i) {
            if (regex_search(cur_source, match, tokens_expressions[i])) {
                if (i == IDENTIFICATION && keywords.find(match[0]) != keywords.end()) {
                    i = KEYWORD;
                }
                if (i != NEWLINE && i != NULL_LITERAL) {
                    tokens.emplace_back(static_cast<token_type>(i), match[0], pos, col, row, tables[i].size());
                    tables[i].push_back(match[0]);
                } else {
                    tokens.emplace_back(static_cast<token_type>(i), match[0], pos, col, row);
                }
                pos += match[0].length();
                if (i == NEWLINE) {
                    col = 0;
                    row++;
                } else if (i == COMMENT && match[0].str()[1] == '*') {
                    int count_from_space = 0, height = 0;
                    for (char c : match[0].str()) {
                        if (c == '\n') {
                            count_from_space = 0;
                            height++;
                        } else {
                            count_from_space++;
                        }
                    }
                    row += height;
                    col = count_from_space;
                } else {
                    col += match[0].length();
                }

                found = true;
                break;
            }
        }
        if (!found) {
            string res = cur_source.substr(0, 1);
            if (correct) {
                correct = false;
                incorrect = Token(UNKNOWN, res, pos, col, row, tables[UNKNOWN].size());
            }

            tokens.emplace_back(incorrect);
            tables[UNKNOWN].push_back(res);
            pos++;
            col++;
        }
    }

    for (const auto &token : tokens) {
        cout << token.to_str() << endl;
    }

    cout << endl << endl;

    for (int i = 0; i < 11; i++) {
        if (i == NEWLINE || i == NULL_LITERAL)
            continue;
        write_tables(Token::token_types[static_cast<token_type>(i)], tables[i]);
    }

    write_tokens();

}
