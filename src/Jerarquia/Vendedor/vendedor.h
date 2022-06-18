//#include "../../BD/sqlite3.h"

#ifndef VENDEDOR_H_
#define VENDEDOR_H_

typedef struct {
	char nombre[40]; // hay que poner aquí el id???
	char dni[40];
	char email[40];
	float sueldo;
	int numVentas;
} Vendedor;

//void anadirBiblioteca(sqlite3 *db, int result, Biblioteca biblioteca);
//void imprimirBibliotecas(sqlite3 *db, Biblioteca biblioteca);
//void eliminarBibliotecas(sqlite3 *db, int result, char cod[100]);
//void eliminarTodasBibliotecas(sqlite3 *db, int result);

#endif /* VENDEDOR_H_ */
