//
// Created by alexey on 23.12.2019.
//

#include "Parser.h"

Parser::Parser(vector<Token> tokens) : tokens(tokens) {}

void Parser::parse() {
    correct = start_parse();

    cout << (correct ? "CORRECT" : "NOT CORRECT") << endl;
    if (!correct)
        cout << "Syntax error on line " << current_token().get_line();
}

bool Parser::start_parse() {
    pointer = 0;
    return statement_list();
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


bool Parser::check_binary_op() {
    return check_type(OP_BINARY) || check_type(OP_ADDITIVE);
}

bool Parser::check_assignment_op() {
    return check_type(OP_ASSIGN) || check_type(OP_EQUAL);
}

bool Parser::check_doubled_op() {
    return check_type(OP_DOUBLED);
}

bool Parser::check_unary_op() {
    return check_type(OP_ADDITIVE) || check_type(OP_EXCLAMATION);
}

// PARSER


bool Parser::statement_list() {
    if (is_empty())
        return true;
    return statement() && statement_list_tail();
}

bool Parser::statement_list_tail() {
    if (is_empty())
        return true;
    return statement() && statement_list_tail();
}

bool Parser::statement() {

    bool expressions = expression_statement() ||
                       assignment_statement() ||
                       while_statement() ||
                       if_else_statement() ||
                       for_statement() ||
                       function_declaration();
    if (expressions)
        return expressions;

    if (check_type(SEMICOLON)) {
        next_token();
        return true;
    }

    int prev_pointer = pointer;
    bool check_block = check_type_move(LEFT_CURLY) && statement_list() && check_type_move(RIGHT_CURLY);
    if (!check_block)
        pointer = prev_pointer;
    return check_block;
}

bool Parser::expression_statement() {
    int prev_pointer = pointer;
    bool check_expression = expression() && check_type_move(SEMICOLON);
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
    bool check_expression = check_type_move(LEFT_ROUND) && expression() && check_type_move(RIGHT_ROUND);
    if (!check_expression)
        pointer = prev_pointer;

    return check_expression;
}

bool Parser::object_accessor() {
    //return check_type(IDENTIFIER) && object_accessor_tail();
    int prev_pointer = pointer;
    bool check_ident = check_type_move(IDENTIFIER) && object_accessor_tail();
    if (!check_ident)
        pointer = prev_pointer;
    return check_ident;
}

bool Parser::object_accessor_tail() {
    int prev_pointer = pointer;
    if (check_type(LEFT_SQUARE)) {
        next_token();
        bool accessor_expression = expression() && check_type_move(RIGHT_SQUARE) && object_accessor_tail();
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    } else if (check_type(POINT)) {
        next_token();
        bool accessor_expression = object_accessor();
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    } else if (check_type(LEFT_ROUND)) {
        next_token();
        bool accessor_expression = method_argument_list() && check_type_move(RIGHT_ROUND) && object_accessor_tail();
        if (!accessor_expression)
            pointer = prev_pointer;
        return accessor_expression;
    }
    return true;
}

bool Parser::method_argument_list() {
    if (check_type(RIGHT_ROUND)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_arguments = expression() && method_argument_list_tail();
    if (!check_arguments)
        pointer = prev_pointer;

    return check_arguments;
}

bool Parser::method_argument_list_tail() {
    if (check_type(RIGHT_ROUND)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_array = check_type_move(COMMA) && expression() && method_argument_list_tail();
    if (!check_array)
        pointer = prev_pointer;

    return check_array;
}

bool Parser::expression() {
    bool check_expr = postfix_expression() ||
                      prefix_expression() ||
                      unary_expression() ||
                      binary_expression() ||
                      assignment_expression() ||
                      ternary_expression() ||
                      object_literal() ||
                      array_literal() ||
                      primary_expression();
    return check_expr;
}

bool Parser::postfix_expression() {
    int prev_pointer = pointer;
    bool check_expr = object_accessor() && doubled_operator();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::prefix_expression() {
    int prev_pointer = pointer;
    bool check_expr = doubled_operator() && object_accessor();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::doubled_operator() {
    if (check_doubled_op()) {
        next_token();
        return true;
    }
    return false;
}

bool Parser::unary_expression() {
    int prev_pointer = pointer;
    bool check_expr = unary_operator() && object_accessor();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::unary_operator() {
    if (check_unary_op()) {
        next_token();
        return true;
    }
    return false;
}

bool Parser::binary_expression() {
    int prev_pointer = pointer;
    bool check_expr = primary_expression() && binary_operation() && expression();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::binary_operation() {
    if (check_binary_op()) {
        next_token();
        return true;
    }
    return false;
}

bool Parser::assignment_expression() {
    int prev_pointer = pointer;
    bool check_expr = object_accessor() && assignment_operation() && expression();
    if (check_expr)
        return true;

    pointer = prev_pointer;
    check_expr = object_accessor() && check_type_move(OP_EQUAL) && function_assignment();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::assignment_operation() {
    if (check_assignment_op()) {
        next_token();
        return true;
    }
    return false;
}

bool Parser::ternary_expression() {
    int prev_pointer = pointer;
    bool check_expr = primary_expression() && check_type_move(QUESTION) &&
                      primary_expression() && check_type_move(COLON) &&
                      primary_expression();
    if (!check_expr)
        pointer = prev_pointer;

    return check_expr;
}

bool Parser::object_literal() {
    int prev_pointer = pointer;
    if (check_type(LEFT_CURLY)) {
        next_token();
    } else {
        return false;
    }
    bool check_object = object_kv_list();
    if (!check_object)
        pointer = prev_pointer;

    return check_object;
}

bool Parser::object_kv_list() {
    if (check_type(RIGHT_CURLY)) {
        next_token();
        return true;
    }

    int prev_pointer = pointer;
    bool check_object = object_kv_pair() && object_kv_list_tail();
    if (!check_object)
        pointer = prev_pointer;

    return check_object;
}

bool Parser::object_kv_list_tail() {
    if (check_type(RIGHT_CURLY)) {
        next_token();
        return true;
    }

    int prev_pointer = pointer;
    bool check_object = check_type_move(COMMA) && object_kv_pair() && object_kv_list_tail();
    if (!check_object)
        pointer = prev_pointer;

    return check_object;
}

bool Parser::object_kv_pair() {
    int prev_pointer = pointer;
    if (check_type(STRING) || check_type(IDENTIFIER)) {
        next_token();
    }
    bool check_object = check_type_move(COLON) && expression();
    if (!check_object)
        pointer = prev_pointer;

    return check_object;
}

bool Parser::array_literal() {
    int prev_pointer = pointer;
    if (check_type(LEFT_SQUARE)) {
        next_token();
    } else {
        return false;
    }
    bool check_array = array_element_list();
    if (!check_array)
        pointer = prev_pointer;

    return check_array;
}

bool Parser::array_element_list() {
    if (check_type(RIGHT_SQUARE)) {
        next_token();
        return true;
    }

    int prev_pointer = pointer;
    bool check_array = expression() && array_element_list_tail();
    if (!check_array)
        pointer = prev_pointer;

    return check_array;
}

bool Parser::array_element_list_tail() {
    if (check_type(RIGHT_SQUARE)) {
        next_token();
        return true;
    }

    int prev_pointer = pointer;
    bool check_array = check_type_move(COMMA) && expression() && array_element_list_tail();
    if (!check_array)
        pointer = prev_pointer;

    return check_array;
}

bool Parser::assignment_statement() {
    int prev_pointer = pointer;
    if (check_type(VAR) || check_type(LET) || check_type(CONST)) {
        next_token();
    } else {
        return expression_statement();
    }

    bool check_statement = assignment_expression() && check_type_move(SEMICOLON);
    if (!check_statement)
        pointer = prev_pointer;
    else
        return check_statement;

    if (!check_type(CONST))
        next_token();
    check_statement = check_type_move(IDENTIFIER) && check_type_move(SEMICOLON);
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}


bool Parser::function_declaration() {
    int prev_pointer = pointer;

    bool check_statement = check_type_move(FUNCTION) && check_type_move(IDENTIFIER) &&
                           check_type_move(LEFT_ROUND) && argument_list() && check_type_move(RIGHT_ROUND) &&
                           function_body();
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::function_assignment() {
    int prev_pointer = pointer;

    bool check_statement = check_type_move(FUNCTION) &&
                           check_type_move(LEFT_ROUND) && argument_list() && check_type_move(RIGHT_ROUND) &&
                           function_body();
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::argument_list() {
    if (check_type(RIGHT_ROUND)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_arguments = argument() && argument_list_tail();
    if (!check_arguments)
        pointer = prev_pointer;

    return check_arguments;
}

bool Parser::argument_list_tail() {
    if (check_type(RIGHT_ROUND)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_array = check_type_move(COMMA) && argument() && argument_list_tail();
    if (!check_array)
        pointer = prev_pointer;

    return check_array;
}

bool Parser::argument() {
    int prev_pointer = pointer;
    bool check_argument = check_type_move(IDENTIFIER) && argument_tail();
    if (!check_argument)
        pointer = prev_pointer;

    return check_argument;
}

bool Parser::argument_tail() {
    if (check_type(RIGHT_ROUND) || check_type(COMMA))
        return true;
    int prev_pointer = pointer;
    bool check_argument = check_type_move(OP_EQUAL) && expression();
    if (!check_argument)
        pointer = prev_pointer;

    return check_argument;
}

bool Parser::function_body() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(LEFT_CURLY))
        check_statement = check_type_move(LEFT_CURLY) && function_body_statement_list() && check_type_move(RIGHT_CURLY);
    else
        check_statement = function_body_statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::function_body_statement_list() {
    if (check_type(RIGHT_CURLY)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_statement = function_body_statement() && function_body_statement_list();
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::function_body_statement() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(RETURN))
        check_statement = check_type_move(RETURN) && expression() && check_type_move(SEMICOLON);
    else
        check_statement = statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}


bool Parser::while_statement() {
    int prev_pointer = pointer;

    bool check_statement = check_type_move(WHILE) &&
                           check_type_move(LEFT_ROUND) && expression() && check_type_move(RIGHT_ROUND) &&
                           loop_body();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::for_statement() {
    int prev_pointer = pointer;

    bool check_statement = check_type_move(FOR) &&
                           check_type_move(LEFT_ROUND) &&
                           assignment_statement() &&
                           expression() && check_type_move(SEMICOLON) &&
                           expression() &&
                           check_type_move(RIGHT_ROUND) &&
                           loop_body();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::loop_body() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(LEFT_CURLY))
        check_statement = check_type_move(LEFT_CURLY) && loop_body_statement_list() && check_type_move(RIGHT_CURLY);
    else
        check_statement = loop_body_statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::loop_body_statement_list() {
    if (check_type(RIGHT_CURLY)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_statement = loop_body_statement() && loop_body_statement_list();
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::loop_body_statement() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(BREAK))
        check_statement = check_type_move(BREAK) && check_type_move(SEMICOLON);
    else if (check_type(CONTINUE))
        check_statement = check_type_move(CONTINUE) && check_type_move(SEMICOLON);
    else
        check_statement = statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::if_else_statement() {
    int prev_pointer = pointer;

    bool check_statement = if_statement() && else_statement_list();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::if_statement() {
    int prev_pointer = pointer;

    bool check_statement = check_type_move(IF) &&
                           check_type_move(LEFT_ROUND) && expression() && check_type_move(RIGHT_ROUND) &&
                           if_body();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::else_statement_list() {
    if (!check_type(ELSE)) {
        return true;
    }
    int prev_pointer = pointer;

    bool check_statement = check_type_move(ELSE) &&
                           if_statement() && else_statement_list();

    if (!check_statement)
        pointer = prev_pointer;
    else
        return check_statement;

    pointer = prev_pointer;
    check_statement = check_type_move(ELSE) && if_body();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::if_body() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(LEFT_CURLY))
        check_statement = check_type_move(LEFT_CURLY) && if_body_statement_list() && check_type_move(RIGHT_CURLY);
    else
        check_statement = if_body_statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::if_body_statement_list() {
    if (check_type(RIGHT_CURLY)) {
        return true;
    }

    int prev_pointer = pointer;
    bool check_statement = if_body_statement() && if_body_statement_list();
    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}

bool Parser::if_body_statement() {
    int prev_pointer = pointer;

    bool check_statement;
    if (check_type(BREAK))
        check_statement = check_type_move(BREAK) && check_type_move(SEMICOLON);
    else if (check_type(CONTINUE))
        check_statement = check_type_move(CONTINUE) && check_type_move(SEMICOLON);
    else if (check_type(RETURN))
        check_statement = check_type_move(RETURN) && expression() && check_type_move(SEMICOLON);
    else
        check_statement = statement();

    if (!check_statement)
        pointer = prev_pointer;

    return check_statement;
}
