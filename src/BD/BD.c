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

// Ticket* getTickets(sqlite3* db){
//     sqlite3_stmt* stmt;
//     Ticket* tickets = (Ticket*) malloc(100 * sizeof(Ticket));

//     char nomComprador[25];
// 	char nomCoche[40];
// 	char fechaCompra[10];

//     int i = 0;
// 	char sql[] = "select nomComprador, nomCoche, fechaCompra from ticket";

// 	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
// 	if (result != SQLITE_OK) {
// 		printf("Error preparing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	printf("SQL query prepared (SELECT)\n");

// 	printf("//////////////////////\n");
// 	printf("//////////////////////\n");
// 	printf("Tickets:\n");

// 	do {
// 		result = sqlite3_step(stmt) ;
// 		if (result == SQLITE_ROW) {
// 			strcpy(tickets[i].nomComprador, (char *) sqlite3_column_text(stmt, 0));
//             strcpy(tickets[i].nomCoche, (char *) sqlite3_column_text(stmt, 1));
//             strcpy(tickets[i].fechaCompra, (char *) sqlite3_column_text(stmt, 2));
//             i++;
// 		}
// 	} while (result == SQLITE_ROW);

// 	printf("\n");
// 	printf("\n");

// 	result = sqlite3_finalize(stmt);
// 	if (result != SQLITE_OK) {
// 		printf("Error finalizing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	printf("Prepared statement finalized (SELECT)\n");

// 	return tickets;
// }

// Coche* getCoches(sqlite3* db){
// 	sqlite3_stmt* stmt; // statement para guardar lo que te devuelve la bd
// 	Coche* coches = (Ticket*) malloc(100 * sizeof(Coche)); // meter en este array de coches lo que hay en cada fila que me devuelve la bd

// 	// la bd te devuelve filas
// 	// dentro de cada fila, cada columna ser� un atributo
// 	// meteremos eso en los atributos que creo
// 	// despu�s con esos atributos crearemos una struct y despu�s esa struct la metemos en el array de structs
// 	char matricula[7];
// 	char marca[15];
// 	char modelo[15];
// 	int automatico;
// 	int plazas;
// 	int anyoFabricacion;

// 	// crear sentencia sql
// 	int i = 0;
// 	char sql[] = "select matricula, marca, modelo, automatico, plazas, anyoFabricacion from coche";

// 	// preparamos el statement
// 	// le pasamos la bd
// 	// le pasamos la sentencia sql
// 	// le pasamos la direcci�n de memoria de stmt, para que guarde ah� lo que nos devuelva la bd en formato de tabla (filas/columnas)
// 	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
// 	if (result != SQLITE_OK) {
// 		printf("Error preparing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db)); // imprime el mensaje de error que devuelve la bd
// 		return NULL;
// 	}

// 	printf("SQL query prepared (SELECT)\n"); // si va bien

// 	printf("//////////////////////\n");
// 	printf("//////////////////////\n");
// 	printf("Coches:\n");
// 	// recorres todas las filas de stmt (lo que te devuelve la bd despues de mandarle la sentencia)
// 	// este do while se va a hacer tantas veces como filas existan en el stmt
// 	do {
// 		result = sqlite3_step(stmt); // el step salta de fila y guarda en resultado si hay una fila o no
// 		if (result == SQLITE_ROW) { // si existe una fila
// 			strcpy(coches[i].matricula, (char*) sqlite3_column_text(stmt, 0));
// 			strcpy(coches[i].marca, (char*) sqlite3_column_text(stmt, 1));
// 			strcpy(coches[i].modelo, (char*) sqlite3_column_text(stmt, 2));
// 			coches[i].automatico = sqlite3_column_text(stmt, 3);
// 			coches[i].plazas = sqlite3_column_text(stmt, 4);
// 			coches[i].anyoFabricacion = sqlite3_column_text(stmt, 5);
// 			i++;
// 		}
// 	} while (result == SQLITE_ROW);  // mientras que exista fila

// 	printf("\n");
// 	printf("\n");

// 	printf("Prepared statement finalized (SELECT)\n");

// 	result = sqlite3_finalize(stmt);
// 	if (result != SQLITE_OK) {
// 		printf("Error finalizing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	return coches;
// }

// Comprador* getCompradores(sqlite3* db){
//     sqlite3_stmt* stmt;
//     Comprador* compradores = (Comprador*) malloc(100 * sizeof(Comprador));

// 	char nombre[25];
// 	char dni[9];
// 	char email[25];
// 	char cuentaBancaria[20];

