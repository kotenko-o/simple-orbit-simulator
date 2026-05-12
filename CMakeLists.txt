cmake_minimum_required(VERSION 3.28.3)
project(simple-orbit-simulator
    DESCRIPTION "A simple, lightweight C++-based orbital mechanics simulator. It was developed as a training project in physics, mathematics, and object-oriented programming in C++."
    LANGUAGES C CXX
    HOMEPAGE_URL https://github.com/kotenko-o/simple-orbit-simulator
)

add_subdirectory(core)
add_subdirectory(app)

enable_testing()
add_subdirectory(test)