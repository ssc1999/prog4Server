#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "BD.h"
#include "sqlite3.h"
#include "../Logger/log.h"
#include "../Jerarquia/Coche/coche.h"
#include "../Jerarquia/Comprador/comprador.h"
#include "../Jerarquia/Ticket/ticket.h"
#include "../Jerarquia/Vendedor/vendedor.h"


Coche** getAllCoches(sqlite3* db)
{
 	sqlite3_stmt* stmt; // statement para guardar lo que te devuelve la bd
	 // meter en este array de coches lo que hay en cada fila que me devuelve la bd
	Coche **coches = (Coche **)malloc(sizeof(Coche *) * 4);
	char matricula[25], marca[25], modelo[25], matriculaTemp[25];
	int i, automatico, plazas, anyoFabricacion;

	for(i = 0; i < 4; i++){
		coches[i] = (Coche *)malloc(sizeof(Coche));
	}
	// la bd te devuelve filas
	// dentro de cada fila, cada columna ser� un atributo
	// meteremos eso en los atributos que creo
	// despu�s con esos atributos crearemos una struct y despu�s esa struct la metemos en el array de structs

	// crear sentencia sql
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
		i = 0;
		result = sqlite3_step(stmt); // el step salta de fila y guarda en resultado si hay una fila o no
		if (result == SQLITE_ROW) { // si existe una fila
			strcpy(coches[i]->matricula, (char*)sqlite3_column_text(stmt, 0));
			strcpy(coches[i]->marca, (char*) sqlite3_column_text(stmt, 1));
 			strcpy(coches[i]->modelo, (char*) sqlite3_column_text(stmt, 2));
 			coches[i]->automatico = sqlite3_column_int(stmt, 3);
 			coches[i]->plazas = sqlite3_column_int(stmt, 4);
 			coches[i]->anyoFabricacion = sqlite3_column_int(stmt, 5);
			printf("Coche %i:\n", i);
			printf("Matricula %s\n", coches[i]->matricula);
			printf("Marca %s\n", coches[i]->marca);
			printf("Modelo %s\n", coches[i]->modelo);
			printf("Automatico: %i\n", coches[i]->automatico);
			printf("Plazas: %i\n", coches[i]->plazas);
			printf("Anyo de fabricacion: %i\n", coches[i]->anyoFabricacion);
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

 	return coches;
 }

// SELECT DONE
int login(sqlite3 *db, char usuario[20], char contrasenya[20])
{
	log_trace("Dentro metodo login BD");
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	int tipo;

	char sql[] = "select usuario, contrasenya, tipo from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia SELECT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);

	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		strcpy(usuarioTemp, (char *)sqlite3_column_text(stmt, 0));
		strcpy(contrasenyaTemp, (char *)sqlite3_column_text(stmt, 1));
		tipo = sqlite3_column_int(stmt, 2);
	}

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia SELECT finalizada");

	if (strcmp(usuarioTemp, usuario) == 0 && strcmp(contrasenyaTemp, contrasenya) == 0)
	{
		log_trace("usuario y contrasenya coinciden");
		return tipo;
	}

	log_trace("Saliendo del metodo login BD");
	return 0;
}

// UPDATE
int updateCocheBD(sqlite3 *db, char matricula[10], char usuario[10])
{
	log_trace("Dentro metodo updateCoche BD");
	sqlite3_stmt *stmt;

	char sql[] = "update coche SET (comprado, usuarioComprador) values(1, ?) where matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia INSERT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia UPDATE finalizada");
	log_trace("Saliendo del metodo updateCoche BD");
}

int updateVendedorBD(sqlite3 *db, int precioCoche, char usuario[10])
{
	log_trace("Dentro metodo updateVendedor BD");
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "update usuario SET (sueldo) values(%i) where usuario = ?", precioCoche);
	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia INSERT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia UPDATE finalizada");
	log_trace("Saliendo del metodo updateVendedor BD");
}

// INSERT
int insertTicketBD(sqlite3 *db, Ticket *ticket)
{
	log_trace("Dentro metodo insertTicket BD");
	sqlite3_stmt *stmt;

	char sql[] = "insert into ticket (nomUsuario, nomComprador, matricula, fechaCompra) values( ?, ?, ?, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia INSERT");

	result = sqlite3_bind_text(stmt, 1, ticket->nomComprador, strlen(ticket->nomComprador), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 1, ticket->nomUsuario, strlen(ticket->nomUsuario), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 1, ticket->matricula, strlen(ticket->matricula), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 1, ticket->fechaCompra, strlen(ticket->fechaCompra), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	log_trace("Atributos anyadidos a la sentencia");
	result = sqlite3_finalize(stmt);

	log_trace("Sentencia INSERT finalizada");
	log_trace("Saliendo del metodo insertTicket BD");
	return 0;
}

