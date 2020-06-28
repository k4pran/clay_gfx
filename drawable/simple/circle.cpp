//
// Created by Ryan McCauley on 28/06/2020.
//

#include <cmath>
#include "circle.h"

Circle::Circle(const Point2D &center, const float radius): center(center), radius(radius) {}

CircleBuilder Circle::make(const Point2D &center, const float radius) {
    return CircleBuilder(center, radius);
}

std::vector<float> Circle::asVertices() {

    float currentAngle = 0.;

    std::vector<Point2D> outerPoints;
    for (float increment = 0.; increment < 2 * M_PI; increment +=(2 * M_PI / 360)) {
        float x = cos(currentAngle + increment);
        float y = sin(currentAngle + increment);
        outerPoints.push_back({center.x + x * radius, center.y + y * radius});
    }

    std::vector<Point2D> innerPoints;
    for (float increment = 0.; increment < 2 * M_PI; increment +=(2 * M_PI / 360)) {
        float x = cos(currentAngle + increment);
        float y = sin(currentAngle + increment);
        innerPoints.push_back({center.x + x * (radius - thickness), center.y + y * (radius - thickness)});
    }

    std::vector<Point2D> triangulatedPoints;
    for (int i = 1; i < innerPoints.size(); i++) {
        triangulatedPoints.push_back(innerPoints[i - 1]);
        triangulatedPoints.push_back(outerPoints[i - 1]);
        triangulatedPoints.push_back(innerPoints[i]);

        triangulatedPoints.push_back(innerPoints[i]);
        triangulatedPoints.push_back(outerPoints[i]);
        triangulatedPoints.push_back(outerPoints[i - 1]);
    }

    std::vector<Point2D> filledPoints;
    if (filled) {
        for (int i = 1; i < outerPoints.size(); i++) {
            filledPoints.push_back(innerPoints[i]);
            filledPoints.push_back(innerPoints[i - 1]);
            filledPoints.push_back(center);
        }
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
        for (auto & filledPoint : filledPoints) {
            vertices.push_back(filledPoint.x);
            vertices.push_back(filledPoint.y);
            vertices.push_back(0);

            vertices.push_back(fillColor.red);
            vertices.push_back(fillColor.green);
            vertices.push_back(fillColor.blue);
            vertices.push_back(fillColor.alpha);
        }
    }

    return vertices;
}

void Circle::setFilled(bool filled) {
    Circle::filled = filled;
}

CircleBuilder &CircleBuilder::withThickness(const float &thickness) {
    circle.thickness = thickness;
    return *this;
}

CircleBuilder &CircleBuilder::withStrokeColor(RGBA rgba) {
    circle.strokeColor = rgba;
    return *this;
}

CircleBuilder &CircleBuilder::withFillColor(RGBA rgba) {
    circle.fillColor = rgba;
    return *this;
}

CircleBuilder &CircleBuilder::filled() {
    circle.filled = true;
    return *this;
}

CircleBuilder::CircleBuilder(const Point2D &center,
                             const float radius): circle(center, radius) {}
