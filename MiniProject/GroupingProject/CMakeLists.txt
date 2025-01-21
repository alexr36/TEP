cmake_minimum_required(VERSION 3.30)
project(GroupingProject2)

set(CMAKE_CXX_STANDARD 26)

add_executable(GroupingProject2 GroupingChallenge.cpp
            GroupingEvaluator.cpp
            GroupingEvaluator.h
            GaussianGroupingEvaluatorFactory.cpp
            GaussianGroupingEvaluatorFactory.h
            Optimizer.cpp
            Optimizer.h
            Point.cpp
            Point.h
        CIndividual.cpp
        CIndividual.h
        CGeneticAlgorithm.cpp
        CGeneticAlgorithm.h
        Constants.h
)
