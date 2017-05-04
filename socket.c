/*  
################################################################ 
# Projet Réseau - Papayoo  
#  
# Serie 1 
# Etudiant 1 : CHRISTODOULOU Nicolas 
#	login : nchrist15
# Etudiant 2 : PIERRE Anthony  
#	login : apierre15
#
# Impl魥ntation des m鴨odes pour l'utilisation des sockets
################################################################ 
 */  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include "types.h"
#include "socket.h"

void initServer(int max_clients, int (* clients_socket)[], int * server_socket, struct sockaddr_in * server_address, int * address_length, int port) {
	int i;
	// Initialisation des sockets clients
	for(i = 0; i < max_clients; i++) {
		(*clients_socket)[i] = 0;
	}

	// Initialisation du socket serveur
	if ((*server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("server_socket failed");
		exit(30);	
	}

	(*server_address).sin_family = AF_INET;
	(*server_address).sin_addr.s_addr = INADDR_ANY;
	(*server_address).sin_port = htons(port);

	// Assignation de l'adresse du port au socket
	SYS(bind(*server_socket, (struct sockaddr *) (server_address), sizeof(*server_address)));

	// Precise le nombre maximum de connections a "ecouter"
	SYS(listen(*server_socket, max_clients));

	// Accepte les connections entrantes
	*address_length = sizeof(server_address);

	printf("En attente ...\n");
}

int acceptConnexionFromClient(fd_set * readfds, int * server_socket, int * current_number, int (* clients_socket)[], struct sockaddr_in * server_address, int address_length, int max_clients) {
	// Variables utilisées uniquement dans la méthode
	int i, desc, waiting, socket_to_add;
	int max_desc;
	struct timeval timer;
	timer.tv_sec = TIMER;
	timer.tv_usec = 0;

	printf("Hello\n");
	// Ajout de sockets enfants à l'ensemble
	for (i = 0; i < max_clients; i++) {
		// Récupération du descripteur
		desc = (* clients_socket)[i];

		printf("desc : %d\n", desc);
		// Si le socket est valide, on l'ajoute à l'ensemble
		if (desc > 0) {
			FD_SET(desc, readfds);
		}

		// On garde la plus grande valeur du descripteur pour faire le select
		if (desc > max_desc) {
			max_desc = desc;
		}
	}


	// Lancement du timer
	SYS(waiting = select((max_desc)+1, readfds, NULL, NULL, &timer));

	printf("wait : %d\n", waiting);

	switch(waiting) {
		case 0:
			printf("Timer écoulé\n");
			return -1;
		default:
			printf("Hello2\n");
			// Nouvelle connection
			if (FD_ISSET(*server_socket, readfds)) {
				SYS(socket_to_add = accept(*server_socket, (struct sockaddr *) server_address, (socklen_t *) &address_length));

				printf("Nouvelle connection\n");

				// Ajout du client
				for (i = 0; i < max_clients; i++) {
					if ((*clients_socket)[i] == 0) {
						(*clients_socket)[i] = socket_to_add;
						FD_SET(socket_to_add, readfds);
						break;
					}
				}
			}

			return 1;
	}
}

void initClientSocket(int * sockfd, int port, struct hostent * host, struct sockaddr_in * addr_serv) {

	// Initialisation du socket client
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("client_socket failed\n");
		exit(31);
	}

	bzero((char *) addr_serv, sizeof(*addr_serv));
	(*addr_serv).sin_family = AF_INET;
	//(*server_address).sin_addr.s_addr = INADDR_ANY;
	bcopy((char *) host->h_addr,(char *) addr_serv->sin_addr.s_addr, host->h_length);
	(*addr_serv).sin_port = htons(port);
}

void connectClient(int * sockfd, struct sockaddr_in * addr_serv) {

	if ((connect(*sockfd, (struct sockaddr*) addr_serv, sizeof(addr_serv))) == 0) {
		perror("client connect failed\n");
		exit(32);
	} 
}

