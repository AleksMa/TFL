//
// Created by alexey on 23.12.2019.
//

#include "Parser.h"

Parser::Parser(vector<Token> tokens) : tokens(tokens) {
    correct = parse();
    cout << (correct ? "CORRECT" : "NOT CORRECT");
}


bool Parser::is_empty() {
    return pointer >= tokens.size();
}

Token Parser::current_token() {
    return tokens[pointer];
}


bool Parser::check_value_move(string value) {
    bool check = !is_empty() && current_token().equals(value);
    if (check)
        next_token();
    return check;
}

bool Parser::check_value(string value) {
    bool check = !is_empty() && current_token().equals(value);
    return check;
}

bool Parser::check_type_move(token_type type) {
    bool check = !is_empty() && current_token().equalsClass(type);
    if (check)
        next_token();
    return check;
}

bool Parser::check_type(token_type type) {
    bool check = !is_empty() && current_token().equalsClass(type);
    return check;
}

bool Parser::next_token() {
    pointer++;
    return !is_empty();
}

// PARSER

bool Parser::parse() {
    return statement_list();
}


bool Parser::statement_list() {
    if (is_empty())
        return true;
//    bool statement_parse = statement();
//    if (!statement_parse)
//        return false;
//    return statement_list_tail();
    return statement() && statement_list_tail();
}

bool Parser::statement_list_tail() {
    if (is_empty())
        return true;
//    bool statement_parse = statement();
//    if (!statement_parse)
//        return false;
//    return statement_list_tail();
    return statement() && statement_list_tail();
}

bool Parser::statement() {

    bool expressions = expression_statement() ||
                       assignment_statement() ||
                       while_statement() ||
                       if_else_statement() ||
                       for_statement() ||
                       funtion_declaration();
    if (expressions)
        return expressions;
    int prev_pointer = pointer;
    bool check_block = check_value_move("{") && statement_list() && check_value_move("}");
    if (!check_block)
        pointer = prev_pointer;
    return check_block;
}

bool Parser::expression_statement() {
    int prev_pointer = pointer;
    bool check_expression = expression() && check_value_move(";");
    if (!check_expression)
        pointer = prev_pointer;
    return check_expression;
}

bool Parser::literal() {
    bool check_literal = check_type(STRING) ||
                         check_type(NULL_LITERAL) ||
                         check_type(BOOLEAN) ||
                         check_type(NUMERIC) ||
                         check_type(REGEXP);
    if (check_literal)
        next_token();
    return check_literal;
}

bool Parser::primary_expression() {
    bool expressions = object_accessor() || literal();
    if (expressions)
        return expressions;

    int prev_pointer = pointer;
    bool check_expression = check_value_move("(") && statement_list() && check_value_move(")");
    if (!check_expression)
        pointer = prev_pointer;

    return check_expression;
}

bool Parser::object_accessor() {
    return check_type(IDENTIFIER) && object_accessor_tail();
}

bool Parser::object_accessor_tail() {
    int prev_pointer = pointer;
    next_token();
    if (check_value("[")) {
        next_token();
        bool accessor_expression = expression() && check_value_move("]");
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    } else if (check_value(".")) {
        next_token();
        bool accessor_expression = object_accessor() && object_complex_tail();
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    }
    return true;
}

bool Parser::object_complex_tail() {
    if (check_value("[")) {
        int prev_pointer = pointer;
        next_token();
        bool accessor_expression = expression() && check_value_move("]");
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    }
    return true;
}

bool Parser::expression() {
    return primary_expression() ||
           postfix_expression() ||
           prefix_expression() ||
           unary_expression() ||
           binary_expression() ||
           assignment_expression() ||
           ternary_expression() ||
           object_literal() ||
           array_literal();
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

bool Parser::if_body_statement_list_tail() {
    return false;
}

bool Parser::if_body_statement() {
    return false;
}


bool Parser::while_statement() {
    return false;
}

bool Parser::for_statement() {
    return false;
}

bool Parser::loop_body() {
    return false;
}

bool Parser::loop_body_statement_list() {
    return false;
}

bool Parser::loop_body_statement_list_tail() {
	return false;
}

bool Parser::loop_body_statement() {
    return false;
}

bool Parser::if_else_statement() {
    return false;
}

bool Parser::if_statement() {
    return false;
}

bool Parser::else_statement_list() {
    return false;
}

bool Parser::if_body() {
    return false;
}

bool Parser::if_body_statement_list() {
	return false;
}
