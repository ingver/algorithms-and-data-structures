CXX = g++ -std=c++1y
CFLAGS = -Wall -g

ALGO_DIR   = algorithms
SEARCH_DIR = algorithms/search
SORTS_DIR  = algorithms/sorts
BUBBLE_SORT_DIR = algorithms/sorts/bubble
INSERT_SORT_DIR = algorithms/sorts/insertion
SELECT_SORT_DIR = algorithms/sorts/selection



test_all: test_cpp


CPP_DIR = ./c++
CPP_SORTS = $(CPP_DIR)/$(BUBBLE_SORT_DIR)/bubble.cpp\
	        $(CPP_DIR)/$(INSERT_SORT_DIR)/insert.cpp\
	        $(CPP_DIR)/$(SELECT_SORT_DIR)/select.cpp


test_cpp: test_cpp_sorts

test_cpp_sorts: $(CPP_SORTS) $(CPP_DIR)/$(SORTS_DIR)/sorts.h
	@$(CXX) -o test_sorts ./tests/c++/test_sorts.cpp $(CPP_SORTS)
	@./test_sorts


clean:
	@rm ./test_sorts
