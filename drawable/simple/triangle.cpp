//
// Created by Ryan McCauley on 18/06/2020.
//

#include "triangle.h"
#include "../../geometry/line-metrics.h"
#include "../../geometry/tri-metrics.h"

Triangle::Triangle(const Point2D &pointA,
                   const Point2D &pointB,
                   const Point2D &pointC): pointA(pointA), pointB(pointB), pointC(pointC) {}

std::vector<float> Triangle::asVertices() {
    // should start at the center of one of the sides so joints are handled correctly
    Point2D triangleSideMid = lineMid(pointA, pointB);
    std::vector<Point2D> trianglePoints = {triangleSideMid, pointB, pointC, pointA, triangleSideMid};

    std::vector<Anchor> anchors = Anchor::createAnchors(trianglePoints, jointType, CapType::BUTT);

    std::vector<Point2D> triangulatedPoints;
    for (auto & anchor : anchors) {
        AnchorMetrics anchorMetrics = AnchorMetrics(anchor, thickness);
        std::vector<Point2D> anchorVertices = anchorMetrics.triangulate();
        triangulatedPoints.insert(triangulatedPoints.end(), anchorVertices.begin(), anchorVertices.end());
    }

    std::vector<Point2D> innerPoints = innerTrianglePoints();

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

    if (filled) {
        for (auto &innerPoint : innerPoints) {
            vertices.push_back(innerPoint.x);
            vertices.push_back(innerPoint.y);
            vertices.push_back(0);

            vertices.push_back(fillColor.red);
            vertices.push_back(fillColor.green);
            vertices.push_back(fillColor.blue);
            vertices.push_back(fillColor.alpha);
        }
    }
    return vertices;
}

std::vector<Point2D> Triangle::innerTrianglePoints() {
    Point2D incenter = findInCenter(pointA, pointB, pointC);
    Vector2D pointAToCentroid = {points2DtoVector2D(pointA, incenter)};
    pointAToCentroid.normalize();
    pointAToCentroid.scale(thickness / 2);

    Vector2D pointBToCentroid = points2DtoVector2D(pointB, incenter);
    pointBToCentroid.normalize();
    pointBToCentroid.scale(thickness / 2);

    Vector2D pointCToCentroid = points2DtoVector2D(pointC, incenter);
    pointCToCentroid.normalize();
    pointCToCentroid.scale(thickness / 2);

    Point2D innerPointA = {pointA.x + pointAToCentroid.x, pointA.y + pointAToCentroid.y};
    Point2D innerPointB = {pointB.x + pointBToCentroid.x, pointB.y + pointBToCentroid.y};
    Point2D innerPointC = {pointC.x + pointCToCentroid.x, pointC.y + pointCToCentroid.y};

    return {innerPointA, innerPointB, innerPointC, innerPointA};
}

const Point2D &Triangle::getPointA() const {
    return pointA;
}

const Point2D &Triangle::getPointB() const {
    return pointB;
}

const Point2D &Triangle::getPointC() const {
    return pointC;
}

void Triangle::setFilled(bool filled) {
    Triangle::filled = filled;
}

TriangleBuilder Triangle::make(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC) {
    return TriangleBuilder(pointA, pointB, pointC);
}

TriangleBuilder &TriangleBuilder::withThickness(const float &thickness) {
    triangle.thickness = thickness;
    return *this;
}

TriangleBuilder &TriangleBuilder::withJoint(const JointType &jointType) {
    triangle.jointType = jointType;
    return *this;
}

TriangleBuilder &TriangleBuilder::withStrokeColor(RGBA rgba) {
    triangle.strokeColor = rgba;
    return *this;
}

TriangleBuilder &TriangleBuilder::withFillColor(RGBA rgba) {
    triangle.fillColor = rgba;
    return *this;
}

TriangleBuilder &TriangleBuilder::filled() {
    triangle.filled = true;
    return *this;
}

TriangleBuilder::TriangleBuilder(const Point2D &pointA,
                                 const Point2D &pointB,
                                 const Point2D &pointC): triangle(pointA, pointB, pointC) {}
