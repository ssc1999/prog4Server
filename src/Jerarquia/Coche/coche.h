#include "../../BD/sqlite3.h"

#ifndef COCHE_H_
#define COCHE_H_

typedef struct {
	char matricula[7];
	char marca[20];
	char modelo[20];
	int automatico;
	int plazas;
	int anyoFabricacion;
	int precio;
} Coche;

void imprimirCoche(Coche* coche);
void copiarCoches(Coche** cocheOrigen, Coche** cocheDestino);
Coche* getCoche(sqlite3 *db, char usuario[20]);

#endif /* COCHE_H_ */
