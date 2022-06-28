// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include "BD/sqlite3.h"
#include "BD/BD.h"
#include "Logger/log.h"
#include "Jerarquia/Comprador/comprador.h"
#include "Jerarquia/Vendedor/vendedor.h"
#include "Jerarquia/Ticket/ticket.h"
#include "Jerarquia/Coche/coche.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void menu(SOCKET comm_socket);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];
	char opcion[20], opcion2[20], usuario[20], contrasenya[20], nombre[25], dni[9], email[25], cuentaBancaria[20], matricula[20], nomComprador[20],  fechaCompra[20];
	float sueldo;
	int i, numVentas, tamanyo, resultado;
	Ticket *ticket;
	Coche** coches;
	Coche* coche;
	Comprador *comprador;
	Vendedor* vendedor;
	sqlite3 *db;
	FILE *fp ; 
	fp = fopen("Logger/log.log", "r+");
	log_add_fp(fp, 0);

	int result = sqlite3_open("BD/BD.sqlite", &db);
	if (result != SQLITE_OK)
	{
		log_error("Error opening database\n");
	}

	log_info("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		log_error("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	log_info("Initialised.\n");

	// SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		log_error("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	log_info("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr *)&server,
			 sizeof(server)) == SOCKET_ERROR)
	{
		log_error("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	log_info("Bind done.\n");

	// LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR)
	{
		log_error("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	// ACCEPT incoming connections (server keeps waiting for them)
	log_info("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr *)&client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET)
	{
		log_error("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	log_info("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
		   ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	// SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	log_info("Waiting for incoming commands from client... \n");

	do
	{
		
		
		comprador = (Comprador *)malloc(sizeof(Comprador));
		vendedor = (Vendedor *)malloc(sizeof(Vendedor));
		coche = (Coche *)malloc(sizeof(Coche));

		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		strcpy(opcion, recvBuff);
		log_info("Servidor esperando instrucciones");
		if (strcmp(opcion, "login") == 0)
		{
			log_info("Proceso de login iniciado");

			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(usuario, recvBuff);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(contrasenya, recvBuff);

			log_info("Usuario y contrasenya recibidos");

			resultado = login(db, usuario, contrasenya);
			// COMPRADOR
			if (resultado == 1)
			{
				strcpy(sendBuff, "comprador");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				log_info("Comprador logueado con exito");
				log_trace("user(%s) - password(%s)", usuario, contrasenya);
				do
				{
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					strcpy(opcion2, recvBuff);
					log_info("Servidor esperando instrucciones");

					if (strcmp(opcion2, "comprarCoches") == 0)
					{
						log_info("Opcion comprarCoches seleccionada");
						// crear array dinamico de punteros de coches
						coches = (Coche**) malloc(20*sizeof(Coche*));
						for (i = 0; i < 20; i++){
							coches[i] = (Coche*) malloc(sizeof(Coche));
						}
						copiarCoches(coches,getAllCoches(db));
						strcpy(sendBuff, "20");
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						// guardar array de coches que devuelve la bd
						
						for ( i = 0; i < 5; i++)
						{
							printf("Main coche %i: \n Matricula: %s \n Marca: %s \n Modelo: %s \n \n", i, coches[i]->matricula, coches[i]->marca, coches[i]->modelo);
						}

						// mandar coches (todos sus atributos) al cliente con un for
						for(i = 0; i < 20; i++){
							strcpy(sendBuff, coches[i]->matricula);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							strcpy(sendBuff, coches[i]->marca);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							strcpy(sendBuff, coches[i]->modelo);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							sscanf(sendBuff, "%ld", coches[i]->automatico);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							sscanf(sendBuff, "%ld", coches[i]->plazas);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							sscanf(sendBuff, "%ld", coches[i]->anyoFabricacion);
							printf("%s", sendBuff);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							fflush(stdout);
						}		

						// recibir matricula
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						strcpy(matricula, recvBuff);

						// recibir usuario
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						strcpy(usuario, recvBuff);

						// recibir fechaCompra
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
						strcpy(fechaCompra, recvBuff);

						// mandar nombreComprador
						// strcpy(nomComprador, getNombreComprador(db, usuario));
						// strcpy(sendBuff,nomComprador);
						// send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						
						// // crear ticket y meterlo en la bd
						// strcpy(ticket->matricula, matricula);
						// strcpy(ticket->nomUsuario, usuario);
						// strcpy(ticket->nomComprador, nomComprador);
						// strcpy(ticket->fechaCompra, fechaCompra);

						// if(comprarCoche(db, ticket) == 0){
						// 	strcpy(sendBuff,"OK");
						// 	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						// }else{
						// 	strcpy(sendBuff,"Error");
						// 	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						// }
						/* code */
						for (i = 0; i < 20; i++){
							free(coches[i]);
						}
						free(coches);
						
					}
					else if (strcmp(opcion2, "miCoche") == 0)
					{
						log_info("Opcion miCoche seleccionada");
						coche = getCoche(db, usuario);
		
						strcpy(sendBuff, coche->matricula);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				

						strcpy(sendBuff, coche->marca);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				

						strcpy(sendBuff, coche->modelo);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				

						itoa(coche->automatico, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				

						itoa(coche->plazas, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				

						itoa(coche->anyoFabricacion, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				
						
						itoa(coche->precio, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				
						log_trace("Coche-> matricula(%s), marca(%s), modelo(%s), automatico(%i), plazas(%i), anyoFabricacion(%i), precio(%i)", coche->matricula, coche->marca, coche->modelo, coche->automatico, coche->plazas, coche->anyoFabricacion, coche->precio);
										}
					else if (strcmp(opcion2, "miTicket") == 0)
					{
						log_info("Opcion miTicket seleccionada");
						ticket = getTicket(db, usuario);

						strcpy(sendBuff, ticket->nomComprador);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", ticket->nomComprador);
						strcpy(sendBuff, ticket->nomUsuario);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", ticket->nomUsuario);
						strcpy(sendBuff, ticket->matricula);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", ticket->matricula);
						strcpy(sendBuff, ticket->fechaCompra);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", ticket->fechaCompra);

						log_trace("Ticket-> nomComprador(%s), nomUsuario(%s), matricula(%s), fechaCompra(%s)", ticket->nomComprador, ticket->nomUsuario, ticket->matricula, ticket->fechaCompra);	
					}
					else if (strcmp(opcion2, "verPerfil") == 0)
					{
						log_info("Opcion verPerfil seleccionada");
						comprador = getComprador(db, usuario);

						strcpy(sendBuff, comprador->usuario);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", comprador->usuario);
						strcpy(sendBuff, comprador->nombre);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", comprador->nombre);
						strcpy(sendBuff, comprador->dni);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", comprador->dni);
						strcpy(sendBuff, comprador->email);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", comprador->email);
						strcpy(sendBuff, comprador->cuentaBancaria);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", comprador->cuentaBancaria);

						log_trace("Comprador-> usuario(%s), nombre(%s), dni(%s), email(%s), cuentaBancaria(%s)", comprador->usuario, comprador->nombre, comprador->dni, comprador->email, comprador->cuentaBancaria);
					}
				} while (strcmp(opcion2, "cerrarSesion") != 0);
				log_info("Sesion cerrada con exito");
			}
			
			else if (resultado == 2)
			{
				strcpy(sendBuff, "vendedor");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				log_info("Vendedor logueado con exito");
				log_trace("user(%s) - password(%s)", usuario, contrasenya);
				do
				{
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					strcpy(opcion2, recvBuff);
					log_info("Servidor esperando instrucciones");

					if (strcmp(opcion2, "verPerfil") == 0)
					{
						log_info("Opcion verPerfil seleccionada");

						if(strcmp(vendedor->usuario, usuario) != 0){
							vendedor = getVendedor(db, usuario);
						}

						printf("%s", vendedor->usuario);
						strcpy(sendBuff, vendedor->usuario);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", vendedor->nombre);
						strcpy(sendBuff, vendedor->nombre);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", vendedor->dni);
						strcpy(sendBuff, vendedor->dni);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("%s", vendedor->email);
						strcpy(sendBuff, vendedor->email);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						
						log_trace("Vendedor-> usuario(%s), nombre(%s), dni(%s), email(%s)", vendedor->usuario,  vendedor->nombre, vendedor->dni, vendedor->email);
						/* code */
					}
					else if (strcmp(opcion2, "verDinero") == 0)
					{
						log_info("Opcion verDinero seleccionada");

						if(strcmp(vendedor->usuario, usuario) != 0){
							vendedor = getVendedor(db, usuario);
						}
						itoa(vendedor->sueldo, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);

						log_trace("Sueldo-> %i", vendedor->sueldo);
					}
					else if (strcmp(opcion2, "verNumeroVentas") == 0)
					{
						log_info("Opcion verNumeroVentas seleccionada");

						if(strcmp(vendedor->usuario, usuario) != 0){
							vendedor = getVendedor(db, usuario);
						}
						itoa(vendedor->numVentas, sendBuff, 10);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);

						log_trace("Numero de ventas-> %i", vendedor->numVentas);
					}
				} while (strcmp(opcion2, "cerrarSesion") != 0);
				log_info("Sesion cerrada con exito");
			}
			else// mirar
			{
				strcpy(sendBuff, "erroneos");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				log_error("Usuario y/o contrasenya incorrecto/s");
			}
		}else if (strcmp(opcion, "registro") == 0)
		{
			log_info("Proceso de registro iniciado");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(opcion2, recvBuff);

			if (strcmp(opcion2, "1") == 0)
			{
				log_info("Iniciando registro de comprador");
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(nombre, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(email, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(cuentaBancaria, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(usuario, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasenya, recvBuff);

				if (registrarComprador(db, usuario, contrasenya, nombre, dni, email, cuentaBancaria) == 1)
				{
					log_info("Comprador agregado con exito a la base de datos");
				}
				else
				{
					log_error("Error intentando agregar el comprador a la base de datos");
				}
			fflush(stdout);
			}
			else if (strcmp(opcion2, "2") == 0)
			{
				log_info("Iniciando registro de vendedor");
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(nombre, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(email, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(usuario, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasenya, recvBuff);

				if (registrarVendedor(db, usuario, contrasenya, nombre, dni, email) == 1)
				{
					log_info("Vendedor agregado con exito a la base de datos");
				}
				else
				{
					log_error("Error intentando agregar el vendedor a la base de datos");
				}
			}
			else
			{
				log_error("Error introduciendo la opcion");
				strcpy(sendBuff, "error");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		fflush(stdout);
		}
	} while (strcmp(opcion, "exit") != 0);

	free(vendedor);
	free(comprador);
	free(coche);
	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();
	log_info("Programa cerrado con exito");
	fclose(fp);

	return 0;
}
