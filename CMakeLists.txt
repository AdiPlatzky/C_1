cmake_minimum_required(VERSION 3.30)
project(C__1)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__1 main.cpp
        Graph.cpp
        Graph.h
        Node_V.cpp
        Node_V.h
        Algorithms.cpp
        Algorithms.h
        Queue.cpp
        Queue.h
        PriorityQueue.cpp
        PriorityQueue.h
        Helpers.h
        UnionFind.cpp
        UnionFind.h
        EdgeList.cpp
        EdgeList.h
)
