//
// Created by Ryan McCauley on 19/05/2020.
//

#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "point.h"

Point2D lineMid(const Point2D& a, const Point2D& b) {
    return {
        (a.x + b.x) / 2,
        (a.y + b.y) / 2
    };
}

float pointDistance(const Point2D& a, const Point2D& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

bool Point2D::equals(const Point2D& otherPoint) const {
    return this->x == otherPoint.x && this->y == otherPoint.y;
}

#endif
