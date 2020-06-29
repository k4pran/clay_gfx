//
// Created by Ryan McCauley on 06/06/2020.
//

#include "polyline.h"


Polyline::Polyline(std::vector<Point2D> points): points(points){};

int Polyline::nbLines() const {
    return points.size() - 1;
}

std::vector<float> Polyline::asVertices() {
    std::vector<Anchor> anchors = Anchor::createAnchors(points, jointType, capType);

    std::vector<Point2D> triangulatedPoints;
    for (auto & anchor : anchors) {
        AnchorMetrics anchorMetrics = AnchorMetrics(anchor, thickness);
        std::vector<Point2D> anchorVertices = anchorMetrics.triangulate();
        triangulatedPoints.insert(triangulatedPoints.end(), anchorVertices.begin(), anchorVertices.end());
    }

    std::vector<float> vertices;
    for (auto & triangulatedPoint : triangulatedPoints) {
        vertices.push_back(triangulatedPoint.x);
        vertices.push_back(triangulatedPoint.y);
        vertices.push_back(0);

        // color todo
        vertices.push_back(strokeColor.red);
        vertices.push_back(strokeColor.green);
        vertices.push_back(strokeColor.blue);
        vertices.push_back(strokeColor.alpha);
    }
    return vertices;
}

PolylineBuilder Polyline::make(std::vector<Point2D> points) {
    return PolylineBuilder(points);
}

PolylineBuilder::PolylineBuilder(std::vector<Point2D> points): polyline(points) {}

PolylineBuilder& PolylineBuilder::withThickness(const float &thickness) {
    polyline.thickness = thickness;
    return *this;
}

PolylineBuilder& PolylineBuilder::withJoint(const JointType &jointType) {
    polyline.jointType = jointType;
    return *this;
}

PolylineBuilder & PolylineBuilder::withStrokeColor(RGBA rgba) {
    polyline.strokeColor = rgba;
    return *this;
}
