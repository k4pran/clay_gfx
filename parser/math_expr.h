//
// Created by Ryan McCauley on 25/09/2020.
//

#ifndef OPENGL_TUTORIAL_MATH_EXPR_H
#define OPENGL_TUTORIAL_MATH_EXPR_H

#include <string>
#include <vector>
#include <map>
#include "../drawable/attribute/range.h"

template <typename T>
struct MathExpr {
    std::string expr;
    std::vector<T> values;

    void valuesFromStep(Range range, T step);
};

template<typename T>
void MathExpr<T>::valuesFromStep(Range range, T step) {
    if (step == 0) {
        throw "Step cannot be 0";
    }
    if (range.start < range.end && step < 0) {
        throw "Step must be positive when range min is less than max";
    }
    if (range.start > range.end && step > 0) {
        throw "Step must be negative when range min is greater than max";
    }

    if (range.start > range.end) {
        for (int i = range.start; i > range.end; i += step) {
            values.push_back(i);
        }
    }
    else {
        for (int i = range.start; i < range.end; i += step) {
            values.push_back(i);
        }
    }
}

#endif //OPENGL_TUTORIAL_MATH_EXPR_H
