//
// Created by Ryan McCauley on 28/06/2020.
//

#ifndef OPENGL_TUTORIAL_CIRCLE_H
#define OPENGL_TUTORIAL_CIRCLE_H

#include <vector>
#include "../primitive/color.h"
#include "../../geometry/point-geo.h"
#include "../../geometry/anchor.h"
#include "../drawable.h"

class CircleBuilder;
class Circle: Drawable {

    Point2D center;
    float radius;
    bool filled = false;
    RGBA strokeColor = {0, 0, 0, 1};
    RGBA fillColor = {1, 1, 1, 1};
    float thickness = 0.02;

public:
    friend class CircleBuilder;

    static CircleBuilder make(const Point2D &center, const float radius);

    Circle(const Point2D &center, const float radius);

    std::vector<float> asVertices() override;

    const Point2D &getCenter() const;

    void setFilled(bool filled);
};

class CircleBuilder {
public:
    CircleBuilder(const Point2D &center, float radius);

    CircleBuilder& withThickness(float thickness);

    CircleBuilder& withStrokeColor(RGBA strokeColor);

    CircleBuilder& withFillColor(RGBA fillColor);

    CircleBuilder& filled();

    operator Circle &&() {
        return std::move(circle);
    }
private:
    Circle circle;
};

#endif //OPENGL_TUTORIAL_CIRCLE_H
