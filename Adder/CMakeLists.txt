cmake_minimum_required(VERSION 3.21)
project(Adder)

set(CMAKE_CXX_STANDARD 17)

add_executable(Adder main.cpp Number.cpp Number.hpp FileIO.cpp FileIO.hpp Adder.hpp Adder.cpp)
