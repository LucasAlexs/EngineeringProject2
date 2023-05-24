#makefile

all: teste doc


aplicacao: teste doc
	gcc -o aplicacao teste doc

teste: aplicacao

teste: main.o matrizes.o
	gcc -o teste main.o matrizes.o

main.o: main.c matrizes/matrizes.c
	gcc -o main.o main.c

matrizes.o: matrizes.c matrizes.h
	gcc -o matrizes.o matrizes.c


