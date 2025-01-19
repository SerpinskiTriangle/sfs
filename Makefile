# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Directories
SRC_DIRS = $(wildcard src/*)
INCLUDE_DIR = include
OBJ_DIR = obj

# Find all source files and corresponding object files
SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target: show usage
.PHONY: all
all:
	@echo "Usage: make <source_filename>.out"
	@echo "Example: make myfile.out"

# Pattern rule to compile any .c file to its corresponding .out file
%.out: src/%.c $(OBJ_DIR)/%.o
	$(CC) $(CFLAGS) -o $@ $<

# Pattern rule to compile a .c file to an object file
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) *.out
