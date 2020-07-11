//
// Created by Ryan McCauley on 11/07/2020.
//

#ifndef OPENGL_TUTORIAL_LINE_H
#define OPENGL_TUTORIAL_LINE_H

#include "../drawable.h"
#include "../../geometry/anchor.h"
#include "color.h"

class LineBuilder;
class Line : Drawable {

    Point2D start;
    Point2D end;
    CapType capType = CapType::BUTT;
    float thickness = 0.02;
    RGBA strokeColor = {0, 0, 0, 1};

public:
    friend class LineBuilder;

    static LineBuilder make(Point2D start, Point2D end);

    Line(Point2D start, Point2D end);

    std::vector<float> asVertices() override;
};

class LineBuilder {
public:
    LineBuilder(Point2D start, Point2D end);

    LineBuilder& withThickness(const float &thickness);

    LineBuilder& withStrokeColor(RGBA rgba);

    LineBuilder& withCapType(CapType capType);

    operator Line &&() {
        return std::move(line);
    }

private:
    Line line;
};

#endif //OPENGL_TUTORIAL_LINE_H
