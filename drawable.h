//
// Created by Ryan McCauley on 16/06/2020.
//

#ifndef OPENGL_TUTORIAL_DRAWABLE_H
#define OPENGL_TUTORIAL_DRAWABLE_H

#include <vector>
#include "point.h"

class Entity {
public:
    virtual std::vector<Point2D> asVertices() = 0;
};

#endif //OPENGL_TUTORIAL_DRAWABLE_H
