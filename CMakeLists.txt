cmake_minimum_required(VERSION 3.28.3)
project(C__1)

set(CMAKE_CXX_STANDARD 20)

add_executable(RunMain main.cpp
        Graph.cpp
        Graph.h
        Node_V.cpp
        Node_V.h
        Algorithms.cpp
        Algorithms.h
        Queue.cpp
        Queue.h
        PropertyQueue.cpp
        PropertyQueue.h
        Helpers.h
        UnionFind.cpp
        UnionFind.h
        EdgeList.cpp
        EdgeList.h
        tests/algorithms_test.cpp
        tests/node_v_test.cpp
        tests/unionFind_test.cpp
        tests/queue_test.cpp
        tests/propertyQueue_test.cpp
        tests/helpers_test.cpp
        tests/edgeList_test.cpp
        tests/memory_test.cpp
        #tests/graph_test.cpp

)
