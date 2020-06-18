//
// Created by Ryan McCauley on 06/06/2020.
//

#ifndef OPENGL_TUTORIAL_POLYLINE_H
#define OPENGL_TUTORIAL_POLYLINE_H

#include <vector>
#include "../drawable.h"
#include "../../geometry/anchor.h"

class Polyline : Drawable {

    std::vector<Point2D> points;
    JointType jointType;
    CapType capType;
    float thickness;

public:
    Polyline() : thickness(0.05), jointType(JointType::MITER), capType(CapType::SQUARE){};

    Polyline(std::vector<Point2D> points, float thickness):
        points(points), thickness(thickness), jointType(JointType::MITER), capType(CapType::SQUARE){};

    Polyline(std::vector<Point2D> points, float thickness, JointType jointType, CapType capType):
        points(points), thickness(thickness), jointType(jointType), capType(capType){};

    std::vector<float> asVertices() override;
    int nbLines() const;
};

#endif //OPENGL_TUTORIAL_POLYLINE_H
