cmake_minimum_required(VERSION 3.29)
project(Lab3act)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lab3act Main.cpp
        CTree.cpp
        CTree.h
        CNode.cpp
        CNode.h
        Constants.h
        CMenu.cpp
        CMenu.h)
