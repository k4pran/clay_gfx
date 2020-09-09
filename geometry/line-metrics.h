//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_LINE_METRICS_H
#define OPENGL_TUTORIAL_LINE_METRICS_H

#include <vector>
#include "point-geo.h"

struct LineMetrics {
    Point2D pointA, pointB;

    float findSlope() const;

    float findYIntercept() const;

    float findLength() const;

    Point2D findMid() const;

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

Intercept findIntersection(const LineMetrics& lineA, const LineMetrics& lineB);

Point2D lineMid(const Point2D& a, const Point2D& b);

#endif //OPENGL_TUTORIAL_LINE_METRICS_H
