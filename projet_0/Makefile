CC=gcc
CFLAGS=-Wall
DEPS=headers/main.h
OBJ=obj/main.o
EXEC=main

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OBJ)

mrproper: clean
	rm -f $(EXEC)