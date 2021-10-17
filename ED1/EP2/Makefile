CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LIBS=-lm
EXECUTAVEL=Sucuri

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Pilha.o Util.o Fila.o Objeto.o Lexer.o Categorias.o Posfixa.o Avalia.o
	gcc main.o Pilha.o Util.o Fila.o Objeto.o Lexer.o Categorias.o Posfixa.o Avalia.o $(LIBS) -o $(EXECUTAVEL)

main.o: main.c
	gcc $(CFLAGS) -c main.c

Pilha.o: Pilha.c
	gcc $(CFLAGS) -c Pilha.c

Fila.o: Fila.c
	gcc $(CFLAGS) -c Fila.c

Objeto.o: Objeto.c
	gcc $(CFLAGS) -c Objeto.c

Lexer.o: Lexer.c
	gcc $(CFLAGS) -c Lexer.c

Util.o: Util.c
	gcc $(CFLAGS) -c Util.c

Categorias.o: Categorias.c
	gcc $(CFLAGS) -c Categorias.c

Posfixa.o: Posfixa.c
	gcc $(CFLAGS) -c Posfixa.c

Avalia.o: Avalia.c
	gcc $(CFLAGS) -c Avalia.c

clean: 
	rm -rf *.o $(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) -e -s expressoes.txt
	
run: $(EXECUTAVEL) 
	./$(EXECUTAVEL) -e