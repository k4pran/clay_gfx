//
// Created by Ryan McCauley on 19/05/2020.
//

#ifndef POINT_H
#define POINT_H

#include <cmath>
#include "point-geo.h"

float Point2D::pointDistance(const Point2D &a, const Point2D &b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

bool Point2D::equals(const Point2D& otherPoint) const {
    return this->x == otherPoint.x && this->y == otherPoint.y;
}

void Point2D::translate(const Vector2D& translationVec) {
    this->x += translationVec.x;
    this->y += translationVec.y;
}

Point2D Point2D::translateCopy(const Vector2D &translationVec) const {
    return {this->x + translationVec.x, this->y + translationVec.y};
}

#endif
