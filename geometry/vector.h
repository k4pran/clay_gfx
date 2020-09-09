//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_VECTOR_H
#define OPENGL_TUTORIAL_VECTOR_H

#include "point-geo.h"

struct Point2D;
struct Vector2D {
    float x, y;

    void normalize();

    void scale(float scalar);

    void reverse();

    void rotate(float rotationDeg);

    float magnitude() const;

    Vector2D scaleCopy(float scalar) const;

    Vector2D reverseCopy() const;
};

Vector2D calcNormalizedVector2D(const Vector2D& vector);

Vector2D points2DtoVector2D(const Point2D& pointA, const Point2D& pointB);

Vector2D getRotatedVector(const Vector2D& vector2D, float rotationDeg);

float magnitude(const Vector2D& vector2D);

#endif //OPENGL_TUTORIAL_VECTOR_H
