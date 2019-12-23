#include <iostream>
#include "Lexer/Lexer.h"

string read_file(const string &path) {
    ifstream source_stream(path);
    ostringstream string_stream;

    string_stream << source_stream.rdbuf();
    source_stream.close();

    return string_stream.str();
}

int main() {

    string input_file = "/home/alexey/TFL/Lab6/test.js";
    string source = read_file(input_file);
    //cout << source << endl;

    Lexer lex(source);
    return 0;
}
