//
// Created by Ryan McCauley on 18/06/2020.
//

#ifndef OPENGL_TUTORIAL_TRIANGLE_H
#define OPENGL_TUTORIAL_TRIANGLE_H

#include "../drawable.h"
#include "../../geometry/anchor.h"
#include "../primitive/color.h"

class TriangleBuilder;
class Triangle: Drawable {

    Point2D pointA;
    Point2D pointB;
    Point2D pointC;

    bool filled = false;
    RGBA strokeColor = {0, 0, 0, 1};
    RGBA fillColor = {1, 1, 1, 1};
    float thickness = 0.02;
    JointType jointType = JointType::MITER;

public:
    friend class TriangleBuilder;

    static TriangleBuilder make(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC);

    Triangle(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC);

    std::vector<float> asVertices() override;

    const Point2D &getPointA() const;

    const Point2D &getPointB() const;

    const Point2D &getPointC() const;

    void setFilled(bool filled);

private:

    std::vector<Point2D> innerTrianglePoints();
};

class TriangleBuilder {
public:
    TriangleBuilder(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC);

    TriangleBuilder& withThickness(const float &thickness);

    TriangleBuilder& withJoint(const JointType &jointType);

    TriangleBuilder& withStrokeColor(const RGBA strokeColor);

    TriangleBuilder& withFillColor(const RGBA fillColor);

    TriangleBuilder& filled();

    operator Triangle &&() {
        return std::move(triangle);
    }
private:
    Triangle triangle;
};

#endif //OPENGL_TUTORIAL_TRIANGLE_H
