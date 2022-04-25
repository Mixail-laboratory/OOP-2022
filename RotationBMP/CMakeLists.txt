cmake_minimum_required(VERSION 3.21)
project(RotationBMP)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test/lib)

add_executable(RotationBMP main.cpp BitmapPlusPlus.hpp ImageModificator.cpp ImageModificator.hpp
        )
