CC=gcc
CFLAGS=-lm

BIN=bin
SRC=src

TARGET=$(BIN)/car_rental_sim
EXAMPLE=$(BIN)/single_server_queue_sim
UTILS=$(shell find src/utils -name '*.c')

all: $(TARGET) run

run: $(TARGET)
	@./$(TARGET)

example: $(EXAMPLE)
	@./$(EXAMPLE)

clean:
	rm -rf $(BIN)
	@mkdir -p $(BIN)

$(TARGET): $(SRC)/main.c $(SRC)/simlib.c $(UTILS)
	@$(CC) $^ $(CFLAGS) -o $@

$(EXAMPLE): $(SRC)/example.c $(SRC)/simlib.c
	@$(CC) $^ $(CFLAGS) -o $@

.PHONY: all run