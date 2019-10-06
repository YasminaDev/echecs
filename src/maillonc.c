#include <stdlib.h>
#include <stdio.h>
#include "maillonc.h"

maillonc_t * creer_maillonc (coups_t x){     		/* Cree maillon des coups jouer */ 
	maillonc_t * m = malloc(sizeof(maillonc_t));
	m->val = x;					/* val du maillon m prend la valeurs de la piece x */
	m->suivant = NULL;				/* Le maillon suivant de m prend la valeurs Null */
	m->precedent = NULL;				/* Le maillon precedent de m prend la valeurs Null */
	return m;
}

void detruire_maillonc (maillonc_t * m){ /* Detruit le maillon de coups */
	detruire_coups(m->val);
	free(&m->val);
	free(m);
}
