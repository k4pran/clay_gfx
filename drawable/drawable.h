//
// Created by Ryan McCauley on 16/06/2020.
//

#ifndef OPENGL_TUTORIAL_DRAWABLE_H
#define OPENGL_TUTORIAL_DRAWABLE_H

#include <vector>
#include "../geometry/point.h"

class Drawable {
public:
    virtual std::vector<float> asVertices() = 0;
};

#endif //OPENGL_TUTORIAL_DRAWABLE_H
