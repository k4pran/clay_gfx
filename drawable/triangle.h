//
// Created by Ryan McCauley on 18/06/2020.
//

#ifndef OPENGL_TUTORIAL_TRIANGLE_H
#define OPENGL_TUTORIAL_TRIANGLE_H

#include "drawable.h"
#include "../geometry/anchor.h"

class Triangle: Drawable {

    Point2D pointA;
    Point2D pointB;
    Point2D pointC;

    bool filled = false;
    float thickness;
    JointType jointType;

public:

    Triangle(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC);

    Triangle(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, JointType jointType);

    Triangle(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, float thickness);

    Triangle(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, float thickness, JointType jointType);

    std::vector<float> asVertices() override;

    const Point2D &getPointA() const;

    const Point2D &getPointB() const;

    const Point2D &getPointC() const;

    void setFilled(bool filled);

private:

    std::vector<Point2D> innerTrianglePoints();
};

#endif //OPENGL_TUTORIAL_TRIANGLE_H
