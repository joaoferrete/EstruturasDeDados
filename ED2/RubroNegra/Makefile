#João Paulo Souza Ferrete e Ramon Pezzin Ton

all: exe

exe: main.o rubro.o
		gcc -g -o exe main.o rubro.o

main.o: rubro.h
		gcc -g -c main.c -Wall

rubro.o: rubro.h
		gcc -g -c rubro.c -Wall
	
clean:
		rm *.o exe
