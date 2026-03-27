# Makefile for unit testing

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I/usr/include/gtest -I$(SRC_DIR)

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main

# Paths
SRC_DIR = ../src
TEST_DIR = .

# Source and test files
SRC = $(SRC_DIR)/dynamic_connectivity.c
TEST_SRC = $(TEST_DIR)/dynamic_connectivity_tests.cpp

# Target executable
TARGET = dynamic_connectivity_tests

# Build rule
all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET) *.o
