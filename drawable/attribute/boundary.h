//
// Created by Ryan McCauley on 01/07/2020.
//

#ifndef OPENGL_TUTORIAL_BOUNDARY_H
#define OPENGL_TUTORIAL_BOUNDARY_H

#include "../../geometry/point-geo.h"

struct Boundary {
    Point2D topLeft;
    Point2D topRight;
    Point2D bottomLeft;
    Point2D bottomRight;
};

#endif //OPENGL_TUTORIAL_BOUNDARY_H
