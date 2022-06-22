#include "../../BD/sqlite3.h"

#ifndef VENDEDOR_H_
#define VENDEDOR_H_

typedef struct
{
	char usuario[20];
	char contrasenya[20];
	char nombre[25];
	char dni[9];
	char email[25];
	float sueldo;
	int numVentas;
	// tipo 2
} Vendedor;

void imprimirVendedor(Vendedor vendedor);

#endif /* VENDEDOR_H_ */
