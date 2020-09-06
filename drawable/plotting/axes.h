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
#include <experimental/optional>

class AxesBuilder2D;
class Axes2D: Drawable {

    Boundary boundary;
    std::experimental::optional<Axis> vAxis;
    std::experimental::optional<Axis> hAxis;

    const char *title = "";
    Range range = {-100, 100};
    int nbTicks = 10;
    bool drawTicks = false;
    float thickness = 0.02;
    RGBA strokeColor = {0.0, 0.0, 0.0, 1.0};

public:
    friend class AxesBuilder2D;

    static AxesBuilder2D make(Boundary boundary);

    std::vector<float> asVertices() override;

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
