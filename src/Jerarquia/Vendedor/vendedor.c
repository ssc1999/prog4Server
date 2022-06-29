#include "vendedor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Logger/log.h"
#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirVendedor(Vendedor vendedor) {
	printf("Nombre: %s\n", vendedor.nombre);
	printf("Dni: %s\n", vendedor.dni);
	printf("Email: %s\n", vendedor.email);
	printf("Sueldo: %f\n", vendedor.sueldo);
	printf("Numero de ventas: %f\n", vendedor.numVentas);
}

Vendedor* getVendedor(sqlite3 *db, char usuario[20]){
	log_trace("Consultando vendedor a la BD");
	Vendedor *vendedor = (Vendedor *)malloc(sizeof(Vendedor));
	vendedor = getVendedorBD(db, usuario);
	log_trace("Mandando vendedor al server");
	return vendedor;
}

void updateVendedor(sqlite3 *db, int precioCoche, char usuario[20]){
	log_trace("Mandando update vendedor a la BD");
	//cogemos el sueldo del admin, le sumamos el precio del coche nuevo, y hacemos update con ese valor
	int precio;
	Vendedor *vendedor = (Vendedor *)malloc(sizeof(Vendedor));
	vendedor = getVendedor(db, usuario);
	precio = vendedor->sueldo;
	precio += precioCoche;
	updateVendedorBD(db, precio, usuario);
	log_trace("Vendedor editado con exito a la BD");
}