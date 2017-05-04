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
# En-tête du module client (joueur)
############################################################
*/
 
#if !defined (_CLIENT_H_)
#define _CLIENT_H_

Message inscription();
void sendMessage(Message msg, int sockfd);

#endif
