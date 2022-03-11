cmake_minimum_required(VERSION 3.21)
project(Image)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(Test/lib)
add_executable(Image main.cpp Image.cpp Image.hpp Range.cpp Range.hpp)
