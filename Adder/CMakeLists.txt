cmake_minimum_required(VERSION 3.21)
project(Adder)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test/lib)
add_executable(Adder main.cpp Number.cpp Number.hpp StreamIO.cpp StreamIO.hpp)
