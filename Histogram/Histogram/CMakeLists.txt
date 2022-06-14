cmake_minimum_required(VERSION 3.21)
project(Histogram)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test/lib)
add_executable(Histogram main.cpp Histogram.cpp Histogram.hpp)
