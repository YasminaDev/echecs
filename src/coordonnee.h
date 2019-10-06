#ifndef COORDONNEE_H
#define COORDONNEE_H

typedef struct coordonnee_s{					/*Definie une structure coordonee avec deux valeurs : x et y*/
	int x;
	int y;
} coordonnee_t;

coordonnee_t creer_coordonnee (int n, int m);			/*Cree coordonnee*/

void coordonnee_cpy (coordonnee_t * a, coordonnee_t b);		/*Copy coordonnee*/

int coordonnee_cmp (coordonnee_t c1, coordonnee_t c2);		/*Compare coordonnee*/

void afficher_coordonnee (coordonnee_t c); 			/*Affiche coordonnee*/

void detruire_coordonnee (coordonnee_t c);			/*Detruie coordonnee*/

#endif
