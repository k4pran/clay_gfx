//
// Created by Ryan McCauley on 27/05/2020.
//
// Algorithm inspired by article - http://artgrammer.blogspot.com/2011/07/drawing-polylines-by-tessellation.html
// Author of the algorithm is the creator of vaser - https://github.com/tyt2y3/vaserenderer
//

#include <vector>
#include <cmath>
#include "anchor.h"
#include "vector.h"
#include "line-metrics.h"

AnchorMetrics::AnchorMetrics(Anchor anchor, float thickness): anchor(anchor), thickness(thickness) {

    // convert begin and center points to a vector
    Vector2D vecAB = points2DtoVector2D(anchor.begin, anchor.center);
    vecAB.normalize();

    // get a second vector 90 degrees from AB to the border with magnitude half the thickness
    Vector2D vecAToBorder = Vector2D{vecAB.x, vecAB.y};
    vecAToBorder.rotate(90);
    vecAToBorder.scale(thickness / 2);

    // convert begin and center points to a vector
    Vector2D vecCB = points2DtoVector2D(anchor.end, anchor.center);
    vecCB.normalize();

    // get a third vector -90 degrees from CB to the border with magnitude half the thickness
    Vector2D vecCToBorder = Vector2D{vecCB.x, vecCB.y};
    vecCToBorder.rotate(-90);
    vecCToBorder.scale(thickness / 2);

    float signedA = signedArea(anchor.begin, anchor.center, anchor.end);

    beginToBorder = vecAToBorder;
    endToBorder = vecCToBorder;
    if (signedA > 0) {
        beginToBorder.scale(-1);
        endToBorder.scale(-1);
    }
}

std::vector<Anchor> Anchor::createAnchors(std::vector<Point2D> points,
                                          const JointType& jointType,
                                          const CapType& capType) {
    if (points.size() < 2) {
        return std::vector<Anchor>{Anchor{}};
    }

    if (points.size() == 2) {
        LineMetrics singleLine = {points.front(), points.back()};
        points = singleLine.splitIntoThree();
    }

    std::vector<Point2D> midPoints;
    for (int i = 1; i < points.size(); i++) {
        midPoints.push_back(lineMid(points.at(i - 1), points.at(i)));
    }

    midPoints.at(0) = points.at(0);
    midPoints.at(points.size() - 2) = points.back();

    std::vector<Anchor> anchors;
    for (int i = 1; i < points.size() - 1; i++) {
        if (midPoints.at(i - 1).equals(midPoints.at(i))) {
            Point2D quarter = lineMid(midPoints.at(i - 1), points.at(i));
            anchors.push_back({midPoints.at(i - 1), quarter, points.at(i),
                               capType, jointType, SegmentPosition::MIDDLE});
        }
        else {
            anchors.push_back({midPoints.at(i - 1), points.at(i), midPoints.at(i),
                               capType, jointType, SegmentPosition::MIDDLE});
        }
    }

    if (anchors.size() == 1) {
        anchors.front().segmentPosition = SegmentPosition::COMPLETE;
    }
    else {
        anchors.front().segmentPosition = SegmentPosition::START;
        anchors.back().segmentPosition = SegmentPosition::END;
    }
    return anchors;
}

std::vector<Point2D> AnchorMetrics::triangulate() const {

    std::vector<Point2D> borderCorners = findBorderCorners();

    Point2D centerBorderA = anchor.center.translateCopy(beginToBorder);
    Point2D centerBorderB = anchor.center.translateCopy(endToBorder);
    Point2D beginBorder = anchor.center.translateCopy(beginToBorder);
    Point2D endBorder = anchor.end.translateCopy(endToBorder);

    Intercept intersection = findIntersection({beginBorder, centerBorderA}, {endBorder, centerBorderB});

    // no joint required for straight anchors
    if (intersection.interceptResult == InterceptResult::COLLINEAR) {
        return triangulateStraight();
    }

    else {
        return triangulateAnchored();
    }
}

std::vector<Point2D> AnchorMetrics::triangulateAnchored() const {
    std::vector<Point2D> borderCorners = findBorderCorners();

    Point2D beginVert1 = anchor.begin.translateCopy(beginToBorder);
    Point2D beginVert2 = anchor.begin.translateCopy(beginToBorder.reverseCopy());

    Point2D endVert5 = anchor.end.translateCopy(endToBorder);
    Point2D endVert6 = anchor.end.translateCopy(endToBorder.reverseCopy());

    std::vector<Point2D> vertices = triangulateLineRects();

    if (anchor.jointType == JointType::MITER) {
        std::vector<Point2D> miterVertices = triangulateMiterJoint();
        vertices.insert(vertices.end(), miterVertices.begin(), miterVertices.end());
    }
    else if (anchor.jointType == JointType::ROUND) {
        std::vector<Point2D> roundVertices = triangulateRoundJoint();
        vertices.insert(vertices.end(), roundVertices.begin(), roundVertices.end());
    }

    if (anchor.segmentPosition == SegmentPosition::START || anchor.segmentPosition == SegmentPosition::COMPLETE) {
        std::vector<Point2D> capPoints = triangulateCap(anchor.center, anchor.begin,
                                                        *this, beginVert1, beginVert2);
        vertices.insert(vertices.end(), capPoints.begin(), capPoints.end());
    }
    if (anchor.segmentPosition == SegmentPosition::END || anchor.segmentPosition == SegmentPosition::COMPLETE) {
        std::vector<Point2D> capPoints = triangulateCap(anchor.center, anchor.end,
                                                        *this, endVert5, endVert6);
        vertices.insert(vertices.end(), capPoints.begin(), capPoints.end());
    }
    return vertices;
}

