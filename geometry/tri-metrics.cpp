//
// Created by Ryan McCauley on 20/06/2020.
//

#include "point.h"
#include "tri-metrics.h"

Point2D findCentroid(const Point2D& pointA, const Point2D& pointB, const Point2D& pointC) {
    return {(pointA.x + pointB.x + pointC.x) / 3, (pointA.y + pointB.y + pointC.y) / 3};
}

Point2D findInCenter(const Point2D &pointA, const Point2D &pointB, const Point2D &pointC) {
    float sideLengthA = pointDistance(pointB, pointC);
    float sideLengthB = pointDistance(pointC, pointA);
    float sideLengthC = pointDistance(pointA, pointB);

    float xTotal = sideLengthA * pointA.x + sideLengthB * pointB.x + sideLengthC * pointC.x;
    float yTotal = sideLengthA * pointA.y + sideLengthB * pointB.y + sideLengthC * pointC.y;
    float sideLengthTotal = sideLengthA + sideLengthB + sideLengthC;
    return {xTotal / sideLengthTotal, yTotal / sideLengthTotal};
}
