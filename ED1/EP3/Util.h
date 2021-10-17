#ifndef EP3_UTIL_H
#define EP3_UTIL_H

#include <stdio.h>

#define ERRO(msg) fprintf(stderr, "ERRO: %s\n", #msg)
#define AVISO(msg) fprintf(stdout, "AVISO: %s\n", #msg)

typedef enum {
    false,
    true
} bool;

void *mallocSafe(size_t nbytes);

int min(int a, int b);

int min3(int a, int b, int c);

int distanciaEdicao(char *a, char *b);


#endif
