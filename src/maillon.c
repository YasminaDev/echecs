#include <stdlib.h>
#include <stdio.h>
#include "maillon.h"

maillon_t * creer_maillon (piece_t x, coordonnee_t c){ /* Cree un maillon */
	maillon_t * m = malloc(sizeof(maillon_t));	/* Alloue de l'espace pour un maillon m */
	coordonnee_cpy(&m->p,c);  /* Copie coordonees de c dans  m */
	m->val = x;		/* val du maillon m prend la valeurs de la piece x */
	m->suivant = NULL;	/* Le maillon suivant de m prend la valeurs Null */
	return m;
}

void detruire_maillon (maillon_t * m){ /* Detruit le maillon */ 
	detruire_piece(m->val);
	detruire_coordonnee(m->p);
	free(m);
}
