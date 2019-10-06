#ifndef _LISTE_H
#define _LISTE_H
#include "maillon.h"

struct liste_s{					/* Cree une structure liste */
	struct maillon_s * premier;		/* Avec le premier maillon de la liste */
	struct maillon_s * dernier;		/* Le dernier maillon de la liste  */
	int taille;				/* et la taille de la liste */
};
typedef struct liste_s liste_t;


liste_t * liste_initialiser();						/* Initialise une liste a  */

int liste_vide (liste_t l);						/* Verifie si la liste est vide */

int liste_cardinal (liste_t);						/* Affiche taille de la liste */

void liste_ajouter_debut (liste_t * l, piece_t x, coordonnee_t co);	/* Ajoute un maillon au debut de la liste */

void liste_ajouter_fin (liste_t * l, piece_t x, coordonnee_t co);	/* Ajoute un maillon a la fin de la liste */ 

maillon_t * liste_extraire_debut (liste_t * l);				/* Extrait premier maillon de la liste */

void liste_afficher (liste_t * l);					/* Affiche liste */

int liste_appartient (liste_t l, piece_t x);				/* Verifie si la piece appartient a liste */

void liste_supprimer (liste_t * l, piece_t x);				/* Supprime une piece de la liste */

void liste_detruire (liste_t * l);					/* Detruit liste */

#endif
