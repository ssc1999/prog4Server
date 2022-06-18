//#include "../../BD/sqlite3.h"

#ifndef COCHE_H_
#define COCHE_H_

typedef struct {
	int idBiblioteca; // hay que poner aquí el id???
	char marca[40];
	char modelo[40];
	boolean automatico;
	int plazas;
	int anyoFabricacion;
} Coche;

//void anadirBiblioteca(sqlite3 *db, int result, Biblioteca biblioteca);
//void imprimirBibliotecas(sqlite3 *db, Biblioteca biblioteca);
//void eliminarBibliotecas(sqlite3 *db, int result, char cod[100]);
//void eliminarTodasBibliotecas(sqlite3 *db, int result);

#endif /* COCHE_H_ */
