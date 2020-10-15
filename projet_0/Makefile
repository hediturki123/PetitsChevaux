# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -std=c11

# Listes des dépendances et des fichiers objets
DEPS=headers/pc_jeu.h
OBJS=obj/main.o obj/pc_jeu.o

# Nom de l'exécutable
EXEC=main

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OBJS)

mrproper: clean
	rm -f $(EXEC)