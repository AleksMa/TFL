//
// Created by alexey on 21.12.2019.
//

#include "Lexer.h"

// INIT FUNCTIONS

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
            regex(R"(^((/\*(.|\n)*?\*/)|(//[^\n]*)))"),                     // comments
            regex(R"(^\n)"),                                                   // newline
            regex(R"(^(("([^"\\]|\\.)*")|('([^'\\]|\\.)*')))"),             // string literal
            regex(R"(^null)"),                                                 // null
            regex(R"(^(true|false))"),                                         // bool literal
            regex(R"(^((0[xb][a-fA-F0-9]+)|([0-9]+((\\.[0-9]+)([eE][+\\-]?[0-9]+)?)?)))"), // numeric literal
            regex(R"(^(/.*/[gimsuy]*))"),                                      // regex literal
            regex(R"(^([a-zA-Z$][\w]*))"),                                    // identifier
            // punctuator
            regex(R"(^((===)|(!==)|(<=)|(>=)|(==)|(!=)|(\+{2})|(--)|(<<)|(>>)|(&&)|([|]{2})|(\+=)|(-=)|(\*=)|(%=)|(/=)|([|]=)|(\^=)|[.;,<>+\-*/%&|^!~?:={}()\[\]]))")
    };
}

// main constructor

Lexer::Lexer(string source) : source(source) {
    correct = true;
    tables = vector<vector<string>>(11);
    make_regex();
    make_keywords();
}

void Lexer::full_lexical_analyse() {
    lexical_analyse();

    write_tables(input_prefix + "tables/");
    write_tokens(input_prefix + "TOKENS.txt");
    write_tokens_ordered(input_prefix + "TOKENS_ORDERED.txt");
}


// Normalization

void Lexer::normalize() {
    regex space_regex("([ \t]+)|((/\\*(.|\\n)*?\\*/)|(//[^\\n]*))");
    smatch space_match;
    normalized_source = regex_replace(source, space_regex, " ");
}

// Lexical analysis

void Lexer::lexical_analyse() {
    regex cur_space_regex("^([ \t]+)");
    pos = 0, col = 0, row = 0;

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
                int code = i;
                string matched_substr = match[0];
                if (code == IDENTIFIER && keywords.find(matched_substr) != keywords.end()) {
                    code = KEYWORD;
                }
                if (code == NULL_LITERAL) {
                    tokens.emplace_back(static_cast<token_type>(code), matched_substr, pos, col, row);
                } else if (code!= NEWLINE && code!= COMMENT) {
                    tokens.emplace_back(static_cast<token_type>(code), matched_substr, pos, col, row, tables[i].size());
                    tables[i].push_back(matched_substr);
                }
                pos += matched_substr.length();
                if (code== NEWLINE) {
                    col = 0;
                    row++;
                } else if (code== COMMENT && matched_substr[1] == '*') {
                    int count_from_space = 0, height = 0;
                    for (char c : matched_substr) {
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
                    col += matched_substr.length();
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
}



// OUTPUT FUNCTIONS


void Lexer::write_tables(string path) {
    for (int i = 0; i <= UNKNOWN; i++) {
        if (i == NEWLINE || i == NULL_LITERAL || i == COMMENT)
            continue;
        write_table(i, path);
    }
}

void Lexer::write_table(int code, string path) {
    string header = Token::token_types[static_cast<token_type>(code)];
    string filename = header;
    transform(filename.begin(), filename.end(), filename.begin(),
              [](unsigned char c) { return std::tolower(c); });
    ofstream output_stream(path + filename + ".csv");
    output_stream << header << endl << endl;
    for (int i = 0; i < tables[code].size(); i++) {
        output_stream << i << ", " << tables[code][i] << endl;
    }
    output_stream.close();
}

void Lexer::write_tokens(string path) {
    ofstream output_stream(path);
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
}

void Lexer::write_tokens_ordered(string path) {
    ofstream output_stream(path);
    int k = 1;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].get_type() == COMMENT || tokens[i].get_type() == NEWLINE)
            continue;
        if (tokens[i].get_line() != k) {
            output_stream << endl;
            i--;
            k++;
        }
        else
            output_stream << tokens[i].to_str() << " ";
    }
    output_stream.close();
}

vector<Token> Lexer::getTokens() {
    return tokens;
}
