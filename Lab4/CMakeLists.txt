cmake_minimum_required(VERSION 3.30)
project(Lab4act)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lab4act Main.cpp
        CError.cpp
        CError.h
        Constants.h
        CResult.h
        CResultSaver.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.cpp
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CNode.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CNode.cpp
        CTests.cpp
        CTests.h
        Constants.cpp)
