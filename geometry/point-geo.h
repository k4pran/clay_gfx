//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_POINT_GEO_H
#define OPENGL_TUTORIAL_POINT_GEO_H

#include "vector.h"

struct Vector2D;
struct Point2D {
    float x, y;

    void translate(const Vector2D& translationVec);

    Point2D translateCopy(const Vector2D& translationVec) const;

    bool equals(const Point2D& otherPoint) const;

    static float pointDistance(const Point2D& a, const Point2D& b);
};

#endif