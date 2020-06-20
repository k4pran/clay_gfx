cmake_minimum_required(VERSION 3.15)
project(opengl_tutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        opengl_tutorial
        main.cpp
        ext/glad/src/glad.c
        shader/shader.h shader/shader.cpp geometry/point.cpp geometry/point.h geometry/vector.h geometry/line-metrics.h geometry/vector.cpp geometry/anchor.h geometry/anchor.cpp geometry/line-metrics.cpp drawable/primitive/polyline.h drawable/primitive/polyline.cpp common/float_approximator.h common/float_approximator.cpp drawable/drawable.h drawable/triangle.h drawable/triangle.cpp geometry/tri-metrics.h geometry/tri-metrics.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(/usr/local/include)
include_directories(ext/glad/include)

target_link_libraries(opengl_tutorial ${GLFW_LIBRARIES})

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")