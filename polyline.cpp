//
// Created by Ryan McCauley on 06/06/2020.
//

#include "polyline.h"
#include "anchor.h"

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

        // color todo
        vertices.push_back(0.);
        vertices.push_back(0.);
        vertices.push_back(0.);
        vertices.push_back(0.);
    }
    return vertices;
}