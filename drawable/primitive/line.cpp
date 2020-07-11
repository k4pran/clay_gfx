//
// Created by Ryan McCauley on 11/07/2020.
//

#include "line.h"

Line::Line(Point2D start, Point2D end): start(start), end(end){};

std::vector<float> Line::asVertices() {
    std::vector<Anchor> anchors = Anchor::createAnchors({start, end}, JointType::BEVEL, capType);

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

        vertices.push_back(strokeColor.red);
        vertices.push_back(strokeColor.green);
        vertices.push_back(strokeColor.blue);
        vertices.push_back(strokeColor.alpha);
    }
    return vertices;
}

LineBuilder Line::make(Point2D start, Point2D end) {
    return LineBuilder(start, end);
}

LineBuilder::LineBuilder(Point2D start, Point2D end): line(start, end) {}

LineBuilder& LineBuilder::withThickness(const float &thickness) {
    line.thickness = thickness;
    return *this;
}

LineBuilder& LineBuilder::withStrokeColor(RGBA rgba) {
    line.strokeColor = rgba;
    return *this;
}

LineBuilder& LineBuilder::withCapType(CapType capType) {
    line.capType = capType;
    return *this;
}