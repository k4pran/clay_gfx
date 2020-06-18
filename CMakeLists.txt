cmake_minimum_required(VERSION 3.15)
project(opengl_tutorial)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        opengl_tutorial
        main.cpp
        ext/glad/src/glad.c
        shader.h shader.cpp point.cpp point.h vector.h line.h vector.cpp anchor.h anchor.cpp line.cpp polyline.h polyline.cpp float_approximator.h float_approximator.cpp drawable.h triangle.h triangle.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(/usr/local/include)
include_directories(ext/glad/include)

target_link_libraries(opengl_tutorial ${GLFW_LIBRARIES})

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")