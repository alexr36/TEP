cmake_minimum_required(VERSION 3.30)
project(Lab5)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab5 Main.cpp
        CMySmartPointer.h
        CRefCounter.cpp
        CRefCounter.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CTree.cpp
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CNode.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab3act/CNode.cpp
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab4act/CResultSaver.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab4act/Constants.cpp
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab4act/CError.cpp
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab4act/CError.h
        /Users/alexrogozinski/CLionProjects/TEP/Lab/Lab4act/CResult.h)
