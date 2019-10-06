#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

liste_t * liste_initialiser(){				/* Initialise une liste */
	liste_t * l = malloc(sizeof(liste_t));		/* Alloue de l'espace pour une liste */
	l->premier = NULL;				/* Le premier maillon de la liste l initialise a NULL */
	l->dernier = NULL;				/* Le dernier maillon de la liste l initialise a NULL */
	l->taille = 0;					/* La taille de la liste est egale a 0 */
	return l;					/* Retourne la liste l */
}

int liste_vide (liste_t l){				/* Verifie si la liste est vide */
	if(l.taille == 0)
		return 1;				/* Retourne 1 si elle est vide */
	return 0;					/* Sinon retourne 0 */
}

int liste_cardinal (liste_t l){
	return l.taille;				/* Retourne la taille de la liste */
}

void liste_ajouter_debut (liste_t * l, piece_t x, coordonnee_t co){	/* Ajoute un maillon au debut de la liste */
	maillon_t  * nvo = creer_maillon(x,co);				/* Alloue de l'espace pour un maillon */
	if(liste_vide(*l) == 1){					/* Si la liste est vide */
		l->premier = nvo;					/* Le premier maillon de la liste l pointe vers nvo */
		l->dernier = nvo;					/* Le dernier maillon de la liste l pointe vers nvo */
	}
	else{								/* Sinon si la liste n'est pas vide */
		nvo->suivant = l->premier;				/* Le maillon suivant de nvo pointe vers le 1er maillon de l */ 
		l->premier = nvo;					/* Le premier maillon de la liste l pointe vers nvo */
	}
	l->taille ++;							/* La taille est augmentee de 1 */
}

void liste_ajouter_fin (liste_t * l, piece_t x, coordonnee_t co){	/* Ajoute un maillon a la fin de la liste */
	maillon_t  * nvo = creer_maillon(x,co);
	if(liste_vide(*l) == 1){
		l->premier = nvo;
		l->dernier = nvo;
	}
	else{
		nvo->suivant = NULL;					/* Le maillon suivant de nvo pointe vers NULL */ 
		l->dernier->suivant = nvo;				/* Le maillon suivant du dernier de la liste pointe vers nvo */ 
		l->dernier = nvo;					/* Le dernier maillon de la liste l pointe vers nvo */
	}
	l->taille ++;
}

maillon_t * liste_extraire_debut (liste_t * l){				/* Extrait le premier maillon de la liste */
	maillon_t * res = NULL;						/* Cree un maillon res NULL */ 
	if(liste_cardinal(*l) > 0){					/* Si la taille de la liste est superieure a 0 */
		res = l->premier;					/* Le maillon res pointe vers le premier de la liste */
		l->premier = res->suivant;				/* Le premier de la liste pointe vers le suivant de res */
		res->suivant = NULL;					/* la maillon suivant de res egale a NULL */
	 	l->taille --;						/* Taille de la liste diminue de 1 */
	}
	return res;							/* Retourne le nouveau maillon */
}


void liste_afficher (liste_t * l){					/* Affiche liste */
	maillon_t * tmp;
	printf("\nListe des pieces captures :\n");
	for(tmp = l->premier; tmp != NULL; tmp = tmp->suivant){		/* Pour maillon tmp pointe vers premier de liste,tmp=suivant de tmp */
		piece_afficher(tmp->val);				/* Affiche la piece */	
		printf("   ");
		afficher_coordonnee(tmp->p);
		printf("\n");
	}
	printf("\n");	
}

int liste_appartient (liste_t l, piece_t x){				/* Verifie si la piece x appartient a la liste l */
	maillon_t * tmp;
	for(tmp = l.premier; tmp != NULL; tmp = tmp->suivant){
		if(strcmp(tmp->val.couleur,x.couleur)==1 && strcmp(tmp->val.type,x.type)==1)	/* Compare si couleur et type de la valeur du maillon tmp et de la piece x sont egale */
			return 1;								/* Retourne 1 si appartient */
	}
	return 0;										/* Sinon retourne 0 */
}


void liste_supprimer (liste_t * l, piece_t x){				/* Supprime la piece x de la liste l */
	maillon_t * tmp = l->premier;
	maillon_t * ancien = l->premier;
	while(tmp != NULL){						/* Tant que maillon tmp different de NULL */
		if(strcmp(tmp->val.couleur,x.couleur)==1 && strcmp(tmp->val.type,x.type)==1){ /* Si meme piece */
			ancien->suivant = tmp->suivant;		
			tmp = tmp->suivant;
			l->taille--;	/* Extrait le maillon */
		}		
		else{				/* Sinon le tmp pointe vers le maillon suivant */
			ancien = tmp;
			tmp = tmp->suivant;
		}
	}
}

void liste_detruire (liste_t * l){					/* Detruit la liste */
	while(!liste_vide(*l))						/* Tant que la liste n'est pas vide */
		detruire_maillon(liste_extraire_debut(l));		/* On extrait le maillon puis on le detruit */
	free(l);							/* On realise un free pour liberer l'espace que nous avons allouee */
}
