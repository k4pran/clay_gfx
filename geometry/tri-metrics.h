//
// Created by Ryan McCauley on 20/06/2020.
//

#include "point.h"
#include "../drawable/simple/triangle.h"

#ifndef OPENGL_TUTORIAL_TRI_METRICS_H
#define OPENGL_TUTORIAL_TRI_METRICS_H

Point2D findCentroid(const Point2D& pointA, const Point2D& pointB, const Point2D& pointC);
Point2D findInCenter(const Point2D& pointA, const Point2D& pointB, const Point2D& pointC);


#endif //OPENGL_TUTORIAL_TRI_METRICS_H