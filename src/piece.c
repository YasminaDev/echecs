#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "piece.h"

piece_t piece_creer(char * c, char * t){             /* Cree une piece */
	piece_t * p = malloc(sizeof(piece_t));	
	p->couleur = malloc(sizeof(char)*6);    /* Alloue de l'espace memoire pour 6 caracteres (BLANC ou NOIR)*/
	p->type = malloc(sizeof(char)*2);	/* Alloue de l'espace memoire pour 2 caracteres ( le type ) */
	strcpy(p->couleur,c);			/* copie la couleur c dans p */
	strcpy(p->type,t);			/* copie le type t dans p */
	return *p;
}

char piece_couleur(piece_t p){
	return *p.couleur;			/* Retourne la couleurs de la piece p */
}

piece_t piece_identifier(char * cc){		/* prend en entre un caractere et */ 
	return piece_creer("",cc);		/* Retourne le caractere d'une piece */
}
	

char piece_caractere(piece_t p){		/* Prend en entree une piece */
	return *p.type;				/* Retourne le type d'une piece */
}

void piece_afficher(piece_t p){
	printf("%s ",p.type);			/* prend en entree une piece et Affiche le type de la piece */ 
}

int cmp_piece (piece_t p1, piece_t p2){		/* prend en entree deux pieces et retourne 1 si les deux pieces ont le meme type */
	if(strcmp(p1.type,p2.type)==0)
		return 1;
	return 0;				/* Sinon retourne 0 */
}

void detruire_piece (piece_t p){		/* Detruit une piece en detruissant l'espace allouer pour la couleur et pour le type */ 
	free(p.couleur);
	free(p.type);
}
