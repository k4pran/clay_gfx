//
// Created by Ryan McCauley on 27/05/2020.
//

#include <iostream>
#include "point.h"
#include "line.h"
#include "float_approximator.h"

float EPSILON = 0.000001;

float Line::findSlope() const { // todo handle undefined slope
    float rise = this->pointB.y - this->pointA.y;
    float run = this->pointB.x - this->pointA.x;
    if (run == 0) {
        return std::numeric_limits<float>::infinity();
    }
    return rise / run;
}

float Line::findYIntercept() const { // todo handle undefined slope and when x is 0
    float slope = this->findSlope();
    if (slope == std::numeric_limits<float>::infinity()) {
        return 0; // todo handle better - may not be 0
    }
    return this->pointA.y - (slope * this->pointA.x);
}

std::vector<Point2D> Line::splitIntoFive() const {
    Point2D midPoint = lineMid(this->pointA, this->pointB);
    Point2D lowerPoint = lineMid(this->pointA, midPoint);
    Point2D upperPoint = lineMid(midPoint, this->pointB);
    return {this->pointA, lowerPoint, midPoint, upperPoint, this->pointB};
}

std::vector<Point2D> Line::splitIntoThree() const {
    Point2D midPoint = lineMid(this->pointA, this->pointB);
    return {this->pointA, midPoint, pointB};
}

Intercept findIntersection(const Line& lineA, const Line& lineB) { // todo handle parallel lines
    float slopeA = lineA.findSlope();
    float slopeB = lineB.findSlope();

    if (slopeA == 0 && slopeB == 0) {
        // todo handle
    }

    float yInterceptA = lineA.findYIntercept();
    float yInterceptB = lineB.findYIntercept();

    // check if collinear
    if (approximatelyEqual(slopeA, slopeB, EPSILON) && approximatelyEqual(yInterceptA, yInterceptB, EPSILON)) {
        return {InterceptResult::COLLINEAR, std::numeric_limits<float>::quiet_NaN()};
    }

    if (slopeA == std::numeric_limits<float>::infinity()) {
        float y = slopeB * lineA.pointA.x + yInterceptB; // todo move to own function
        return {InterceptResult::SINGLE, Point2D{lineA.pointA.x, y}};
    }
    else if (slopeB == std::numeric_limits<float>::infinity()) {
        float y = slopeA * lineB.pointA.x + yInterceptA;
        return {InterceptResult::SINGLE, Point2D{lineB.pointA.x, y}};
    }

    if (slopeB - slopeA == 0) {
        return {InterceptResult::NO_INTERCEPT, std::numeric_limits<float>::quiet_NaN()};
    }

    float xIntersection = (yInterceptB - yInterceptA) / (slopeA - slopeB);
    float yIntersection = slopeA * xIntersection + yInterceptA;

    return {InterceptResult::SINGLE, {xIntersection, yIntersection}};
}