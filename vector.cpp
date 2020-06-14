//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "vector.h"
#include "point.h"

float magnitude(const Vector2D& vector2D) {
    return sqrt(pow(vector2D.x, 2) + pow(vector2D.y, 2));
}

void Vector2D::normalize() {
    float magnitude = ::magnitude(*this);
    this->x /= magnitude;
    this->y /= magnitude;
}

void Vector2D::scale(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vector2D::rotate(float rotationDeg) {
    float rotationRadians = M_PI/180.0 * rotationDeg;
    float initialX = this->x;
    float initialY = this->y;

    this->x = initialX * cos(rotationRadians) - initialY * sin(rotationRadians);
    this->y = initialX * sin(rotationRadians) + initialY * cos(rotationRadians);
}

float Vector2D::magnitude() const {
    return ::magnitude(*this);
}

Vector2D calcNormalizedVector2D(const Vector2D& vector) {
    float magnitude = ::magnitude(vector);
    return {vector.x / magnitude, vector.y / magnitude};
}

Vector2D points2DtoVector2D(const Point2D& pointA, const Point2D& pointB) {
    return {pointB.x - pointA.x, pointB.y - pointA.y};
}

Vector2D getRotatedVector(const Vector2D& vector2D, float rotationDeg) {
    float rotationRadians = M_PI/180.0 * rotationDeg;
    return {
            vector2D.x * cos(rotationRadians) - vector2D.y * sin(rotationRadians),
            vector2D.x * sin(rotationRadians) + vector2D.y * cos(rotationRadians)
    };
}

#endif