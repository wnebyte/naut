cmake_minimum_required(VERSION 3.24)
project(Naut)

set(CMAKE_CXX_STANDARD 11)

# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message("Error: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

# sets the include directory path
set(INCLUDE_DIRECTORY src/include)

set(SOURCES
        ${INCLUDE_DIRECTORY}/core/windowfwd.h
        ${INCLUDE_DIRECTORY}/core/window.h
        ${INCLUDE_DIRECTORY}/core/camerafwd.h
        ${INCLUDE_DIRECTORY}/core/camera.h
        ${INCLUDE_DIRECTORY}/core/orthocamerafwd.h
        ${INCLUDE_DIRECTORY}/core/orthocamera.h
        ${INCLUDE_DIRECTORY}/core/perspectivecamerafwd.h
        ${INCLUDE_DIRECTORY}/core/perspectivecamera.h
        src/cpp/core/window.cpp
        src/cpp/core/camera.cpp
        src/cpp/core/orthocamera.cpp
        src/cpp/core/perspectivecamera.cpp
        src/cpp/main.cpp
        src/c/glad.c)

add_executable(Naut ${SOURCES})

target_link_libraries(Naut glfw3 ${GL_LIBRARY} m)

target_include_directories(Naut PRIVATE ${INCLUDE_DIRECTORY})

add_compile_definitions(CPP_VERSION=${CMAKE_CXX_STANDARD})
