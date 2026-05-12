add_library(test_framework STATIC 
    test_framework.c
)
target_include_directories(test_framework PUBLIC .)

set(TEST_MODULES objects vector simulation hitbox)

foreach(module ${TEST_MODULES})
    set(test_name run_test_${module})
    
    add_executable(${test_name} ${module}_tests.cpp)
    
    target_link_libraries(${test_name} PRIVATE engine_lib test_framework)
    
    add_test(NAME ${module}_test COMMAND ${test_name})
endforeach()