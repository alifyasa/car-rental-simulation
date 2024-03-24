CC=gcc
CFLAGS=-lm
BIN=bin
SRC=src
TARGET=$(BIN)/car_rental_simulation

all: $(TARGET) run

$(TARGET): $(SRC)/main.c $(SRC)/simlib.c
	@$(CC) $^ $(CFLAGS) -o $@

run: $(TARGET)
	@./$(TARGET)

.PHONY: all run