# Compilateur utilisé
CC=gcc

# Options du compilateur
CFLAGS=-Wall -std=c11

# Listes des dépendances et des fichiers objets
DEPS=hdr/pc_jeu.h hdr/pc_utils.h
OBJS=obj/petitschevaux.o obj/pc_jeu.o obj/pc_utils.o

# Nom de l'exécutable
EXEC=petitschevaux

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

petitschevaux: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OBJS)

mrproper: clean
	rm -f $(EXEC)