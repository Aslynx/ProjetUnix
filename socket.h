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
# Définition des m鴨odes pour l'utilisation des sockets 
################################################################ 
*/  

#if ! defined (_SOCKET_H_)
#define _SOCKET_H_

void initServer(int, int (*)[], int *, struct sockaddr_in * , int *, int);

int acceptConnexionFromClient(fd_set *, int *, int *, int (*)[], struct sockaddr_in *, int, int);

void initClientSocket(int *, int, struct hostent *, struct sockaddr_in *);

void connectClient(int *, struct sockaddr_in *);

#endif
