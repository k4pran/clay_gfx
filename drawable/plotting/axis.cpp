//
// Created by Ryan McCauley on 30/06/2020.
//

#include <cmath>
#include "axis.h"
#include "../../geometry/line-metrics.h"

Axis::Axis(AxisType axisType, Boundary boundary): axisType(axisType), boundary(boundary){}

AxisBuilder Axis::make(AxisType axisType, Boundary boundary) {
    return AxisBuilder(axisType, boundary);
}

std::vector<float> Axis::asVertices() {
    std::vector<Point2D> vertices;

    std::vector<Point2D> spinePoints = createSpine();
    std::vector<Point2D> ticks = createTicks(spinePoints.back(),spinePoints.front());

    return std::vector<float>();
}

std::vector<Point2D> Axis::createSpine() {
    if (axisType == AxisType::HORIZONTAL) {
        return createHorizontalSpine();
    }
    else if (axisType == AxisType::VERTICAL) {
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
    Point2D topAxisPoint = {center.x, center.y + axisLength / 2};
    Point2D bottomAxisPoint = {center.x, center.y - axisLength / 2};

    return {topAxisPoint, bottomAxisPoint};
}

std::vector<Point2D> Axis::createTicks(Point2D start, Point2D end) {
    if (axisType == AxisType::HORIZONTAL) {
        return createHorizontalAxisTicks(start, end);
    }
    else if (axisType == AxisType::VERTICAL) {
        return createVerticalAxisTicks(start, end);
    }
    return {};
}

std::vector<Point2D> Axis::createHorizontalAxisTicks(Point2D start, Point2D end) {
    if (range.min > range.max) {
        // todo error
        return {};
    }
    float inc = determineTickSpacing(start, end);
    std::vector<Point2D> tickPoints;
    const float y = start.y;
    for (int i = 0; i < nbTicks; i++) {
        tickPoints.push_back({start.x + i * inc, y});
        tickPoints.push_back({start.x + i * inc, y + TICK_LENGTH});
    }
    return tickPoints;
}

std::vector<Point2D> Axis::createVerticalAxisTicks(Point2D start, Point2D end) {
    if (range.min > range.max) {
        // todo error
        return {};
    }
    float inc = determineTickSpacing(start, end);
    std::vector<Point2D> tickPoints;
    const float x = start.x;
    for (int i = 0; i < nbTicks; i++) {
        tickPoints.push_back({x, start.y + i * inc});
        tickPoints.push_back({x + TICK_LENGTH, start.y + i * inc});
    }
    return tickPoints;
}

float Axis::determineTickSpacing(Point2D &start, Point2D &end) {
    return Point2D::pointDistance(start, end) / nbTicks;
}

AxisBuilder::AxisBuilder(AxisType axisType, Boundary boundary): axis(axisType, boundary) {}

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


AxisBuilder& AxisBuilder::withTicks(bool ticks) {
    axis.ticks = ticks;
    return *this;
}

AxisBuilder& AxisBuilder::withThickness(float thickness) {
    axis.thickness = thickness;
    return *this;
}

AxisBuilder& AxisBuilder::withStrokeColor(RGBA strokeColor) {
    axis.strokeColor = strokeColor;
    return *this;
}