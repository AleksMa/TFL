//
// Created by alexey on 23.12.2019.
//

#ifndef LAB6_PARSER_H
#define LAB6_PARSER_H

#include "../Lexer/Lexer.h"


class Parser {
private:
    int pointer;
    bool correct;

    vector<Token> tokens;

public:

    Parser(vector<Token> tokens);

    bool statement_list();
    bool statement_list_tail();
    bool statement();
    bool literal();
    bool primary_expression();
    bool object_accessor();
    bool expression();
    bool postfix_expression();
    bool prefix_expression();
    bool unary_expression();
    bool unary_operation();
    bool binary_expression();
    bool binary_operation();
    bool assignment_expression();
    bool assignment_operation();
    bool ternary_expression();
    bool object_literal();
    bool object_kv_list();
    bool object_kv_list_tail();
    bool object_kv_pair();
    bool array_literal();
    bool array_element_list();
    bool array_element_list_tail();
    bool expression_statement();
    bool assignment_statement();
    bool funtion_declaration();
    bool argument_list();
    bool argument_list_tail();
    bool argument();
    bool function_body();
    bool function_body_statement_list();
    bool function_body_statement_list_tail();
    bool function_body_statement();
    bool while_statement();
    bool for_statement();
    bool loop_body();
    bool loop_body_statement_list();
    bool loop_body_statement_list_tail();
    bool loop_body_statement();
    bool if_else_statement();
    bool if_statement();
    bool else_statement_list();
    bool if_body();
    bool if_body_statement_list();
    bool if_body_statement_list_tail();
    bool if_body_statement();


};


#endif //LAB6_PARSER_H
