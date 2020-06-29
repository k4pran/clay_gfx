//
// Created by Ryan McCauley on 06/06/2020.
//

#ifndef OPENGL_TUTORIAL_POLYLINE_H
#define OPENGL_TUTORIAL_POLYLINE_H

#include <vector>
#include "../drawable.h"
#include "../../geometry/anchor.h"
#include "color.h"

class PolylineBuilder;
class Polyline : Drawable {

    std::vector<Point2D> points;
    JointType jointType = JointType::MITER;
    CapType capType = CapType::BUTT;
    float thickness = 0.02;
    RGBA strokeColor = {0, 0, 0, 1};

public:
    friend class PolylineBuilder;

    static PolylineBuilder make(std::vector<Point2D> points);

    Polyline(std::vector<Point2D> points);

    std::vector<float> asVertices() override;
    int nbLines() const;
};

class PolylineBuilder {
public:
    PolylineBuilder(std::vector<Point2D> points);

    PolylineBuilder& withThickness(const float &thickness);

    PolylineBuilder& withJoint(const JointType &jointType);

    PolylineBuilder & withStrokeColor(RGBA rgba);

    operator Polyline &&() {
        return std::move(polyline);
    }

private:
    Polyline polyline;
};

#endif //OPENGL_TUTORIAL_POLYLINE_H
