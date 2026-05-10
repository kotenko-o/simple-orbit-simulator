cmake_minimum_required(VERSION 3.28.3)
project(simple-orbit-simulator
    DESCRIPTION "A simple, lightweight C++-based orbital mechanics simulator. It was developed as a training project in physics, mathematics, and object-oriented programming in C++."
    LANGUAGES C CXX
    HOMEPAGE_URL https://github.com/kotenko-o/simple-orbit-simulator
)

add_library(engine_lib
    src/objects.cpp
    src/physics.cpp
    src/simple_vector.cpp
    src/simulation.cpp
    src/hitbox.cpp
)

target_include_directories(engine_lib
    PUBLIC include
)

add_executable(simulation
    src/app.cpp
)

target_link_libraries(simulation
    engine_lib
)

add_library(test_framework
    test/test_framework.c
)

target_include_directories(test_framework 
    PUBLIC test
)

# Tests Executables
add_executable(run_test_objects test/objects_tests.cpp)
add_executable(run_test_vector test/vector_tests.cpp)
add_executable(run_test_simulation test/simulation_tests.cpp)
add_executable(run_test_hitbox test/hitbox_tests.cpp)

# Link the tests to both the engine and the test framework!
target_link_libraries(run_test_objects engine_lib test_framework)
target_link_libraries(run_test_vector engine_lib test_framework)
target_link_libraries(run_test_simulation engine_lib test_framework)
target_link_libraries(run_test_simulation engine_lib test_framework)
target_link_libraries(run_test_hitbox engine_lib test_framework)

# CTest
enable_testing()

add_test(NAME objects_test COMMAND run_test_objects)
add_test(NAME vector_test COMMAND run_test_vector)
add_test(NAME simulation_test COMMAND run_test_simulation)
add_test(NAME hitbox_test COMMAND run_test_hitbox)