#include <iostream>
#include "Lexer.h"

int main() {
    Lexer lex("aa");
    for (auto keyword : lex.keywords) {
        cout << keyword << endl;
    }
    return 0;
}
