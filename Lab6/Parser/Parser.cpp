//
// Created by alexey on 23.12.2019.
//

#include "Parser.h"

Parser::Parser(vector<Token> tokens): tokens(tokens) {

}

bool Parser::statement_list() {
    return false;
}

bool Parser::statement_list_tail() {
    return false;
}

bool Parser::statement() {
    return false;
}

bool Parser::literal() {
    return false;
}

bool Parser::primary_expression() {
    return false;
}

bool Parser::object_accessor() {
    return false;
}

bool Parser::expression() {
    return false;
}

bool Parser::postfix_expression() {
    return false;
}

bool Parser::prefix_expression() {
    return false;
}

bool Parser::unary_expression() {
    return false;
}

bool Parser::unary_operation() {
    return false;
}

bool Parser::binary_expression() {
    return false;
}

bool Parser::binary_operation() {
    return false;
}

bool Parser::assignment_expression() {
    return false;
}

bool Parser::assignment_operation() {
    return false;
}

bool Parser::ternary_expression() {
    return false;
}

bool Parser::object_literal() {
    return false;
}

bool Parser::object_kv_list() {
    return false;
}

bool Parser::object_kv_list_tail() {
    return false;
}

bool Parser::object_kv_pair() {
    return false;
}

bool Parser::array_literal() {
    return false;
}

bool Parser::array_element_list() {
    return false;
}

bool Parser::array_element_list_tail() {
    return false;
}

bool Parser::expression_statement() {
    return false;
}

bool Parser::assignment_statement() {
    return false;
}

bool Parser::funtion_declaration() {
    return false;
}

bool Parser::argument_list() {
    return false;
}

bool Parser::argument_list_tail() {
    return false;
}

bool Parser::argument() {
    return false;
}

bool Parser::function_body() {
    return false;
}

bool Parser::function_body_statement_list() {
    return false;
}

bool Parser::function_body_statement_list_tail() {
    return false;
}

bool Parser::function_body_statement() {
    return false;
};


bool Parser::while_statement(){
};

bool Parser::for_statement(){
};

bool Parser::loop_body(){
};

bool Parser::loop_body_statement_list(){
};

bool Parser::loop_body_statement_list_tail(){
};

bool Parser::loop_body_statement(){
};

bool Parser::if_else_statement(){
};

bool Parser::if_statement(){
};

bool Parser::else_statement_list(){
};

bool Parser::if_body(){
};

bool Parser::if_body_statement_list(){
}
