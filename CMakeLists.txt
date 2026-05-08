cmake_minimum_required(VERSION 4.2.3)
project(simple-orbit-simulator
    DESCRIPTION "A simple, lightweight C++-based orbital mechanics simulator. It was developed as a training project in physics, mathematics, and object-oriented programming in C++."
    LANGUAGES C CXX
    HOMEPAGE_URL https://github.com/kotenko-o/simple-orbit-simulator
)

# 1. Lib mit Projekt-Modulen
add_library(engine_lib
    src/objects.cpp
    src/physics.cpp
    src/simple_vector.cpp
    src/simulation.cpp
)

# Verbinden von header-Dateien zum lib
target_include_directories(engine_lib
    PUBLIC include
)

# 2. Eigentliches (executable) Program
add_executable(simulation
    src/app.cpp
)

# Verbinden engine_lib zum executable Program
target_link_libraries(simulation
    engine_lib
)

# 3. Lib für test_framework
add_library(test_framework
    test/test_framework.c
)

# Muss ein Ordner sein, keine Datei!
target_include_directories(test_framework 
    PUBLIC test
)

# 4. Tests Executables
# (Assuming the files are named .cpp, not .c.cpp)
add_executable(run_test_objects test/objects_tests.cpp)
add_executable(run_test_vector test/vector_tests.cpp)

# CRITICAL: Link the tests to both the engine and the test framework!
target_link_libraries(run_test_objects engine_lib test_framework)
target_link_libraries(run_test_vector engine_lib test_framework)

# 5. CTest Registrierung
enable_testing()

add_test(NAME objects_test COMMAND run_test_objects)
add_test(NAME vector_test COMMAND run_test_vector)