add_executable(simulation 
    src/app.cpp
)

target_include_directories(simulation PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(simulation
    PRIVATE SOSCore
)