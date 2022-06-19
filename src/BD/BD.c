#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "BD.h"
#include "sqlite3.h"
#include "../Jerarquia/Coche/coche.h"
#include "../Jerarquia/Comprador/comprador.h"
#include "../Jerarquia/Ticket/ticket.h"
#include "../Jerarquia/Vendedor/vendedor.h"

Ticket* getTickets(sqlite3* db){
    sqlite3_stmt* stmt;
    Ticket* tickets = (Ticket*) malloc(15*sizeof(Ticket));

    char nomComprador[25];
	char nomCoche[40];
	char fechaCompra[10];
    int i = 0;
	char sql[] = "select nomComprador, nomCoche, fechaCompra from ticket";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	printf("//////////////////////\n");
	printf("//////////////////////\n");
	printf("Tickets:\n");
    // recorres todas las filas de stmt(lo que te devuelve la bd despues de mandarle la sentencia)
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(tickets[i].nomComprador, (char *) sqlite3_column_text(stmt, 1));
            strcpy(tickets[i].nomCoche, (char *) sqlite3_column_text(stmt, 2));
            strcpy(tickets[i].fechaCompra, (char *) sqlite3_column_text(stmt, 3));
            i++;
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return tickets;
}


Coche* getCoches(sqlite3* db);
Comprador* getCompradores(sqlite3* db);
Vendedor* getVendedores(sqlite3* db);

int updateCoche(sqlite3* db, char marca[15], char modelo[15], int automatico, int plazas, int anyoFabricacion);

int insertTicket(sqlite3* db, char nomComprador[25], char nomCoche[40], char fechaCompra[10]);

int deleteTickets(sqlite3* db, char nomComprador[25]);

int imprimirTickets(sqlite3* db, char nomComprador[25]);
