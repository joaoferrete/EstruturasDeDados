#João Paulo Souza Ferrete e Ramon Pezzin Ton

all: exe

exe: main.o avl.o
		gcc -o exe main.o avl.o

main.o: main.c avl.h
		gcc -c main.c -Wall

avl.o: avl.c avl.h
		gcc -c avl.c -Wall
	
clean:
		rm main.o avl.o exe