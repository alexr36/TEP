cmake_minimum_required(VERSION 3.29)
project(Lab2)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lab2 cmake-build-debug/main.cpp
        cmake-build-debug/CNumber.h
        cmake-build-debug/CNumber.cpp
        cmake-build-debug/constants.h
        cmake-build-debug/constants.cpp)
