#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listec.h"

listec_t * listec_initialiser(){					/* Initialise liste des coups */
	listec_t * l = malloc(sizeof(listec_t));		
	l->premier = NULL;						/* Premier de la liste initialiser a NULL */ 
	l->dernier = NULL;						/* Dernier de la liste initialiser a NULL */ 
	l->taille = 0;							/* Taille de la liste iniatialiser a 0 */
	return l;							/* Retourner la liste des coups */
}

int listec_vide (listec_t l){						/* Si la liste est vide retourne 1 sinon retourne 0 */ 
	if(l.taille == 0)
		return 1;
	return 0;
}

int listec_cardinal (listec_t l){					/* Retourne la taille de la liste */
	return l.taille;
}

void listec_ajouter_debut (listec_t * l, coups_t x){			/* Ajoute un coups au debut de la liste */
	maillonc_t  * nvo = creer_maillonc(x);				/* Cree un maillon */
	if(listec_vide(*l) == 1){					/* Si la liste est vide le premier et le dernier de la liste pointe vers le nouveau maillon */ 		
		l->premier = nvo;
		l->dernier = nvo;
	}
	else{
		nvo->precedent = NULL;					/* Sinon l'ajoute au debut de la liste */
		nvo->suivant = l->premier;
		l->premier->precedent = nvo;
		l->premier = nvo;
	}
	l->taille ++;							/* Augmente la taille de 1 */
}

void listec_ajouter_fin (listec_t * l, coups_t x){
	maillonc_t  * nvo = creer_maillonc(x);
	if(listec_vide(*l) == 1){
		l->premier = nvo;
		l->dernier = nvo;
	}
	else{
		nvo->suivant = NULL;
		l->dernier->suivant = nvo;
		nvo->precedent = l->dernier;
		l->dernier = nvo;
	}
	l->taille ++;
}

maillonc_t * listec_extraire_debut (listec_t * l){			/* Extrait le premier maillon de la liste */
	maillonc_t * res = NULL;					/* Cree un pointeur res qui va pointer le premier maillon de la liste et l'extrait */
	if(listec_cardinal(*l) > 0){
		res = l->premier;
		l->premier = res->suivant;
		res->suivant = NULL;
	 	l->taille --;						/* Taille de la liste diminue de 1 */
	}
	return res;
}

maillonc_t * listec_extraire_fin (listec_t * l){			/* Extrait le dernier maillon de la liste */
	maillonc_t * res = NULL;
	if(l->taille > 0){
		res = l->dernier;
		l->dernier = res->precedent;
		if(l->dernier != NULL)
			l->dernier->suivant = NULL;		
		res->precedent = NULL;
	 	l->taille --;
	}
	return res;
}

void listec_afficher (listec_t * l){					/* Affiche la liste des coups jouees */
	maillonc_t * tmp;
	printf("\nListe des coups joues :\n");
	for(tmp = l->premier; tmp != NULL; tmp = tmp->suivant)		/* Affiche la piece de chaque maillon parcouru */
		coups_afficher(tmp->val);
	printf("\n");
}

void listec_detruire (listec_t * l){					/* Detruit la liste */
	while(!listec_vide(*l))
		detruire_maillonc(listec_extraire_debut(l));
	free(l);
}
