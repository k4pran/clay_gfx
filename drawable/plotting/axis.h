//
// Created by Ryan McCauley on 30/06/2020.
//

#ifndef OPENGL_TUTORIAL_AXIS_H
#define OPENGL_TUTORIAL_AXIS_H

#include "../primitive/color.h"
#include "../drawable.h"
#include "../attribute/range.h"
#include "../attribute/boundary.h"

class AxisBuilder;
enum class AxisType;
class Axis: Drawable {

    const float TICK_LENGTH = 0.01;
    const char *title = "";
    AxisType axisType;
    Boundary boundary;
    Range range = {-100, 100};
    int nbTicks = 10;
    bool ticks = false;
    float thickness = 0.02;
    RGBA strokeColor = {0.0, 0.0, 0.0, 1.0};

    std::vector<Point2D> createSpine();
    std::vector<Point2D> createHorizontalSpine();
    std::vector<Point2D> createVerticalSpine();

    std::vector<Point2D> createTicks(Point2D start, Point2D end);
    std::vector<Point2D> createHorizontalAxisTicks(Point2D start, Point2D end);
    std::vector<Point2D> createVerticalAxisTicks(Point2D start, Point2D end);
    float determineTickSpacing(Point2D &start, Point2D &end);

public:
    friend class AxisBuilder;

    Axis(AxisType axisType, Boundary boundary);

    static AxisBuilder make(AxisType axisType, Boundary boundary);

    std::vector<float> asVertices() override;
};

class AxisBuilder {
public:
    AxisBuilder(AxisType axisType, Boundary boundary);

    AxisBuilder& withTitle(const char *title);

    AxisBuilder& withRange(Range range);

    AxisBuilder& withNbTicks(int ticks);

    AxisBuilder& withTicks(bool ticks);

    AxisBuilder& withThickness(float thickness);

    AxisBuilder& withStrokeColor(RGBA rgba);


    explicit operator Axis &&() {
        return std::move(axis);
    }

private:
    Axis axis;
};

enum class AxisType {
    HORIZONTAL,
    VERTICAL
};

#endif //OPENGL_TUTORIAL_AXIS_H
