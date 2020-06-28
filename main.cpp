#include <GLFW/glfw3.h>
#include <vector>
#include <yaml-cpp/yaml.h>
#include "geometry/vector.h"
#include "geometry/point.h"
#include "geometry/anchor.h"
#include "drawable/primitive/polyline.h"
#include "drawable/simple/triangle.h"
#include "drawable/simple/rect.h"
#include "scene.h"

int main()
{
    YAML::Node config = YAML::LoadFile("../config.yaml");
    YAML::Node windowConfig = config["window"];

    const std::string title = windowConfig["title"].as<std::string>();
    const int width = windowConfig["width"].as<int>();
    const int height = windowConfig["height"].as<int>();

    Scene scene = Scene(title.c_str(), width, height);
    scene.init();
    unsigned int rectVertId = scene.generateBuffer();

    Point2D p1 = {-0.15, -0.15};
    Point2D p2 = {-0.15, 0.15};
    Point2D p3 = {0.15, 0.15};
    Point2D p4 = {0.15, -0.15};

    Rect rect = Rect::make(p1, p2, p3, p4)
            .withThickness(0.03)
            .withJoint(JointType::MITER)
            .filled()
            .withFillColor({0, 0, 0, 1})
            .withStrokeColor({1, 0, 0, 1});

    std::vector<float> vertices = rect.asVertices();
    scene.bindBuffer(rectVertId, vertices);

    scene.bindArray(rectVertId, vertices);
    scene.render();

    return 0;
}