Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(TEST_MODULES objects vector simulation hitbox)

set(CATCH_DEVELOPMENT_BUILD OFF CACHE BOOL "")
set(BUILD_TESTING OFF CACHE BOOL "")

foreach(module ${TEST_MODULES})
    set(test_exe run_test_${module})
    
    add_executable(${test_exe} ${module}_tests.cpp)
    
    target_link_libraries(${test_exe} PRIVATE SOSCore Catch2::Catch2WithMain)
    
    target_include_directories(${test_exe} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
    add_test(NAME ${module}_test COMMAND ${test_exe})
endforeach()