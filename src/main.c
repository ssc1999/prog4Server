// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include "BD/sqlite3.h"
#include "BD/BD.h"
#include "Jerarquia/Comprador/comprador.h"

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
	char opcion[20], opcion2[20], usuario[20], char contrasenya[20], char nombre[25], dni[9], char email[25], char cuentaBancaria[20];
	float sueldo;
	int numVentas;
	sqlite3 *db;

	int result = sqlite3_open("BD/BD.sqlite", &db);
	if (result != SQLITE_OK)
	{
		printf("Error opening database\n");
	}

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	// SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr *)&server,
			 sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	// LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR)
	{
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	// ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr *)&client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
		   ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	// SEND and RECEIVE data (CLIENT/SERVER PROTOCOL)
	printf("Waiting for incoming commands from client... \n");

	do
	{
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		strcpy(opcion, recvBuff);

		if (strcmp(opcion, "login") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(usuario, recvBuff);
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(contrasenya, recvBuff);

			// COMPRADOR
			if (login(db, usuario, contrasenya) == 1)
			{
				strcpy(sendBuff, "comprador");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				do
				{
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					strcpy(opcion2, recvBuff);
					if (strcmp(opcion2, "comprarCoches") == 0)
					{
						// solicitar todos los coches a la bd
						// guardar array de coches que devuelve la bd

						// mandar numero de coches al cliente

						// mandar coches al cliente con un for

						// recibir matricula
						// recibir usuario
						// recibir nombreComprador
						// recibir fechaCompra
						// crear ticket y meterlo en la bd

						/* code */
					}
					if (strcmp(opcion2, "misCoches") == 0)
					{
						/* code */
					}
					if (strcmp(opcion2, "misTickets") == 0)
					{
						/* code */
					}
					if (strcmp(opcion2, "verPerfil") == 0)
					{
						/* code */
					}
				} while (strcmp(opcion2, "cerrarSesion") == 0);
			}
			// VENDEDOR
			if (login(db, usuario, contrasenya) == 2)
			{
				strcpy(sendBuff, "vendedor");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);

				do
				{
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					strcpy(opcion2, recvBuff);
					if (strcmp(opcion2, "verPerfil") == 0)
					{
						// solicitar todos los coches a la bd
						// guardar array de coches que devuelve la bd

						// mandar numero de coches al cliente

						// mandar coches al cliente con un for

						// recibir matricula
						// recibir usuario
						// recibir nombreComprador
						// recibir fechaCompra
						// crear ticket y meterlo en la bd

						/* code */
					}
					if (strcmp(opcion2, "verTickets") == 0)
					{
						/* code */
					}
				} while (strcmp(opcion2, "cerrarSesion") == 0);
			}
			else
			{
				strcpy(sendBuff, "erroneos");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}
		if (strcmp(opcion, "registro") == 0)
		{
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			strcpy(opcion2, recvBuff);

			if (strcmp(opcion2, "1") == 0)
			{
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(usuario, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasenya, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(nombre, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(email, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(cuentaBancaria, recvBuff);

				if (registrarComprador(db, usuario, contrasenya, nombre, dni, email, cuentaBancaria) == 1)
				{
					printf("Comprador agregado con exito a la BD");
				}
				else
				{
					printf("Error al agregar al comprador a la BD");
				}
			}
			if (strcmp(opcion2, "2") == 0)
			{
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(usuario, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(contrasenya, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(nombre, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(dni, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				strcpy(email, recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				sscanf(recvBuff, "%f.2", &sueldo);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				numVentas = iota(recvBuff);

				if (registrarVendedor(db, usuario, contrasenya, nombre, dni, email, sueldo, numVentas) == 1)
				{
					printf("Comprador agregado con exito a la BD");
				}
				else
				{
					printf("Error al agregar al comprador a la BD");
				}
			}
			else
			{
				// mando error a cliente
				strcpy(sendBuff, "error");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			}
		}
	} while (strcmp(opcion, "exit") != 0);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}