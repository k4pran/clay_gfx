//
// Created by Ryan McCauley on 06/09/2020.
//

#include "axes.h"

Axes2D::Axes2D(Boundary boundary) :
        boundary(boundary) {
}

AxesBuilder2D Axes2D::make(Boundary boundary) {
    return {boundary};
}

std::vector<float> Axes2D::asVertices() {
    if (!vAxis) {
        vAxis = {Axis::make(AxisType::VERTICAL, boundary)
                         .withTicks(drawTicks)
                         .withThickness(thickness)
                         .withNbTicks(nbTicks)
                         .withRange(range).withStrokeColor(strokeColor)};
    }
    if (!hAxis) {
        hAxis = {Axis::make(AxisType::HORIZONTAL, boundary)
                         .withTicks(drawTicks)
                         .withThickness(thickness)
                         .withNbTicks(nbTicks)
                         .withRange(range).withStrokeColor(strokeColor)};
    }

    std::vector<float> vAxisVertices = vAxis->asVertices();
    std::vector<float> hAxisVertices = hAxis->asVertices();

    std::vector<float> vertices;
    vertices.reserve(vAxisVertices.size() + hAxisVertices.size());

    vertices.insert(vertices.end(), hAxisVertices.begin(), hAxisVertices.end());
    vertices.insert(vertices.end(), vAxisVertices.begin(), vAxisVertices.end());
    return vertices;
}

AxesBuilder2D::AxesBuilder2D(Boundary boundary) : axes(boundary) {}

AxesBuilder2D &AxesBuilder2D::withTitle(const char *title) {
    axes.title = title;
    return *this;
}

AxesBuilder2D &AxesBuilder2D::withRange(Range range) {
    axes.range = range;
    return *this;
}

AxesBuilder2D &AxesBuilder2D::withNbTicks(int nbTcks) {
    axes.nbTicks = nbTcks;
    return *this;
}


AxesBuilder2D &AxesBuilder2D::withTicks() {
    axes.drawTicks = true;
    return *this;
}

AxesBuilder2D &AxesBuilder2D::withThickness(float thickness) {
    axes.thickness = thickness;
    return *this;
}

AxesBuilder2D &AxesBuilder2D::withStrokeColor(RGBA strokeColor) {
    axes.strokeColor = strokeColor;
    return *this;
}