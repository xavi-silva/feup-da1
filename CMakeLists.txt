cmake_minimum_required(VERSION 3.27)
project(Proj)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proj main.cpp
        data_structures/Graph.h
        data_structures/MutablePriorityQueue.h
        data_structures/UFDS.cpp
        data_structures/UFDS.h
        menu.cpp)
