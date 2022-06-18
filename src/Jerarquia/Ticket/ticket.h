//#include "../../BD/sqlite3.h"

#ifndef TICKET_H_
#define TICKET_H_

typedef struct {
	int idTicket; // hay que poner aquí el id???
	char nomComprador[25];
	char nomCoche[40]; // marca modelo
	char fechaCompra[10];
} Ticket;

//void anadirBiblioteca(sqlite3 *db, int result, Biblioteca biblioteca);
//void imprimirBibliotecas(sqlite3 *db, Biblioteca biblioteca);
//void eliminarBibliotecas(sqlite3 *db, int result, char cod[100]);
//void eliminarTodasBibliotecas(sqlite3 *db, int result);

#endif /* TICKET_H_ */
