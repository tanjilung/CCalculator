cmake_minimum_required(VERSION 3.14)
project(ctest_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(ctest src/main.cpp src/math_utils.cpp)
target_include_directories(ctest PRIVATE include)

# Tests
enable_testing()
add_executable(ctest_tests tests/test_main.cpp src/math_utils.cpp)
target_include_directories(ctest_tests PRIVATE include)
add_test(NAME ctest_tests COMMAND ctest_tests)
