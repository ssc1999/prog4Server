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

void getAllCoches(sqlite3* db, Coche *coches){
 	sqlite3_stmt* stmt; // statement para guardar lo que te devuelve la bd
	 // meter en este array de coches lo que hay en cada fila que me devuelve la bd
	char matricula[25], marca[25], modelo[25], matriculaTemp[25];
	int automatico, plazas, anyoFabricacion;
	// la bd te devuelve filas
	// dentro de cada fila, cada columna ser� un atributo
	// meteremos eso en los atributos que creo
	// despu�s con esos atributos crearemos una struct y despu�s esa struct la metemos en el array de structs

	// crear sentencia sql
 	int i = 0;
 	char sql[] = "select matricula, marca, modelo, automatico, plazas, anyoFabricacion from coche where comprado = '0'";

 	// preparamos el statement
 	// le pasamos la bd
 	// le pasamos la sentencia sql
 	// le pasamos la direcci�n de memoria de stmt, para que guarde ah� lo que nos devuelva la bd en formato de tabla (filas/columnas)
 	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
 	// if (result != SQLITE_OK) {
 	// 	printf("Error preparing statement (SELECT)\n");
 	// 	printf("%s\n", sqlite3_errmsg(db)); // imprime el mensaje de error que devuelve la bd
 	// 	return NULL;
 	// }

 	printf("SQL query prepared (SELECT)\n"); // si va bien

 	// recorres todas las filas de stmt (lo que te devuelve la bd despues de mandarle la sentencia)
 	// este do while se va a hacer tantas veces como filas existan en el stmt
	printf("//////////////////////////////////\n");
	printf("//////////////////////////////////\n");
	printf("DATOS DE LA BD\n");
	do {
		
		result = sqlite3_step(stmt); // el step salta de fila y guarda en resultado si hay una fila o no
		if (result == SQLITE_ROW) { // si existe una fila
			strcpy(matricula, (char*)sqlite3_column_text(stmt, 0));
			strcpy(marca, (char*) sqlite3_column_text(stmt, 1));
 			strcpy(modelo, (char*) sqlite3_column_text(stmt, 2));
 			automatico = sqlite3_column_int(stmt, 3);
 			plazas = sqlite3_column_int(stmt, 4);
 			anyoFabricacion = sqlite3_column_int(stmt, 5);
			printf("Matricula bd : %s\n" ,matricula);
			printf("marca bd : %s\n" ,marca);
			strcpy(coches[i].matricula, matricula);
			strcpy(coches[i].marca, marca);
			strcpy(coches[i].modelo, modelo);
			printf("Coche %i:\n", i);
			printf("Matricula %s\n", coches[i].matricula);
			printf("Marca %s\n", coches[i].marca);
			printf("Modelo %s\n", coches[i].modelo);
			i++;
		}
		
 	} while (result == SQLITE_ROW);  // mientras que exista fila
	printf("//////////////////////////////////");
	printf("//////////////////////////////////");
 	printf("\n");
 	printf("\n");

 	printf("Prepared statement finalized (SELECT)\n");

 	result = sqlite3_finalize(stmt);
 	// if (result != SQLITE_OK) {
 	// 	printf("Error finalizing statement (SELECT)\n");
 	// 	printf("%s\n", sqlite3_errmsg(db));
 	// 	return NULL;
 	// }

 	return ;
 }

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

// SELECT DONE
int login(sqlite3 *db, char usuario[20], char contrasenya[20])
{
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	int tipo;

	char sql[] = "select usuario, contrasenya, tipo from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		strcpy(usuarioTemp, (char *)sqlite3_column_text(stmt, 0));
		strcpy(contrasenyaTemp, (char *)sqlite3_column_text(stmt, 1));
		tipo = sqlite3_column_int(stmt, 2);
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	if (strcmp(usuarioTemp, usuario) == 0 && strcmp(contrasenyaTemp, contrasenya) == 0)
	{
		printf("Usuario y contrasenya coinciden");
		return tipo;
	}
	return 0;
}

