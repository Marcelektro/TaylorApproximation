CFLAGS = -Wall

# compiler
CC = gcc

# project structure
SRC_DIR = ./src
BUILD_DIR = ./build

# ensure build directory exists
$(shell mkdir -p $(BUILD_DIR))

# output artifact
TARGET = main

all: $(TARGET)

$(TARGET): $(BUILD_DIR)/main.o
	$(CC) -o $(TARGET) $(BUILD_DIR)/main.o -lm

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(BUILD_DIR)/*.o

run: $(TARGET)
	./$(TARGET)


.PHONY: all clean run
