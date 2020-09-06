//
// Created by Ryan McCauley on 06/09/2020.
//

#include "axes.h"

Axes2D::Axes2D(Boundary boundary) :
        boundary(boundary),
        vAxis(Axis::make(AxisType::VERTICAL, boundary)),
        hAxis(Axis::make(AxisType::HORIZONTAL, boundary)) {
}

std::vector<float> Axes2D::asVertices() {
    return {}; // todo
}

AxesBuilder2D::AxesBuilder2D(Boundary boundary) : axes(boundary) {

}
