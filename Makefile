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
INCLUDES = -I$(GLAD_INC)
GLAD = ./glad
GLAD_INC = $(GLAD)/include

TARGET := create_window 
TARGET := $(addprefix $(BUILD)/, $(TARGET))
CPP_FILES := create_window.cpp 
OBJECTS := $(CPP_FILES:.cpp=.o) glad.o
OBJECTS := $(addprefix $(BUILD)/, $(OBJECTS))

# Recipes
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS) 
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile objects
$(BUILD)/glad.o: $(GLAD)/src/glad.c | $(BUILD)
	$(CC) -c $(CFLAGS) -o $@ $< 

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@    

.PHONY : clean run-test

clean :
	rm -rf $(BUILD)

run-test: $(TARGET)
	./$(TARGET)

$(BUILD):
	mkdir -p $(BUILD)