// SELECT
Comprador* getCompradorBD(sqlite3 *db, char usuario[20])
{
	log_trace("Dentro metodo getComprador BD");
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	Comprador* c = (Comprador*) malloc(sizeof(Comprador));

	char sql[] = "select usuario, contrasenya, nombre, dni, email, cuentaBancaria from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia SELECT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_step(stmt);
	
	if (result == SQLITE_ROW)
	{
		strcpy(c->usuario, (char *)sqlite3_column_text(stmt, 0));
		strcpy(c->contrasenya, (char *)sqlite3_column_text(stmt, 1));
		strcpy(c->nombre, (char *)sqlite3_column_text(stmt, 2));
		strcpy(c->dni, (char *)sqlite3_column_text(stmt, 3));
		strcpy(c->email, (char *)sqlite3_column_text(stmt, 4));
		strcpy(c->cuentaBancaria, (char *)sqlite3_column_text(stmt, 5));
	}
	result = sqlite3_finalize(stmt);

	log_trace("Sentencia SELECT finalizada");
	log_trace("Saliendo del metodo getComprador BD");

	return c;
}
// SELECT
Vendedor* getVendedorBD(sqlite3 *db, char usuario[20])
{
	log_trace("Dentro metodo getVendedor BD");
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	Vendedor* v = (Vendedor*) malloc(sizeof(Vendedor));

	char sql[] = "select usuario, contrasenya, nombre, dni, email, sueldo, numVentas from usuario where usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia SELECT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);

	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		strcpy(v->usuario, (char *)sqlite3_column_text(stmt, 0));
		strcpy(v->contrasenya, (char *)sqlite3_column_text(stmt, 1));
		strcpy(v->nombre, (char *)sqlite3_column_text(stmt, 2));
		strcpy(v->dni, (char *)sqlite3_column_text(stmt, 3));
		strcpy(v->email, (char *)sqlite3_column_text(stmt, 4));
		v->sueldo = sqlite3_column_int(stmt, 5);
		v->numVentas = sqlite3_column_int(stmt, 6);
	}

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia SELECT finalizada");
	log_trace("Saliendo del metodo getVendedor BD");

	return v;
}
// SELECT
Coche* getCocheBD(sqlite3 *db, char usuario[20])
{
	log_trace("Dentro metodo getCoche BD");
	sqlite3_stmt *stmt;
	Coche* c = (Coche*) malloc(sizeof(Coche));

	char sql[] = "select marca, modelo, automatico, anyoFabricacion, matricula, plazas, precio from coche where usuarioComprador = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia SELECT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);

	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW)
	{
		strcpy(c->matricula, (char *)sqlite3_column_text(stmt, 4));
		strcpy(c->marca, (char *)sqlite3_column_text(stmt, 0));
		strcpy(c->modelo, (char *)sqlite3_column_text(stmt, 1));
		c->automatico = sqlite3_column_int(stmt, 2);
		c->anyoFabricacion = sqlite3_column_int(stmt, 3);
		c->plazas = sqlite3_column_int(stmt, 5);
		c->precio = sqlite3_column_int(stmt, 6);
	}

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia SELECT finalizada");
	log_trace("Saliendo del metodo getCoche BD");

	return c;
}
// SELECT
Ticket *getTicketBD(sqlite3 *db, char usuario[20])
{
	log_trace("Dentro metodo getCoche BD");
	sqlite3_stmt *stmt;
	char usuarioTemp[20], contrasenyaTemp[20];
	Ticket* t = (Ticket*) malloc(sizeof(Ticket));

	char sql[] = "select nomComprador, matricula, fechaCompra, nomUsuario, precio from ticket where nomUsuario = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia SELECT");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_step(stmt);
	
	if (result == SQLITE_ROW)
	{
		strcpy(t->nomComprador, (char *)sqlite3_column_text(stmt, 0));
		strcpy(t->matricula, (char *)sqlite3_column_text(stmt, 1));
		strcpy(t->fechaCompra, (char *)sqlite3_column_text(stmt, 2));
		strcpy(t->nomUsuario, (char *)sqlite3_column_text(stmt, 3));
		t->precio = sqlite3_column_int(stmt, 4);
	}

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia SELECT finalizada");
	log_trace("Saliendo del metodo getCoche BD");

	return t;
}
// INSERT
int registrarComprador(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25], char cuentaBancaria[20])
{
	log_trace("Dentro metodo registrarComprador BD");
	sqlite3_stmt *stmt;
	char tipo[3] = "1";
	char sql[] = "insert into usuario (nombre, dni, tipo, cuentaBancaria, usuario, contrasenya, sueldo, numVentas, email) values( ?, ?, ?, ?, ?, ?, NULL, NULL, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia INSERT");

	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, cuentaBancaria, strlen(cuentaBancaria), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, usuario, strlen(usuario), SQLITE_STATIC);	
	result = sqlite3_bind_text(stmt, 6, contrasenya, strlen(contrasenya), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 7, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia INSERT finalizada");
	log_trace("Saliendo del metodo registrarVendedor BD");

	return 1;
}
// INSERT
int registrarVendedor(sqlite3 *db, char usuario[20], char contrasenya[20], char nombre[25], char dni[9], char email[25])
{
	log_trace("Dentro metodo registrarVendedor BD");
	sqlite3_stmt *stmt;

	char tipo[3] = "2";
	char sql[] = "insert into usuario (nombre, dni, tipo, cuentaBancaria, usuario, contrasenya, sueldo, numVentas, email) values( ?, ?, ?, NULL, ?, ?, NULL, NULL, ?)";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	log_trace("Preparando sentencia INSERT");

	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 3, tipo, strlen(tipo), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, usuario, strlen(usuario), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, contrasenya, strlen(contrasenya), SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 6, email, strlen(email), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	log_trace("Atributos anyadidos a la sentencia");

	result = sqlite3_finalize(stmt);

	log_trace("Sentencia INSERT finalizada");
	log_trace("Saliendo del metodo registrarVendedor BD");

	return 1;
}