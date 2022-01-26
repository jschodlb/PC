CC = gcc
CFLAGS = -Wall -pedantic -ansi
BIN = ccl.exe
OBJ = error.o linked_list.o colour_linked_list.o main.o ccl.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@

