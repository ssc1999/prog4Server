#include "../../BD/sqlite3.h"

#ifndef COMPRADOR_H_
#define COMPRADOR_H_

typedef struct {
	char nombre[25];
	char dni[9];
	char email[25];
	char cuentaBancaria[20];
} Comprador;

void imprimirComprador(Comprador comprador);

#endif /* COMPRADOR_H_ */
