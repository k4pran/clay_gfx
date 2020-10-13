//
// Created by Ryan McCauley on 25/09/2020.
//

#ifndef OPENGL_TUTORIAL_MATH_PARSER_H
#define OPENGL_TUTORIAL_MATH_PARSER_H

#include <exprtk.hpp>
#include "math_expr.h"

template<typename T>
std::vector<T> parseSingleVar(MathExpr<T> mathExpr) {
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T> expression_t;
    typedef exprtk::parser<T> parser_t;

    const std::string expression_string =
            mathExpr.expr;

    T x;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_string, expression);

    std::vector<T> result;
    for (auto i : mathExpr.values) {
        x = i;
        result.push_back(expression.value());
    }
    return result;
}

#endif //OPENGL_TUTORIAL_MATH_PARSER_H
