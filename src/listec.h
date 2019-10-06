#ifndef _LISTEC_H
#define _LISTEC_H
#include "maillonc.h"

struct listec_s{			/* Cree une structure listec */
	struct maillonc_s * premier;	/* Avec le premier maillon */
	struct maillonc_s * dernier;	/* Le dernier maillon */
	int taille;			/* Et la taille */
};
typedef struct listec_s listec_t;


listec_t * listec_initialiser();

int listec_vide (listec_t l);

int listec_cardinal (listec_t);

void listec_ajouter_debut (listec_t * l, coups_t x);

void listec_ajouter_fin (listec_t * l, coups_t x);

maillonc_t * listec_extraire_debut (listec_t * l);

maillonc_t * listec_extraire_fin (listec_t * l);

void listec_afficher (listec_t * l);

void listec_detruire (listec_t * l);

#endif
