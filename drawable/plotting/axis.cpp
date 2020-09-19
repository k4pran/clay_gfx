//
// Created by Ryan McCauley on 30/06/2020.
//

#include "axis.h"
#include "../../geometry/line-metrics.h"

Axis::Axis(AxisType axisType, Boundary boundary) : axisType(axisType), boundary(boundary) {}

AxisBuilder Axis::make(AxisType axisType, Boundary boundary) {
    return AxisBuilder(axisType, boundary);
}

std::vector<float> Axis::asVertices() {
    std::vector<float> vertices;

    std::vector<Point2D> spinePoints = createSpine();
    std::vector<float> spineVertices = spineAsVertices(spinePoints);
    vertices.insert(vertices.end(), spineVertices.begin(), spineVertices.end());

    if (drawTicks) {
        std::vector<float> ticks = ticksAsVertices(spinePoints.front(), spinePoints.back());
        vertices.insert(vertices.end(), ticks.begin(), ticks.end());
    }

    return vertices;
}

std::vector<float> Axis::spineAsVertices(std::vector<Point2D> spinePoints) {
    Line spine = Line::make(spinePoints[0], spinePoints[1])
            .withThickness(this->thickness)
            .withCapType(rounded ? CapType::ROUND : CapType::BUTT);
    return spine.asVertices();
}

std::vector<float> Axis::ticksAsVertices(Point2D start, Point2D end) {
    std::vector<Line> ticks = createTicks(start, end);
    std::vector<float> tickVertices;
    for (auto tick : ticks) {
        std::vector<float> lineVertices = tick.asVertices();
        tickVertices.insert(tickVertices.end(), lineVertices.begin(), lineVertices.end());
    }
    return tickVertices;
}

std::vector<Point2D> Axis::createSpine() {
    if (axisType == AxisType::HORIZONTAL) {
        return createHorizontalSpine();
    } else if (axisType == AxisType::VERTICAL) {
        return createVerticalSpine();
    }
    return {};
}

std::vector<Point2D> Axis::createHorizontalSpine() {
    Point2D center = lineMid(boundary.topLeft, boundary.bottomRight);
    float axisLength = Point2D::pointDistance(boundary.topLeft, boundary.topRight);
    Point2D leftAxisPoint = {center.x - axisLength / 2, center.y};
    Point2D rightAxisPoint = {center.x + axisLength / 2, center.y};

    return {leftAxisPoint, rightAxisPoint};
}

std::vector<Point2D> Axis::createVerticalSpine() {
    Point2D center = lineMid(boundary.topLeft, boundary.bottomRight);
    float axisLength = Point2D::pointDistance(boundary.topLeft, boundary.bottomLeft);
    Point2D bottomAxisPoint = {center.x, center.y - axisLength / 2};
    Point2D topAxisPoint = {center.x, center.y + axisLength / 2};

    return {bottomAxisPoint, topAxisPoint};
}

std::vector<Line> Axis::createTicks(Point2D start, Point2D end) {
    if (axisType == AxisType::HORIZONTAL) {
        Point2D startPaddingAdjusted = {start.x + ENDPOINT_PADDING, start.y};
        Point2D endPaddingAdjusted = {end.x - ENDPOINT_PADDING, end.y};
        return createHorizontalAxisTicks(startPaddingAdjusted, endPaddingAdjusted);
    } else if (axisType == AxisType::VERTICAL) {
        Point2D startPaddingAdjusted = {start.x, start.y + ENDPOINT_PADDING};
        Point2D endPaddingAdjusted = {end.x, end.y - ENDPOINT_PADDING};
        return createVerticalAxisTicks(startPaddingAdjusted, endPaddingAdjusted);
    }
    return {};
}

std::vector<Line> Axis::createHorizontalAxisTicks(Point2D start, Point2D end) {
    if (range.min > range.max) {
        // todo error
        return {};
    }
    float inc = determineTickSpacing(start, end);
    std::vector<Line> ticks;
    const float y = start.y;
    for (int i = 0; i < nbTicks; i++) {
        float vOffset = (i * inc);
        float hOffset = thickness / 2;
        Line tick = Line::make({start.x + vOffset, y + hOffset}, {start.x + vOffset, y + TICK_LENGTH + hOffset})
                .withThickness(this->thickness / 2);
        ticks.push_back(tick);
    }
    return ticks;
}

std::vector<Line> Axis::createVerticalAxisTicks(Point2D start, Point2D end) {
    if (range.min > range.max) {
        // todo error
        return {};
    }
    float inc = determineTickSpacing(start, end);
    std::vector<Line> ticks;
    const float x = start.x;
    for (int i = 0; i < nbTicks; i++) {
        float hOffset = (i * inc);
        float vOffset = thickness / 2;
        Line tick = Line::make({x + vOffset, start.y + hOffset}, {x + TICK_LENGTH + vOffset, start.y + hOffset})
                .withThickness(this->thickness / 2);
        ticks.push_back(tick);
    }
    return ticks;
}

float Axis::determineTickSpacing(Point2D &start, Point2D &end) {
    return (Point2D::pointDistance(start, end) / nbTicks);
}

AxisBuilder::AxisBuilder(AxisType axisType, Boundary boundary) : axis(axisType, boundary) {}

AxisBuilder &AxisBuilder::withTitle(const char *title) {
    axis.title = title;
    return *this;
}

AxisBuilder &AxisBuilder::withRange(Range range) {
    axis.range = range;
    return *this;
}

AxisBuilder &AxisBuilder::withNbTicks(int nbTcks) {
    axis.nbTicks = nbTcks;
    return *this;
}

AxisBuilder &AxisBuilder::withTicks(bool drawTicks) {
    axis.drawTicks = drawTicks;
    return *this;
}

AxisBuilder &AxisBuilder::withTicks() {
    axis.drawTicks = true;
    return *this;
}

AxisBuilder &AxisBuilder::withThickness(float thickness) {
    axis.thickness = thickness;
    return *this;
}

AxisBuilder &AxisBuilder::withStrokeColor(RGBA strokeColor) {
    axis.strokeColor = strokeColor;
    return *this;
}

AxisBuilder &AxisBuilder::asRounded(bool rounded) {
    axis.rounded = rounded;
    return *this;
}

AxisBuilder &AxisBuilder::asRounded() {
    axis.rounded = true;
    return *this;
}