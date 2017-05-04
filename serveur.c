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
# Impl魥ntation des m鴨odes pour le serveur
################################################################ 
 */  

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>		/* Signaux */
#include <netinet/in.h>		/* sockaddr_in */ 
#include "serveur.h"
#include "types.h"
#include "socket.h"

int main(int argc, char** argv) {
	int max_clients = NOMBRE_JOUEURS_MAX;
	int server_socket;
	int address_length; 
	int clients_socket[max_clients];
	int opt = TRUE;
	int i, activity, current_number = 0;
	int port;
	struct sockaddr_in server_address;	

	// Descripteurs
	fd_set readfds;

	if (argc != 3) {
		perror("Usage : ./serveur port affichage erreur");
		exit(1);
	}

	port = atoi(argv[1]);

	// Initialisation du serveur
	initServer(max_clients, &clients_socket, &server_socket, &server_address, &address_length, port);

	//sleep(1000);

	while(TRUE) {
		// Nettoyage des descripteurs
		FD_ZERO(&readfds);

		// Ajout du socket serveur a l'ensemble
		FD_SET(server_socket, &readfds);

		// Accepte ou non les demandes de connections du client
		activity = acceptConnexionFromClient(&readfds, &server_socket, &current_number, &clients_socket, &server_address, address_length, max_clients);
		switch(activity) {
			case -1:
				break;
			default:
				printf("Hello");
				break;
		}
	}

	return 0;
}

void sig_handler(int signal) {
	switch(signal) {
		case SIGINT:
			printf("Au revoir !");	
	}
}
