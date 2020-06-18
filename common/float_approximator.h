//
// Created by Ryan McCauley on 14/06/2020.
//

#ifndef OPENGL_TUTORIAL_FLOAT_APPROXIMATOR_H
#define OPENGL_TUTORIAL_FLOAT_APPROXIMATOR_H

bool approximatelyEqual(float a, float b, float epsilon);

bool essentiallyEqual(float a, float b, float epsilon);

bool definitelyGreaterThan(float a, float b, float epsilon);

bool definitelyLessThan(float a, float b, float epsilon);

#endif //OPENGL_TUTORIAL_FLOAT_APPROXIMATOR_H
