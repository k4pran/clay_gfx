//
// Created by Ryan McCauley on 06/06/2020.
//

#ifndef OPENGL_TUTORIAL_POLYLINE_H
#define OPENGL_TUTORIAL_POLYLINE_H

#include <vector>
#include <list>
#include "line.h"

struct Polyline {
    std::vector<Point2D> points;

    int nbLines() const;
};

#endif //OPENGL_TUTORIAL_POLYLINE_H
