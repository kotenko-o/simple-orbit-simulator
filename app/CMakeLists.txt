add_executable(simulation 
    src/app.cpp
)

target_link_libraries(simulation
    PRIVATE engine_lib
)