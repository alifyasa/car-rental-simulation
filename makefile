# Makefile for compiling simlib C++ program

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Linker flags
LDFLAGS = -lsimlib

# Source, Object, and Binary directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Targets
MAIN_TARGET = $(BIN_DIR)/sim_program
TEST_TARGET = $(BIN_DIR)/test_program

# Main Source and Object files
MAIN_SOURCES = $(wildcard $(SRC_DIR)/main.cpp)
MAIN_OBJECTS = $(MAIN_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test Source and Object files
TEST_SOURCES = $(wildcard $(SRC_DIR)/test.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(MAIN_TARGET)

# Main program target
$(MAIN_TARGET): $(MAIN_OBJECTS) | $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) -o $@

# Test program target
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all test clean