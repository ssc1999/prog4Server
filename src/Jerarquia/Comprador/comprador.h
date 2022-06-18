//#include "../../BD/sqlite3.h"

#ifndef COMPRADOR_H_
#define COMPRADOR_H_

typedef struct {
	char nombre[25]; // hay que poner aquí el id???
	char dni[9];
	char email[25];
	char cuentaBancaria[20];
} Comprador;

//void anadirBiblioteca(sqlite3 *db, int result, Biblioteca biblioteca);
//void imprimirBibliotecas(sqlite3 *db, Biblioteca biblioteca);
//void eliminarBibliotecas(sqlite3 *db, int result, char cod[100]);
//void eliminarTodasBibliotecas(sqlite3 *db, int result);

#endif /* COMPRADOR_H_ */
