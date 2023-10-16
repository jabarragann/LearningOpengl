# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -O2 $(INCLUDES)
# CFLAGS = -Wall -ggdb -O3 $(INCLUDES)
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic $(INCLUDES)
# CXXFLAGS = -Wall -ggdb -O3 $(INCLUDES)
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# Directories
SRC = src
BUILD = build
INCLUDES = -I$(GLAD_INC) -I./include
GLAD = ./glad
GLAD_INC = $(GLAD)/include

TARGETS := create_window create_triangle 
TARGETS := $(addprefix $(BUILD)/, $(TARGETS))
CPP_EXEC := create_window.cpp create_triangle.cpp
CPP_FILES := Shader.cpp 
OBJECTS := $(CPP_FILES:.cpp=.o) glad.o
OBJECTS := $(addprefix $(BUILD)/, $(OBJECTS))

# Recipes
all: $(TARGETS)
$(BUILD)/create_window: $(BUILD)/create_window.o $(OBJECTS) 
$(BUILD)/create_triangle: $(BUILD)/create_triangle.o $(OBJECTS) 

# Link
$(TARGETS): $(OBJECTS) 
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile objects
$(BUILD)/glad.o: $(GLAD)/src/glad.c | $(BUILD)
	$(CC) -c $(CFLAGS) -o $@ $< 

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@    

$(BUILD)/%.o: $(SRC)/%.cpp $(INCLUDES) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@    

.PHONY : all clean run-test

clean :
	rm -rf $(BUILD)

run-test: $(TARGETS)
	./$(BUILD)/create_triangle

$(BUILD):
	mkdir -p $(BUILD)