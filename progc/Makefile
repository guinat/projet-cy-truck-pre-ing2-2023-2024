# Compiler and compiler flags
CC = gcc
CFLAGS = -Isrc/include
LDFLAGS = -lm

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/_exec

# Default target: build the executable
all: $(TARGET)

# Rule to build the executable from object files
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Declare 'all' and 'clean' as phony targets (no real files associated)
.PHONY: all clean
