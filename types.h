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
# Définition des structures utilisées pour une partie de Papayoo 
################################################################ 
*/  

#if ! defined (_TYPES_PAPAYOO_H_)
#define _TYPES_PAPAYOO_H_

// Types messages
#define INSCRIPTION 1
#define INSCRIPTION_REUSSIE 2
#define INSCRIPTION_ECHOUEE 3
#define DEMARRAGE_PARTIE 4
#define DEMARRAGE_MANCHE 5
#define DISTRIBUTION_CARTES 6
#define DONNE_CARTES 7
#define REDISTRIBUTION_CARTES 8
#define DEMARRAGE_TOUR 9
#define DEMANDE_CARTE 10
#define JOUE_CARTE 11
#define PLUS_DE_CARTE 12
#define ENVOIE_PLI 13
#define COMPTE_POINTS 14
#define DONNE_POINTS 15
#define GAGNANT_PARTIE 16
#define GAGNE_PARTIE 17
#define PARTIE_ARRETEE 18
#define FIN_PARTIE 19
#define ELIMINE 20
#define TIMER 30

#define TRUE 1
#define FALSE 0 
#define NOMBRES_MANCHES 3
#define NOMBRE_JOUEURS_MAX 4
 
#define SYS(call) ((call) == -1) ? (perror(#call ": ERROR"), exit(1)) : 0

typedef struct carte { 
    int valeur; 
    enum couleur {COEUR, CARREAU, TREFLE, PIQUE, PAYOO}Couleur; 
} Carte; 
 
typedef struct message { 
    int type; 
    char message[1024]; 
    Carte cartes[5]; 
} Message; 

typedef struct joueur {
    char nom[50];
    int points;
    // A remplir au fur et a mesure du projet
} Joueur;

#endif 
