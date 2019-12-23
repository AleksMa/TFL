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
    void AssgnmenrStatement();
    void FuntionDeclaration();
    void ArgumentList();
    void ArgumentListTail();

};


#endif //LAB6_PARSER_H
