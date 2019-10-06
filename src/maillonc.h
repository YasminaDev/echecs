#ifndef _MAILLONC_H
#define _MAILLONC_H
#include "coups.h"

struct maillonc_s {		/* Cree structure maillon des coups jouer*/
	coups_t val;		/* Avec une piece */
	struct maillonc_s * suivant;/*   un maillon suivant */
	struct maillonc_s * precedent;/*  et un maillon precedent */
}; 
typedef struct maillonc_s maillonc_t;
 
maillonc_t * creer_maillonc (coups_t x);

void detruire_maillonc (maillonc_t * m);

#endif
