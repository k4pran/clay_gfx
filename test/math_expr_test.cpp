//
// Created by Ryan McCauley on 13/10/2020.
//

#include "catch.hh"
#include "../parser/math_parser.h"

TEST_CASE("Negative step when min < max should fail") {
    MathExpr<double> mathExpr = {"x + 1"};
    REQUIRE_THROWS(mathExpr.valuesFromStep(Range{0, 10}, -1));
}

TEST_CASE("Positive step when min > max should fail") {
    MathExpr<double> mathExpr = {"x + 1"};
    REQUIRE_THROWS(mathExpr.valuesFromStep(Range{10, 0}, 1));
}

TEST_CASE("Step 0 should fail when min is less than max or vice versa") {
    MathExpr<double> mathExpr = {"x + 1"};
    REQUIRE_THROWS(mathExpr.valuesFromStep(Range{10, 0}, 0));
    REQUIRE_THROWS(mathExpr.valuesFromStep(Range{0, 10}, 0));
}

TEST_CASE("Test constant increasing step generation") {
    MathExpr<double> mathExpr = {"x + 1"};
    mathExpr.valuesFromStep(Range{0, 10}, 1);
    REQUIRE(mathExpr.values.size() == 10);
    for(int i = 0; i < 10; i++) {
        REQUIRE(mathExpr.values[i] == i);
    }
}

TEST_CASE("Test constant decreasing step generation") {
    MathExpr<double> mathExpr = {"x + 1"};
    mathExpr.valuesFromStep(Range{0, -10}, -2);
    REQUIRE(mathExpr.values.size() == 5);
    REQUIRE(mathExpr.values[0] == 0);
    REQUIRE(mathExpr.values[1] == -2);
    REQUIRE(mathExpr.values[2] == -4);
    REQUIRE(mathExpr.values[3] == -6);
    REQUIRE(mathExpr.values[4] == -8);
}