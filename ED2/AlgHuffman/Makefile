all: exe

exe: main.o huffman.o
		gcc -g -o exe main.o huffman.o

main.o: main.c huffman.h
		gcc -g -c main.c -Wall

huffman.o: huffman.c huffman.h
		gcc -g -c huffman.c -Wall
	
clean:
		rm main.o huffman.o exe