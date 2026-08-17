cmake_minimum_required(VERSION 3.14)
project(ccalculator_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt MOC processing automatically
set(CMAKE_AUTOMOC ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Main executable (Qt GUI calculator app)
add_executable(ccalculator
    src/main.cpp
    src/math_utils.cpp
    src/calculator_window.cpp
    include/calculator_window.h
)
target_include_directories(ccalculator PRIVATE include)
target_link_libraries(ccalculator PRIVATE Qt5::Widgets)

# Tests
enable_testing()
add_executable(ccalculator_tests tests/test_main.cpp src/math_utils.cpp)
target_include_directories(ccalculator_tests PRIVATE include)
add_test(NAME ccalculator_tests COMMAND ccalculator_tests)
