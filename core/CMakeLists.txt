add_library(SOSCore STATIC
    src/physics.cpp
    src/hitbox.cpp
    src/objects.cpp
    src/simple_vector.cpp
    src/simulation.cpp
)

target_include_directories(SOSCore
    PUBLIC include
)   