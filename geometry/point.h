//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_POINT_H
#define OPENGL_TUTORIAL_POINT_H

struct Point2D {
    float x, y;

    bool equals(const Point2D& otherPoint) const;
};

Point2D lineMid(const Point2D& a, const Point2D& b);

float pointDistance(const Point2D& a, const Point2D& b);

#endif