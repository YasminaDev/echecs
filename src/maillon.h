#ifndef _MAILLON_H
#define _MAILLON_H
#include "piece.h"
#include "coordonnee.h"

struct maillon_s{			/* Cree structure maillon */
	piece_t val;			/* Avec une piece */
	coordonnee_t p;			/* Des coordonees */
	struct maillon_s * suivant;	/*  et un maillon suivant */
};
typedef struct maillon_s maillon_t;
 

maillon_t * creer_maillon (piece_t x, coordonnee_t c);

void detruire_maillon (maillon_t * m);

#endif
