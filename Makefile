CXX = g++ -std=c++1y
CFLAGS = -Wall -g

ALGO_DIR   = algorithms
SEARCH_DIR = algorithms/search
SORTS_DIR  = algorithms/sorts
BUBBLE_SORT_DIR = $(SORTS_DIR)/bubble
INSERT_SORT_DIR = $(SORTS_DIR)/insertion
SELECT_SORT_DIR = $(SORTS_DIR)/selection



test_all: test_cpp


CPP_DIR = ./c++


test_cpp: test_cpp_sorts

test_cpp_sorts: $(CPP_DIR)/$(SORTS_DIR)/sorts.h
	@$(CXX) $(CFLAGS) -o test_sorts ./tests/c++/test_sorts.cpp
	@./test_sorts


clean:
	@rm ./test_sorts
