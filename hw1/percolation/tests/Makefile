# Makefile for unit testing

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I/usr/include/gtest -I$(PERCOLATION_DIR) -I$(DYNAMIC_CONNECTIVITY_DIR)

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main

# Paths
PERCOLATION_DIR = ../src
DYNAMIC_CONNECTIVITY_DIR = ../../dynamic_connectivity/src
TEST_DIR = .

# Source and test files
SRC = $(PERCOLATION_DIR)/percolation.c $(DYNAMIC_CONNECTIVITY_DIR)/dynamic_connectivity.c
TEST_SRC = $(TEST_DIR)/percolation_tests.cpp

# Target executable
TARGET = percolation_tests

# Build rule
all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET) *.o
