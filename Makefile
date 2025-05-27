CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -g

SRC = Graph.cpp Algorithms.cpp Node_V.cpp PropertyQueue.cpp Queue.cpp UnionFind.cpp EdgeList.cpp

TEST = tests/memory_test.cpp tests/edgeList_test.cpp tests/helpers_test.cpp tests/node_v_test.cpp tests/propertyQueue_test.cpp tests/queue_test.cpp tests/unionFind_test.cpp tests/algorithms_test.cpp

INCLUDES = -I.

TARGET_MAIN = run_main
TARGET_TEST = run_test

.PHONY: all clean run-main run-test test main

all: $(TARGET_MAIN) $(TARGET_TEST)

$(TARGET_MAIN): $(SRC) main.cpp
	$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o $(TARGET_MAIN) $(INCLUDES)

$(TARGET_TEST): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(TARGET_TEST) $(INCLUDES)

run-main: $(TARGET_MAIN)
	./$(TARGET_MAIN)

run-test: $(TARGET_TEST)
	./$(TARGET_TEST)

test: run-test
main: run-main

valgrind: $(TARGET_TEST)
	valgrind --leak-check=full ./$(TARGET_TEST)

clean:
	rm -f $(TARGET_MAIN) $(TARGET_TEST)
