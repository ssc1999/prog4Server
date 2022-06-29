#include "coche.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Logger/log.h"
#include "../../BD/BD.h"
#include "../../BD/sqlite3.h"
//#include "../../Log/logger.h"

void imprimirCoche(Coche *coche) {
	printf("Matricula: %s\n", coche->matricula);
	printf("Marca: %s\n", coche->marca);
	printf("Modelo: %s\n", coche->modelo);
	if(coche->automatico == 0){
		printf("No automatico\n");
	} else if(coche->automatico == 1){
		printf("Automatico\n");
	}
	printf("Plazas: %d\n", coche->plazas);
	printf("Anyo fabricacion: %d\n", coche->anyoFabricacion);
	printf("Precio: %i\n", coche->precio);
}

void copiarCoches(Coche** cocheOrigen, Coche** cocheDestino){
	for (int i = 0; i < 4;i++){
		free(cocheDestino[i]);
	}
	cocheDestino = cocheOrigen;
	free(cocheOrigen);
}

Coche *getCoche(sqlite3 *db, char usuario[20]){
	log_trace("Consultando coche a la BD");
	Coche* coche = (Coche*) malloc(sizeof(Coche));
	coche = getCocheBD(db, usuario);
	log_trace("Mandando coche al server");
	return coche;
}

void updateCoche(sqlite3 *db, char matricula[20], char usuario[20]){
	log_trace("Mandando update coche a la BD");
	updateCocheBD(db, matricula, usuario);
	log_trace("Coche editado con exito a la BD");
}