//     int i = 0;
// 	char sql[] = "select nombre, dni, email, cuentaBancaria, usuario, contrasenya from usuario where tipo = 0; 

// 	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
// 	if (result != SQLITE_OK) {
// 		printf("Error preparing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	printf("SQL query prepared (SELECT)\n");

// 	printf("//////////////////////\n");
// 	printf("//////////////////////\n");
// 	printf("Compradores:\n");

// 	do {
// 		result = sqlite3_step(stmt);
// 		if (result == SQLITE_ROW) {
// 			strcpy(compradores[i].nombre, (char*) sqlite3_column_text(stmt, 0));
//          strcpy(compradores[i].dni, (char*) sqlite3_column_text(stmt, 1));
//          strcpy(compradores[i].email, (char*) sqlite3_column_text(stmt, 2));
//          strcpy(compradores[i].cuentaBancaria, (char*) sqlite3_column_text(stmt, 3));
//          strcpy(vendedores[i].usuario, (char*) sqlite3_column_text(stmt, 4));
//          strcpy(vendedores[i].contrasenya, (char*) sqlite3_column_text(stmt, 5));
//          i++;
// 		}
// 	} while (result == SQLITE_ROW);

// 	printf("\n");
// 	printf("\n");

// 	printf("Prepared statement finalized (SELECT)\n");

// 	result = sqlite3_finalize(stmt);
// 	if (result != SQLITE_OK) {
// 		printf("Error finalizing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	return compradores;
// }

// Vendedor* getVendedores(sqlite3* db){
//     sqlite3_stmt* stmt;
//     Vendedor* vendedores = (Vendedor) malloc(100 * sizeof(Vendedor));

// 	char nombre[25];
// 	char dni[9];
// 	char email[25];
// 	float sueldo;
// 	int numVentas;

//     int i = 0;
// 	char sql[] = "select nombre, dni, email, sueldo, numVentas, usuario, contrasenya from usuario where tipo = 1"; 

// 	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
// 	if (result != SQLITE_OK) {
// 		printf("Error preparing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	printf("SQL query prepared (SELECT)\n");

// 	printf("//////////////////////\n");
// 	printf("//////////////////////\n");
// 	printf("Vendedores:\n");

// 	do {
// 		result = sqlite3_step(stmt);
// 		if (result == SQLITE_ROW) {
// 			strcpy(vendedores[i].nombre, (char*) sqlite3_column_text(stmt, 0));
//             strcpy(vendedores[i].dni, (char*) sqlite3_column_text(stmt, 1));
//             strcpy(vendedores[i].email, (char*) sqlite3_column_text(stmt, 2));
//             atoi(vendedores[i].sueldo, sqlite3_column_text(stmt, 3));
//             atoi(vendedores[i].numVentas, sqlite3_column_text(stmt, 4));
//             strcpy(vendedores[i].usuario, (char*) sqlite3_column_text(stmt, 5));
//             strcpy(vendedores[i].contrasenya, (char*) sqlite3_column_text(stmt, 6));
//             i++;
// 		}
// 	} while (result == SQLITE_ROW);

// 	printf("\n");
// 	printf("\n");

// 	printf("Prepared statement finalized (SELECT)\n");

// 	result = sqlite3_finalize(stmt);
// 	if (result != SQLITE_OK) {
// 		printf("Error finalizing statement (SELECT)\n");
// 		printf("%s\n", sqlite3_errmsg(db));
// 		return NULL;
// 	}

// 	return vendedores;
// }

int updateCoche(sqlite3* db, char marca[15], char modelo[15], int automatico, int plazas, int anyoFabricacion);
// pasarle solo la referencia del coche (matr�cula)

int insertTicket(sqlite3* db, char nomComprador[25], char nomCoche[40], char fechaCompra[10]);

int deleteTickets(sqlite3* db, char usuario[20]) {
	sqlite3_stmt *stmt;

	char sql[] = "delete * from comprador where (usuario) values (?)"; // where comprador == ?

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");

	return SQLITE_OK;
}

int loginBD(sqlite3 *db, char usuario[20], char contrasenya[20]){
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];

	char sql[] = "select usuario, contrasenya from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql)+1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		strcpy(usuarioTemp, (char*) sqlite3_column_text(stmt, 0));
		strcpy(contrasenyaTemp, (char*) sqlite3_column_text(stmt, 1));
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	if(strcmp(usuarioTemp,usuario) == 0 && strcmp(contrasenyaTemp, contrasenya) ==0) {
		printf("Usuario y contrasenya coinciden");
		return 1;
	}

	return 0;
}
//int imprimirTickets(sqlite3* db, char nomComprador[25]);
