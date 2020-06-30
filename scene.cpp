//
// Created by Ryan McCauley on 27/06/2020.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "scene.h"

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec4 aColor;\n"
                                 "out vec4 ourColor;\n\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec4 ourColor;"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(ourColor);\n"
                                   "} ";

Scene::Scene(const char *windowTitle,
             unsigned int screenWidth,
             unsigned int screenHeight) :
        windowTitle(windowTitle), screenWidth(screenWidth),screenHeight(screenHeight) {}

void Scene::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // todo handle error
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initGlad();
    initShaders();
    initDefaultVAO();
}

void Scene::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // todo handle error
    }
}

void Scene::initShaders() {
    initVertShaders();
    initFragShaders();

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, defaultVertShader);
    glAttachShader(shaderProgram, defaultFragShader);
    glLinkProgram(shaderProgram);

    int shaderLinkSuccess;
    char shaderLinkInfoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderLinkSuccess);
    if(!shaderLinkSuccess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, shaderLinkInfoLog);
        std::cout << "Shader program linking failed: \n" << shaderLinkInfoLog << std::endl;
    }

    cleanupShaders();

    glUseProgram(shaderProgram);
}

void Scene::initVertShaders() {
    defaultVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(defaultVertShader, 1, &vertexShaderSource, NULL);
    glCompileShader(defaultVertShader);

    int vertSuccess;
    char vertInfoLog[512];
    glGetShaderiv(defaultVertShader, GL_COMPILE_STATUS, &vertSuccess);

    if(!vertSuccess)
    {
        glGetShaderInfoLog(defaultVertShader, 512, NULL, vertInfoLog);
        std::cout << "Vertex shader failed to compile: \n" << vertInfoLog << std::endl;
    }
}

void Scene::initFragShaders() {
    defaultFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(defaultFragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(defaultFragShader);

    int fragSuccess;
    char fragInfoLog[512];
    glGetShaderiv(defaultFragShader, GL_COMPILE_STATUS, &fragSuccess);

    if(!fragSuccess)
    {
        glGetShaderInfoLog(defaultFragShader, 512, NULL, fragInfoLog);
        std::cout << "Fragment shader failed to compile: \n" << fragInfoLog << std::endl;
    }
}

void Scene::render() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        bindVAO(1); // todo do dynamically

        for (auto const& vbo : VBOs) {
            bindVAO(vbo.first);
        }

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 1000000);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Scene::cleanupShaders() {
    glDeleteShader(defaultVertShader);
    glDeleteShader(defaultFragShader);
}

unsigned int Scene::generateVBO() {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    return VBO;
}

void Scene::bindVBO(unsigned int VBO, const std::vector<float> &vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    VBOs.insert(std::make_pair(VBO, vertices));
}

void Scene::initDefaultVAO() {
    glGenVertexArrays(1, &VAO);
}

unsigned int Scene::bindVAO(unsigned int vbo) {
    std::vector<float> vertices = VBOs[vbo];
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return VAO;
}

void Scene::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Scene::enableAlpha() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Scene::enableWireFrameMode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
