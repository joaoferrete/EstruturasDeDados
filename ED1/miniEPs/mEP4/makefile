EXECUTAVEL=mEP4

CC     = gcc
CFLAGS = -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -g -fno-inline -fno-omit-frame-pointer
GLLIB = -lm -lGL -lGLU -lglut

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o mEP4.o 
	@$(CC) main.o mEP4.o $(GLLIB) -o $(EXECUTAVEL) $(CFLAGS)

main.o: main.c Lista.h
	@$(CC) $(CFLAGS) -c main.c -o main.o

mEP4.o: mEP4.c Lista.h
	@$(CC) $(CFLAGS) -c mEP4.c -o mEP4.o
