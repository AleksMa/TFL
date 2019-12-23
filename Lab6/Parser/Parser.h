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
    void StatementList();
    void StatementListTail();
    void Statement();
    void Literal();
    void PrimaryExpression();
    void ObjectAccessor();
    void Expression();
    void PostfixExpression();
    void PrefixExpression();
    void UnaryExpression();
    void UnaryOperation();
    void BinaryExpression();
    void BinaryOperation();
    void AssignmentExpression();
    void AssignmentOperation();
    void TernaryExpression();
    void ObjectLiteral();
    void ObjectKVList();
    void ObjectKVListTail();
    void ObjectKVPair();
    void ArrayLiteral();
    void ArrayElementList();
    void ArrayElementListTail();
    void ExpressionStatement();
    void AssignmentStatement();
    void FuntionDeclaration();
    void ArgumentList();
    void ArgumentListTail();
    void Argument();
    void FunctionBody();
    void FunctionBodyStatementList();
    void FunctionBodyStatementListTail();
    void FunctionBodyStatement();
    void while_statement();
    void for_statement();
    void loop_body();
    void loop_body_statement_list();
    void loop_body_statement_list_tail();
    void loop_body_statement();
    void if_else_statement();
    void if_statement();
    void else_statement_list();
    void if_body();
    void if_body_statement_list();





};


#endif //LAB6_PARSER_H
