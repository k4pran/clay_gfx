//
// Created by Ryan McCauley on 30/06/2020.
//

#ifndef OPENGL_TUTORIAL_AXIS_H
#define OPENGL_TUTORIAL_AXIS_H

#include "../primitive/color.h"
#include "../drawable.h"
#include "../attribute/range.h"
#include "../attribute/boundary.h"
#include "../primitive/line.h"

class AxisBuilder;
enum class AxisType;
class Axis: Drawable {

    float TICK_LENGTH = 0.015;
    float ENDPOINT_PADDING = 0.05;
    const char *title = "";
    AxisType axisType;
    Boundary boundary;
    Range range = {-100, 100};
    int nbTicks = 10;
    bool drawTicks = false;
    bool rounded = false;
    float thickness = 0.02;
    RGBA strokeColor = {0.0, 0.0, 0.0, 1.0};

    std::vector<Point2D> createSpine();
    std::vector<Point2D> createHorizontalSpine();
    std::vector<Point2D> createVerticalSpine();

    std::vector<Line> createTicks(Point2D start, Point2D end);
    std::vector<Line> createHorizontalAxisTicks(Point2D start, Point2D end);
    std::vector<Line> createVerticalAxisTicks(Point2D start, Point2D end);
    float determineTickSpacing(Point2D &start, Point2D &end);

public:
    friend class AxisBuilder;

    Axis(AxisType axisType, Boundary boundary);

    static AxisBuilder make(AxisType axisType, Boundary boundary);

    std::vector<float> asVertices() override;

    std::vector<float> spineAsVertices(std::vector<Point2D> spinePoints);

    std::vector<float> ticksAsVertices(Point2D start, Point2D end);


};

class AxisBuilder {
public:
    AxisBuilder(AxisType axisType, Boundary boundary);

    AxisBuilder& withTitle(const char *title);

    AxisBuilder& withRange(Range range);

    AxisBuilder& withNbTicks(int ticks);

    AxisBuilder& withTicks(bool drawTicks);

    AxisBuilder& withTicks();

    AxisBuilder& withThickness(float thickness);

    AxisBuilder& withStrokeColor(RGBA rgba);

    AxisBuilder& asRounded(bool rounded);

    AxisBuilder& asRounded();

    operator Axis &&() {
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
