
EXECUTAVEL=EP1

CC     = gcc
CFLAGS = -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -g -fno-inline -fno-omit-frame-pointer
GLLIB = -lm -lGL -lGLU -lglut

all: $(EXECUTAVEL)

$(EXECUTAVEL): mainSemOpenGL.o Imagem.o  Filtros.o
	@echo Criando arquivo executável: $@
	@$(CC) mainSemOpenGL.o Imagem.o Filtros.o $(GLLIB) -o $(EXECUTAVEL) 

mainSemOpenGL.o: mainSemOpenGL.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c mainSemOpenGL.c

Imagem.o: Imagem.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c Imagem.c 

Filtros.o: Filtros.c
	@echo Compilando arquivo objeto: $@
	@$(CC) $(CFLAGS) -c Filtros.c 

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

memcheck: $(EXECUTAVEL) 
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) BritishUmbrellaColor.ppm

.PHONY: clean
clean:
	rm -f $(EXECUTAVEL) *.o