//
// Created by Ryan McCauley on 27/06/2020.
//

#ifndef OPENGL_TUTORIAL_SCENE_H
#define OPENGL_TUTORIAL_SCENE_H

#include <string>
#include <map>

class Scene {

    GLFWwindow* window;
    const char *windowTitle;
    unsigned int screenWidth;
    unsigned int screenHeight;

    unsigned int shaderProgram;
    unsigned int defaultVertShader;
    unsigned int defaultFragShader;

    std::map<unsigned int, std::vector<float>> VBOs;
    unsigned int VAO;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    void initVertShaders();
    void initFragShaders();
    void cleanupShaders();
    void initGlad();
    void initShaders();
    void initDefaultVAO();

public:
    Scene(const char *windowTitle, unsigned int screenWidth, unsigned int screenHeight);

public:
    void init();

    unsigned int generateVBO();

    void bindVBO(unsigned int vbo, const std::vector<float> &vertices);

    unsigned int bindVAO(unsigned int vbo);

    void enableAlpha();

    void enableWireFrameMode();

    void render();
};

#endif //OPENGL_TUTORIAL_SCENE_H
