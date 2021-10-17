CFLAGS=-O0 -g -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LIBS=-lm
EXECUTAVEL=mEP5

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Lista.o Objetos.o Util.o mEP5.o
	gcc main.o Lista.o Objetos.o Util.o mEP5.o $(LIBS) -o $(EXECUTAVEL)

main.o: main.c
	gcc $(CFLAGS) -c main.c

Lista.o: Lista.c
	gcc $(CFLAGS) -c Lista.c

Objetos.o: Objetos.c
	gcc $(CFLAGS) -c Objetos.c

Util.o: Util.c
	gcc $(CFLAGS) -c Util.c

mEP5.o: mEP5.c
	gcc $(CFLAGS) -c mEP5.c

clean: 
	rm -rf *.o $(EXECUTAVEL)

run: $(EXECUTAVEL) 
	./$(EXECUTAVEL) < entrada.txt

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) < entrada.txt
	
