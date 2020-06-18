//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_LINE_H
#define OPENGL_TUTORIAL_LINE_H

#include <vector>
#include "point.h"

struct Line {
    Point2D pointA, pointB;

    float findSlope() const;

    float findYIntercept() const;

    std::vector<Point2D> splitIntoThree() const;

    std::vector<Point2D> splitIntoFive() const;
};

enum class InterceptResult {
    SINGLE,
    MULTIPLE,
    COLLINEAR,
    INFINITE,
    PARALLEL,
    NO_INTERCEPT
};

struct Intercept {
    InterceptResult interceptResult;
    Point2D intercept;
};

Intercept findIntersection(const Line& lineA, const Line& lineB);

#endif //OPENGL_TUTORIAL_LINE_H
