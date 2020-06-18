//
// Created by Ryan McCauley on 06/06/2020.
//

#include "polyline.h"

int Polyline::nbLines() const {
    return this->points.size() - 1;
}

std::vector<Point2D> Polyline::asVertices() {
    return {};
}

Polyline::Polyline(std::vector<Point2D> points): points(points) {}