// UPDATE
int updateCocheBD(sqlite3 *db, char matricula[10], char usuario[10])
{
}

// INSERT
int insertTicket(sqlite3 *db, Ticket *ticket)
{
	sqlite3_stmt *stmt;

	char sql[] = "insert into ticket (nomUsuario, nomComprador, matricula, fechaCompra) values( ?, ?, ?, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, ticket->nomComprador, strlen(ticket->nomComprador), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, ticket->nomUsuario, strlen(ticket->nomUsuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, ticket->matricula, strlen(ticket->matricula), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, ticket->fechaCompra, strlen(ticket->fechaCompra), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return 0;
}

// SELECT
Comprador getCompradorBD(sqlite3 *db, char usuario[20])
{
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	Comprador c;

	char sql[] = "select usuario, contrasenya, nombre, dni, email, cuentaBancaria from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return c;
	}

	printf("SQL query prepared (SELECT)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return c;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		strcpy(c.usuario, (char *)sqlite3_column_text(stmt, 0));
		strcpy(c.contrasenya, (char *)sqlite3_column_text(stmt, 1));
		strcpy(c.nombre, (char *)sqlite3_column_text(stmt, 2));
		strcpy(c.dni, (char *)sqlite3_column_text(stmt, 3));
		strcpy(c.email, (char *)sqlite3_column_text(stmt, 4));
		strcpy(c.cuentaBancaria, (char *)sqlite3_column_text(stmt, 5));

		// c.usuario = (char *)sqlite3_column_text(stmt, 0);
		// c.contrasenya = (char *)sqlite3_column_text(stmt, 1);
		// c.nombre = (char *)sqlite3_column_text(stmt, 2);
		// c.dni = (char *)sqlite3_column_text(stmt, 3);
		// c.email = (char *)sqlite3_column_text(stmt, 4);
		// c.cuentaBancaria = (char *)sqlite3_column_text(stmt, 5);
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return c;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return c;
}
// SELECT
Vendedor getVendedor(sqlite3 *db, char usuario[20]){

}
// SELECT
Coche *getCoches(sqlite3 *db, char usuario[20])
{
}
// SELECT
Ticket *getTickets(sqlite3 *db, char usuario[20])
{
}
// INSERT
int registrarComprador(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25], char cuentaBancaria[20])
{
	sqlite3_stmt *stmt;
	printf("%s\n", usuario);
	printf("%s\n", contrasenya);
	printf("%s\n", nombre);
	printf("%s\n", dni);
	printf("%s\n", email);
	printf("%s\n", cuentaBancaria);
	char tipo[3] = "1";
	char sql[] = "insert into usuario (nombre, dni, tipo, cuentaBancaria, usuario, contrasenya, sueldo, numVentas, email) values( ?, ?, ?, ?, ?, ?, NULL, NULL, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 4, cuentaBancaria, strlen(cuentaBancaria), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 5, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	result = sqlite3_bind_text(stmt, 6, contrasenya, strlen(contrasenya), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 7, email, strlen(email), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into comprador table\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement\n");
		return 0;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return 1;
}
// INSERT
int registrarVendedor(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25])
{
	sqlite3_stmt *stmt;

	char tipo[3] = "2";
	char sql[] = "insert into usuario (nombre, dni, tipo, cuentaBancaria, usuario, contrasenya, sueldo, numVentas, email) values( ?, ?, ?, NULL, ?, ?, NULL, NULL, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 4, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
	result = sqlite3_bind_text(stmt, 5, contrasenya, strlen(contrasenya), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 6, email, strlen(email), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into comprador table\n");
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return 1;
}

// DELETE
int deleteTickets(sqlite3 *db, char usuario[20])
{
	sqlite3_stmt *stmt;

	char sql[] = "delete * from comprador where (usuario) values (?)"; // where comprador == ?

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK)
	{
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
	{
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
	{
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");

	return SQLITE_OK;
}

// int imprimirTickets(sqlite3* db, char nomComprador[25]);
