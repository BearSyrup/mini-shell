TARGET = ./bin/mini-shell
CC := gcc
CFLAGS := -g -Wall

.PHONY: run all

# Directories
SRC_DIR := src
OUT_DIR := out

# get all files in src/
SRCS := $(wildcard $(SRC_DIR)/*.c)

# convert each .c file into .o 
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

all: $(TARGET)

# all objects to executable
$(TARGET): $(OBJS)
	@echo "Linking $@ ..."
	$(CC) $(CFLAGS) $^ -o $@

#each .c to .o
$(OUT_DIR)/%.o:$(SRC_DIR)/%.c
	@echo "Compiling $<"	
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "cleaning bin"
	rm -rf ./bin/*
	rm -rf ./out/*.o
