#ifndef _COUPS_H
#define _COUPS_H
#include "coordonnee.h"


struct coups_s {					/* Cree une structure coups */
	coordonnee_t depart;				/* Avec une coordonnee de depart */
	coordonnee_t arrivee;				/* Une coordonee d'arrivee */
	int piece;					/* et une valeur boleene */
}; typedef struct coups_s coups_t;			/* Si piece= 1 alors une piece est capture si=0 alors non capture */

coups_t creer_coups(coordonnee_t d, coordonnee_t a, int x);		/* Permet de creeer un coups */


void coups_afficher(coups_t c);

void detruire_coups (coups_t c);

#endif
