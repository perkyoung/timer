cmake_minimum_required(VERSION 3.3)
project(timer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES main.cpp timer.cpp timeval.cpp)
add_executable(timer ${SOURCE_FILES})