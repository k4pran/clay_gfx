//
// Created by Ryan McCauley on 20/06/2020.
//

#include "rect.h"
#include "../../geometry/line-metrics.h"

Rect::Rect(const Point2D &pointA,
           const Point2D &pointB,
           const Point2D &pointC,
           const Point2D &pointD): pointA(pointA), pointB(pointB), pointC(pointC), pointD(pointD) {}

std::vector<float> Rect::asVertices() {
    // should start at the center of one of the sides so joints are handled correctly
    Point2D rectSideMid = lineMid(pointA, pointB);
    std::vector<Point2D> rectPoints = {rectSideMid, pointB, pointC, pointD, pointA, rectSideMid};

    std::vector<Anchor> anchors = Anchor::createAnchors(rectPoints, jointType, CapType::BUTT);

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

    if (filled) {
        std::vector<Point2D> innerPoints = triangulateInnerRect();
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

std::vector<Point2D> Rect::triangulateInnerRect() {
    std::vector<Point2D> innerPoints = innerRectPoints();
    return {innerPoints[0], innerPoints[1], innerPoints[2],
            innerPoints[2], innerPoints[3], innerPoints[0]};
}

std::vector<Point2D> Rect::innerRectPoints() {
    Point2D centerPoint = lineMid(pointA, pointC);

    Vector2D vecAToCenter = points2DtoVector2D(pointA, centerPoint);
    vecAToCenter.normalize();
    vecAToCenter.scale(thickness / 2);

    Vector2D vecBToCenter = points2DtoVector2D(pointB, centerPoint);
    vecBToCenter.normalize();
    vecBToCenter.scale(thickness / 2);

    Vector2D vecCToCenter = points2DtoVector2D(pointC, centerPoint);
    vecCToCenter.normalize();
    vecCToCenter.scale(thickness / 2);

    Vector2D vecDToCenter = points2DtoVector2D(pointD, centerPoint);
    vecDToCenter.normalize();
    vecDToCenter.scale(thickness / 2);

    Point2D innerPointA = pointA.translateCopy(vecAToCenter);
    Point2D innerPointB = pointB.translateCopy(vecBToCenter);
    Point2D innerPointC = pointC.translateCopy(vecCToCenter);
    Point2D innerPointD = pointD.translateCopy(vecDToCenter);

    return {innerPointA, innerPointB, innerPointC, innerPointD};
}


const Point2D &Rect::getPointA() const {
    return pointA;
}

const Point2D &Rect::getPointB() const {
    return pointB;
}

const Point2D &Rect::getPointC() const {
    return pointC;
}

const Point2D &Rect::getPointD() const {
    return pointD;
}

RectBuilder Rect::make(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC, const Point2D &pointD) {
    return RectBuilder(pointA, pointB, pointC, pointD);
}

RectBuilder::RectBuilder(const Point2D &pointA,
                         const Point2D &pointB,
                         const Point2D &pointC,
                         const Point2D &pointD): rect(pointA, pointB, pointC, pointD) {}
