#include <stdlib.h>
#include <stdio.h>
#include "coups.h"

coups_t creer_coups(coordonnee_t d, coordonnee_t a, int x){	/* Cree un coups */
	coups_t * c = malloc(sizeof(coups_t));			/* Alloue de l'espace pour c */
	coordonnee_cpy(&c->depart,d);				/* Copie coordonnee de depart dans c */
	coordonnee_cpy(&c->arrivee,a);				/* Copie coordonnee d'arrivee dans c */
	c->piece = x;						/* copie x (valeur boleene 0 ou 1 pour savoir si la piece est capturee) dans x */
 
	return *c;						/* Retourne c */
}


void coups_afficher(coups_t c){
	printf("Coordonnee de depart : ");
	afficher_coordonnee(c.depart);
	printf(". Coordonnee d'arrivee : ");
	afficher_coordonnee(c.arrivee);
	if(c.piece == 1)
		printf(". Une piece a etait capturee.\n");
	else
		printf(". Aucune piece n'a etait capturee.\n");
}

void detruire_coups (coups_t c){
	detruire_coordonnee(c.depart);
	detruire_coordonnee(c.arrivee);
	free(&c);
}
