CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -g

SRC = Graph.cpp Algorithms.cpp Node_V.cpp PropertyQueue.cpp Queue.cpp UnionFind.cpp EdgeList.cpp

TEST = tests/edgeList_test.cpp tests/helpers_test.cpp tests/node_v_test.cpp tests/propertyQueue_test.cpp tests/queue_test.cpp tests/unionFind_test.cpp tests/algorithms_test.cpp

INCLUDES = -Items

TARGET = run_test

.PHONY: all clean run valgrind

all: $(TARGET)

$(TARGET): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(TARGET) $(INCLUDES)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)
