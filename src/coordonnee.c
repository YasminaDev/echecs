#include <stdlib.h>
#include <stdio.h>
#include "coordonnee.h"

coordonnee_t creer_coordonnee(int n, int m){			/*Cree une coordonnee de l'echéquier*/
	coordonnee_t *co = malloc(sizeof(coordonnee_t));	/* Aloue de l'espace */
	co->x = n;						/* Affecte la valeur n a coordonnee */
	co->y = m;						/*Affecte la valeur m a coordonnee*/
	return *co;						/*Retourne la coordonnee*/
}

void coordonnee_cpy(coordonnee_t * a, coordonnee_t b){ 		/* Copie une coordonnee b dans a */
	a->x = b.x;
	a->y = b.y;
}

int coordonnee_cmp (coordonnee_t c1, coordonnee_t c2){	/* Compare deux coordonnees */
	if(c1.x == c2.x && c1.y == c2.y)	
		return 1;			/* Retourne 1 si elles ont les même coordonnees */
	return 0;				/* Sinon retourne 0 */
}

void afficher_coordonnee (coordonnee_t c){
	printf("(%d,%d)",c.x,c.y);		/* Affiche les coordonnees x et y de la piece */
}

void detruire_coordonnee (coordonnee_t c){	/*Libere l'espace alouer pour une coordonne*/
	free(&c);				
}
