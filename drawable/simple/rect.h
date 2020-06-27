//
// Created by Ryan McCauley on 20/06/2020.
//

#ifndef OPENGL_TUTORIAL_RECT_H
#define OPENGL_TUTORIAL_RECT_H

#include "../../geometry/point.h"
#include "../drawable.h"
#include "../primitive/color.h"
#include "../../geometry/anchor.h"

class RectBuilder;
class Rect: Drawable {

    Point2D pointA;
    Point2D pointB;
    Point2D pointC;
    Point2D pointD;

    bool filled = false;
    RGBA strokeColor = {0, 0, 0, 1};
    RGBA fillColor = {1, 1, 1, 1};
    float thickness = 0.02;
    JointType jointType;

public:
    friend class RectBuilder;

    static RectBuilder make(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, const Point2D &pointD);

    Rect(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, const Point2D &pointD);

    std::vector<float> asVertices() override;

    const Point2D &getPointA() const;

    const Point2D &getPointB() const;

    const Point2D &getPointC() const;

    const Point2D &getPointD() const;

private:

    std::vector<Point2D> triangulateInnerRect();
    std::vector<Point2D> innerRectPoints();
};

class RectBuilder {
public:
    RectBuilder(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, const Point2D &pointD);

    RectBuilder& withThickness(const float &thickness);

    RectBuilder& withJoint(const JointType &jointType);

    RectBuilder& filled();

    RectBuilder & withStrokeColor(RGBA rgba);

    RectBuilder & withFillColor(RGBA rgba);

    operator Rect &&() {
        return std::move(rect);
    }

private:
    Rect rect;
};

#endif //OPENGL_TUTORIAL_RECT_H
