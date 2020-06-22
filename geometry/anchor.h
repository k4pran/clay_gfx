//
// Created by Ryan McCauley on 25/05/2020.
//

#ifndef OPENGL_TUTORIAL_ANCHOR_H
#define OPENGL_TUTORIAL_ANCHOR_H

#include "point.h"
#include "vector.h"

enum class CapType {
    BUTT,
    ROUND,
    SQUARE
};

enum class JointType {
    MITER,
    BEVEL,
    ROUND
};

enum class SegmentPosition {
    START,
    MIDDLE,
    END,
    COMPLETE
};

struct Anchor {
    Point2D begin, center, end;
    CapType capType;
    JointType jointType;
    SegmentPosition segmentPosition;

    static std::vector<Anchor> createAnchors(std::vector<Point2D> points,
                                             const JointType& jointType,
                                             const CapType& capType);
};

struct AnchorMetrics {
    Anchor anchor;
    float thickness;
    Vector2D beginToBorder;
    Vector2D endToBorder;

    AnchorMetrics(Anchor anchor, float thickness);

    std::vector<Point2D> triangulateMiterJoint() const;

    std::vector<Point2D> triangulateBevelJoint() const;

    std::vector<Point2D> triangulateRoundJoint() const;

    std::vector<Point2D> triangulateLineRects() const;

    std::vector<Point2D> triangulateStraight() const;

    std::vector<Point2D> triangulateAnchored() const;

    std::vector<Point2D> triangulate() const;

    std::vector<Point2D> findBorderCorners() const;
};

std::vector<Point2D> triangulateCap(const Point2D& beginSegment,
                                    const Point2D& endSegment,
                                    const AnchorMetrics& anchorMetrics,
                                    const Point2D& segmentCornerA,
                                    const Point2D& segmentCornerB);

std::vector<Point2D> triangulateSquareCap(const Point2D& beginSegment,
                                          const Point2D& endSegment,
                                          const AnchorMetrics& anchorMetrics,
                                          const Point2D& segmentCornerA,
                                          const Point2D& segmentCornerB);

float signedArea(const Point2D& pointA, const Point2D& pointB, const Point2D& pointC);

#endif //OPENGL_TUTORIAL_ANCHOR_H
