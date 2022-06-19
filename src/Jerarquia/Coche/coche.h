#include "../../BD/sqlite3.h"

#ifndef COCHE_H_
#define COCHE_H_

typedef struct {
	char marca[15];
	char modelo[15];
	int automatico;
	int plazas;
	int anyoFabricacion;
} Coche;

void imprimirCoche(Coche coche);

#endif /* COCHE_H_ */
