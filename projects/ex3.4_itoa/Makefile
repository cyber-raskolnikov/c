# Define variables for the source file and build directory
SRC = ex3.4_itoa.c
BUILD_DIR = exe
EXEC = $(BUILD_DIR)/$(basename $(notdir $(SRC)))

# Compiler and compiler flags
CC = clang
CFLAGS = -Wall -Wextra -std=c11

# Default target: compile the program
all: $(BUILD_DIR) $(EXEC)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile the source file into an executable
$(EXEC): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run the executable
run: 
	@echo running $(EXEC)
	./$(EXEC)

# Declare phony targets
.PHONY: all clean run
