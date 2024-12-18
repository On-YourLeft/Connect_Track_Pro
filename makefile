# Compiler and Flags
CC = gcc
CFLAGS = -Wall -std=c99 -g -MMD -MP

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)
EXEC = $(BUILD_DIR)/connect_track_pro

# Default target
all: $(EXEC)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Rule to build the executable
$(EXEC): $(BUILD_DIR) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

# Rule to compile .c files into .o files (with dependency generation)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files for incremental builds
-include $(DEP_FILES)

# Clean up generated files
clean:
ifeq ($(OS),Windows_NT)
	del /S /Q $(BUILD_DIR)\* 2>nul && rmdir /S /Q $(BUILD_DIR) 2>nul || exit 0
else
	rm -rf $(BUILD_DIR)
endif

# Run the program
run: $(EXEC)
	./$(EXEC)

# Rebuild everything
rebuild: clean all