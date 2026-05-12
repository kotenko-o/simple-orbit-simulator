add_library(test_framework STATIC test_framework.c)
target_include_directories(test_framework PUBLIC .)

set(TEST_MODULES objects vector simulation hitbox)

foreach(module ${TEST_MODULES})
    set(test_exe run_test_${module})
    
    add_executable(${test_exe} ${module}_tests.cpp)
    
    target_link_libraries(${test_exe} PRIVATE SOSCore test_framework)
    
    target_include_directories(${test_exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
    add_test(NAME ${module}_test COMMAND ${test_exe})
endforeach()