std::vector<Point2D> AnchorMetrics::triangulateStraight() const {
    std::vector<Point2D> borderCorners = findBorderCorners();

    std::vector<Point2D> vertices = {borderCorners[0], borderCorners[1], borderCorners[3],
                                     borderCorners[0], borderCorners[2], borderCorners[3]};

    if (anchor.segmentPosition == SegmentPosition::START || anchor.segmentPosition == SegmentPosition::COMPLETE) {
        std::vector<Point2D> capPoints = triangulateCap(anchor.center, anchor.begin,
                                                        *this, borderCorners[0], borderCorners[1]);
        vertices.insert(vertices.end(), capPoints.begin(), capPoints.end());
    }
    if (anchor.segmentPosition == SegmentPosition::END || anchor.segmentPosition == SegmentPosition::COMPLETE) {
        std::vector<Point2D> capPoints = triangulateCap(anchor.center, anchor.end,
                                                        *this, borderCorners[3], borderCorners[4]);
        vertices.insert(vertices.end(), capPoints.begin(), capPoints.end());
    }
    return vertices;
}

std::vector<Point2D> AnchorMetrics::triangulateLineRects() const {
    std::vector<Point2D> vertices;

    Point2D centerBorderA = anchor.center.translateCopy(beginToBorder);
    Point2D centerBorderB = anchor.center.translateCopy(endToBorder);
    Point2D beginBorder = anchor.begin.translateCopy(beginToBorder);
    Point2D endBorder = anchor.end.translateCopy(endToBorder);
    Intercept intersection = findIntersection({beginBorder, centerBorderA}, {endBorder, centerBorderB});

    Point2D intersectionPoint = intersection.intercept;

    Vector2D centerToJoint3 = Vector2D{points2DtoVector2D(anchor.center, intersectionPoint)};

    Point2D beginVert1 = anchor.begin.translateCopy(beginToBorder);
    Point2D beginVert2 = anchor.begin.translateCopy(beginToBorder.reverseCopy());
    Point2D beginVert3 = anchor.center.translateCopy(centerToJoint3.reverseCopy());

    Point2D beginVert4 = anchor.begin.translateCopy(beginToBorder);
    Point2D beginVert5 = anchor.center.translateCopy(centerToJoint3.reverseCopy());
    Point2D beginVert6 = anchor.center.translateCopy(beginToBorder);

    Point2D endVert1 = anchor.center.translateCopy(centerToJoint3.reverseCopy());
    Point2D endVert2 = anchor.center.translateCopy(endToBorder);
    Point2D endVert3 = anchor.end.translateCopy(endToBorder);

    Point2D endVert4 = anchor.center.translateCopy(centerToJoint3.reverseCopy());
    Point2D endVert5 = anchor.end.translateCopy(endToBorder);
    Point2D endVert6 = anchor.end.translateCopy(endToBorder.reverseCopy());

    return {beginVert1, beginVert2, beginVert3,
            beginVert4, beginVert5, beginVert6,
            endVert1, endVert2, endVert3,
            endVert4, endVert5, endVert6};
}

std::vector<Point2D> AnchorMetrics::triangulateMiterJoint() const {
    std::vector<Point2D> vertices;

    Point2D centerBorderA = anchor.center.translateCopy(beginToBorder);
    Point2D centerBorderB = anchor.center.translateCopy(endToBorder);
    Point2D beginBorder = anchor.begin.translateCopy(beginToBorder);
    Point2D endBorder = anchor.end.translateCopy(endToBorder);
    Intercept intersection = findIntersection({beginBorder, centerBorderA}, {endBorder, centerBorderB});

    Point2D intersectionPoint = intersection.intercept;

    Vector2D centerToJoint3 = Vector2D{points2DtoVector2D(anchor.center, intersectionPoint)};

    Point2D centerVert1 = anchor.center.translateCopy(centerToJoint3.reverseCopy());
    Point2D centerVert2 = anchor.center.translateCopy(beginToBorder);
    Point2D centerVert3 = anchor.center.translateCopy(endToBorder);

    // joint
    Point2D joint1 = anchor.center.translateCopy(beginToBorder);
    Point2D joint2 = anchor.center.translateCopy(endToBorder);
    Point2D joint3 = anchor.center.translateCopy(centerToJoint3);

    vertices.push_back(centerVert1);
    vertices.push_back(centerVert2);
    vertices.push_back(centerVert3);
    vertices.push_back(joint1);
    vertices.push_back(joint2);
    vertices.push_back(joint3);

    return vertices;
}

