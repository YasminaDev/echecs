#ifndef _PIECE_H
#define _PIECE_H

typedef struct piece_s{		/* Cree une structure piece */
	char * couleur;		/* Avec couleur */
	char * type;		/* et un type */
} piece_t;

piece_t piece_creer(char * c, char * t);

char piece_couleur(piece_t p);

piece_t piece_identifier(char * cc);

char piece_caractere(piece_t p);

void piece_afficher(piece_t p);

int cmp_piece (piece_t p1, piece_t p2);

void detruire_piece (piece_t p);

#endif
