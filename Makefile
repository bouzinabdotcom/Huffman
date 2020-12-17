CC = gcc
CCOPTS = -Wall

all: main

listes.o:	listes.c listes.h
	${CC} ${CCOPTS} -c listes.c

file.o:		file.c file.h
	${CC} ${CCOPTS} -c file.c


arbre.o:	arbre.c arbre.h
	${CC} ${CCOPTS} -c arbre.c

gestion_fichier.o:	gestion_fichier.c gestion_fichier.h
	${CC} ${CCOPTS} -c gestion_fichier.c

huffman.o:	huffman.c huffman.h
	${CC} ${CCOPTS} -c huffman.c

main.o:	main.c
	${CC} ${CCOPTS} -c main.c

main:	main.o arbre.o listes.o file.o gestion_fichier.o huffman.o
	${CC} ${CCOPTS} -o huff main.o arbre.o listes.o file.o gestion_fichier.o huffman.o
	make clean

clean:
	rm *.o 
