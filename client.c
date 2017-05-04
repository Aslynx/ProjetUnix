/*
#############################################################
# Projet Réseau - Papayoo 
# 
# Serie 1
# Etudiant 1 : CHRISTODOULOU Nicolas
#   login : nchrist15
# Etudiant 2 : PIERRE Anthony
#   login : apierre15
#  
# Implémentation du module client (joueur)
############################################################
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
#include "client.h" 

Joueur joueur;

int main (int argc, char** argv) {
	int port;
	int sockfd; 
	struct sockaddr_in addr_serv;
	struct hostent * host;

	char buffer[256];

	if (argc < 3) {
		perror("Usage : ./client port ipaddress\n");
		exit(20);
	}

	port = atoi(argv[1]);
	host = gethostbyname(argv[2]);

	if (host == NULL) {
		perror("Pas de serveur a cette adresse ip\n");
		exit(21);
	}

	// Création du socket du client
	//initClientSocket(&sockfd, port, host, &addr_serv);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("client_socket failed\n");
		exit(31);
	}

	bzero((char *) &addr_serv, sizeof(addr_serv));
	(addr_serv).sin_family = AF_INET;
	//(*server_address).sin_addr.s_addr = INADDR_ANY;
	bcopy((char *) host->h_addr,(char *) &addr_serv.sin_addr.s_addr, host->h_length);
	(addr_serv).sin_port = htons(port);

	// Inscription du client
	Message msgInscription = inscription();
	struct timeval tv = {TIMER, 0};

	// Connexion au serveur
	connectClient(&sockfd, &addr_serv); 

	// Envoi du message d'inscription
	sendMessage(msgInscription, sockfd);

	return 0;
}

Message inscription() {
	char message[256];
	char buffer[256];
	int length;
	Message msgInscription;

	strncpy(message, "Veuillez choisir votre pseudo :\n", 255);
	printf("%s", message);

	if ((length = read(0, buffer, 255)) > 0) {
		strcpy(joueur.nom, buffer);
		msgInscription.type = INSCRIPTION;
		buffer[length-1] = '\0';
		strncpy(msgInscription.message, buffer, length); 
		return msgInscription;
	} else {
		exit(22);
	} 
}

void sendMessage(Message msg, int sockfd) {
	printf("Send\n");
	SYS(send(sockfd, &msg, sizeof(Message), 0));
}