std::vector<Point2D> AnchorMetrics::triangulateRoundJoint() const {
    std::vector<Point2D> vertices;
    Point2D centerBorderA = anchor.center.translateCopy(beginToBorder);
    Point2D centerBorderB = anchor.center.translateCopy(endToBorder);
    Point2D beginBorder = anchor.begin.translateCopy(beginToBorder);
    Point2D endBorder = anchor.end.translateCopy(endToBorder);
    Intercept intersection = findIntersection({beginBorder, centerBorderA}, {endBorder, centerBorderB});

    Vector2D centerToJoint3 = Vector2D{points2DtoVector2D(anchor.center, intersection.intercept)};

    Point2D arcOrigin = anchor.center.translateCopy(centerToJoint3.reverseCopy());

    Vector2D arcStart = points2DtoVector2D(arcOrigin, centerBorderA);
    arcStart.normalize();

    Vector2D arcEnd = points2DtoVector2D(arcOrigin, centerBorderB);
    arcEnd.normalize();

    float arcStartAngle = acos(arcStart.x);
    float arcEndAngle = acos(arcEnd.x);

    if (arcStart.y > 0){
        arcStartAngle = 2 * M_PI - arcStartAngle;
    }
    if (arcEnd.y > 0){
        arcEndAngle = 2 * M_PI - arcEndAngle;
    }

    float radius = Point2D::pointDistance(centerBorderA, arcOrigin);

    bool incremental = true;
    if (arcStartAngle > arcEndAngle) {
        incremental = false; // decrement
    }

    std::vector<Point2D> jointVerts;
    if ( incremental) {
        for (float a = arcStartAngle; a < arcEndAngle; a += M_PI / 18) {
            float x = cos(a);
            float y = sin(a);
            jointVerts.push_back({arcOrigin.x + x * radius, arcOrigin.y - y * radius});
        }
    }
    else {
        for (float a = arcStartAngle; a > arcEndAngle; a -= M_PI / 18) {
            float x = cos(a);
            float y = sin(a);
            jointVerts.push_back({arcOrigin.x + x * radius, arcOrigin.y - y * radius});
        }
    }

    for (int i = 1; i < jointVerts.size(); i++) {
        vertices.push_back(arcOrigin);
        vertices.push_back(jointVerts.at(i - 1));
        vertices.push_back(jointVerts.at(i));
    }
    vertices.push_back(arcOrigin);
    vertices.push_back(jointVerts.back());
    vertices.push_back(centerBorderB);

    return vertices;
}

std::vector<Point2D> triangulateCap(const Point2D& beginSegment,
                                    const Point2D& endSegment,
                                    const AnchorMetrics& anchorMetrics,
                                    const Point2D& segmentCornerA,
                                    const Point2D& segmentCornerB) {
    if (anchorMetrics.anchor.capType == CapType::SQUARE) {
        return triangulateSquareCap(beginSegment, endSegment, anchorMetrics, segmentCornerA, segmentCornerB);
    }
    else if (anchorMetrics.anchor.capType == CapType::ROUND) {
        // todo
    }
    return {};
}

std::vector<Point2D> triangulateSquareCap(const Point2D& beginSegment,
                                          const Point2D& endSegment,
                                          const AnchorMetrics& anchorMetrics,
                                          const Point2D& segmentCornerA,
                                          const Point2D& segmentCornerB) {
    Vector2D segmentAsVec = points2DtoVector2D(beginSegment, endSegment);
    segmentAsVec.normalize();
    segmentAsVec.scale(anchorMetrics.thickness / 2);
    Point2D capCornerA = segmentCornerA.translateCopy(segmentAsVec);
    Point2D capCornerB = segmentCornerB.translateCopy(segmentAsVec);
    return {capCornerA, capCornerB, segmentCornerA, segmentCornerA, segmentCornerB, capCornerB};
}

std::vector<Point2D> AnchorMetrics::findBorderCorners() const {
    Point2D vert1 = anchor.begin.translateCopy(beginToBorder);
    Point2D vert2 = anchor.begin.translateCopy(beginToBorder.reverseCopy());
    Point2D vert3 = anchor.end.translateCopy(endToBorder);
    Point2D vert4 = anchor.end.translateCopy(endToBorder.reverseCopy());
    return {vert1, vert2, vert3, vert4};
};

float signedArea(const Point2D& pointA, const Point2D& pointB, const Point2D& pointC) {
    return (pointB.x - pointA.x) * (pointC.y - pointA.y) - (pointC.x - pointA.x) * (pointB.y - pointA.y);
}