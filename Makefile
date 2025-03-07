CFLAGS = -Wall

# compiler
CC = gcc

# project structure
SRC_DIR = ./src
BUILD_DIR = ./build

# ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# output artifact
TARGET_MAIN = main
TARGET_COMP = compare


# source/obj files
SRC_MAIN = $(SRC_DIR)/main.c
OBJ_MAIN = $(BUILD_DIR)/main.o

SRC_COMP = $(SRC_DIR)/compare.c
OBJ_COMP = $(BUILD_DIR)/compare.o

SRC_CALC = $(SRC_DIR)/approximation.c
OBJ_CALC = $(BUILD_DIR)/approximation.o


all: $(TARGET_MAIN) $(TARGET_COMP)

# build executables
$(TARGET_MAIN): $(OBJ_MAIN) $(OBJ_CALC)
	$(CC) -o $(TARGET_MAIN) $(OBJ_MAIN) $(OBJ_CALC) -lm

$(TARGET_COMP): $(OBJ_COMP) $(OBJ_CALC)
	$(CC) -o $(TARGET_COMP) $(OBJ_COMP) $(OBJ_CALC) -lm


# compile object files
$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_COMP): $(SRC_COMP)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CALC): $(SRC_CALC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET_MAIN) $(TARGET_COMP) $(BUILD_DIR)/*.o


.PHONY: all clean run
