cmake_minimum_required(VERSION 3.3)
project(timer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp src/timer.cpp src/timeval.cpp)
add_executable(timer ${SOURCE_FILES})