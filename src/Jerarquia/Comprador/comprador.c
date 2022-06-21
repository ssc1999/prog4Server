#include "comprador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirComprador(Comprador comprador) {
	printf("Nombre: %s\n", comprador.nombre);
	printf("Dni: %s\n", comprador.dni);
	printf("Email: %s\n", comprador.email);
	printf("Cuenta bancaria: %s\n", comprador.cuentaBancaria);
}

int login(sqlite3* db, char usuario[20], char contrasenya[20]){
	int result = loginBD(db, usuario, contrasenya);
	return result;
}

int comprarCoche(sqlite3 *db, char matricula[20], char usuario){
	//metodo BD de cambiar atributo en coche 
	//metodo de crear ticket
}