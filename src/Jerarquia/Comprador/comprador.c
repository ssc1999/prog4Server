#include "comprador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirComprador(Comprador comprador)
{
	printf("Nombre: %s\n", comprador.nombre);
	printf("Dni: %s\n", comprador.dni);
	printf("Email: %s\n", comprador.email);
	printf("Cuenta bancaria: %s\n", comprador.cuentaBancaria);
}

void comprarCoche(sqlite3 *db, char matricula[20], char usuario[20]){
	//CREAR TICKET

	//UPDATE VENDEDOR

	//UPDATE COCHE
}

Comprador* getComprador(sqlite3 *db, char usuario[20]){
	Comprador* comprador = (Comprador*) malloc(sizeof(Comprador));
	comprador = getCompradorBD(db, usuario);
	printf("%s", comprador->usuario);
	return comprador;
}

// char *getNombreComprador(sqlite3 *db, char usuario[20]){
// 	char *nombreComprador = malloc(sizeof(char) * 20);
// 	strcpy(nombreComprador, getComprador(db, usuario).nombre);
// 	return nombreComprador;
// }