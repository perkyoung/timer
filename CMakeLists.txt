cmake_minimum_required(VERSION 3.3)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp src/interval_timer.cpp src/timeval.cpp)
add_executable(test_1 ${SOURCE_FILES})