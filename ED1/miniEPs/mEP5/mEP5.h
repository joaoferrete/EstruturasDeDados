#ifndef __AVALIA_H_
#define __AVALIA_H_

#include "Lista.h"
#include "Objetos.h"
#include "Util.h"

bool expressaoValida(Lista *);

Objeto *avaliaExpressao(Lista *);

#endif