//
// Created by Ryan McCauley on 06/09/2020.
//

#ifndef OPENGL_TUTORIAL_AXES_H
#define OPENGL_TUTORIAL_AXES_H

#include "../attribute/boundary.h"
#include "../attribute/range.h"
#include "../primitive/color.h"
#include "../drawable.h"
#include "axis.h"

class AxesBuilder;
class Axes2D: Drawable {

    Boundary boundary;
    Axis vAxis;
    Axis hAxis;

    std::vector<float> asVertices() override;

public:
    friend class AxesBuilder2D;

    Axes2D(Boundary boundary);
};

class AxesBuilder2D {
public:
    AxesBuilder2D(Boundary boundary);

    AxesBuilder2D& withTitle(const char *title);

    AxesBuilder2D& withRange(Range range);

    AxesBuilder2D& withNbTicks(int ticks);

    AxesBuilder2D& withTicks();

    AxesBuilder2D& withThickness(float thickness);

    AxesBuilder2D& withStrokeColor(RGBA rgba);


    operator Axes2D &&() {
        return std::move(axes);
    }

private:
    Axes2D axes;
};

#endif //OPENGL_TUTORIAL_AXES_H
