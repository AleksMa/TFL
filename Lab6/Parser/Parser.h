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

//    set<string> binary_ops = {"===", "!==", "<=", ">=", "==", "!=", "<<", ">>", "&&", "||", "<", ">", "+", "-", "*", "/", "%"};
//    set<string> assignment_ops = {"+=", "-=", "*=", "%=", "&=", "|=", "^=", "="};
//    set<string> doubled_ops = {"++", "--"};
//    set<string> unary_ops = {"+", "-", "!"};

    bool is_empty();
    Token current_token();
    bool next_token();
    bool check_value_move(string value);
    bool check_value(string value);

    bool check_type_move(token_type type);
    bool check_type(token_type type);

    bool check_binary_op();
    bool check_assignment_op();
    bool check_doubled_op();
    bool check_unary_op();

    bool start_parse();
    bool statement_list();
    bool statement_list_tail();
    bool statement();
    bool literal();
    bool primary_expression();
    bool object_accessor();
    bool object_accessor_tail();
    bool method_argument_list();
    bool method_argument_list_tail();
    bool expression();
    bool postfix_expression();
    bool prefix_expression();
    bool doubled_operator();
    bool unary_expression();
    bool unary_operator();
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
    bool function_declaration();
    bool function_assignment();
    bool argument_list();
    bool argument_list_tail();
    bool argument();
    bool argument_tail();
    bool function_body();
    bool function_body_statement_list();
    bool function_body_statement();
    bool while_statement();
    bool for_statement();
    bool loop_body();
    bool loop_body_statement_list();
    bool loop_body_statement();
    bool if_else_statement();
    bool if_statement();
    bool else_statement_list();
    bool if_body();
    bool if_body_statement_list();
    bool if_body_statement();

public:
    Parser(vector<Token> tokens);

    void parse();
};


#endif //LAB6_PARSER_H
