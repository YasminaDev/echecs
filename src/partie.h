#ifndef _PARTIE_H
#define _PARTIE_H
#include "liste.h"
#include "listec.h"

typedef struct partie_s{
	piece_t echiquier[8][8];		/*creer le tableau de piece (l'echiquier)*/
	liste_t * pieces_capturees;
	listec_t * coups_joues;
	int joueur; /* BLANC = 0 et NOIR = 1 */
} partie_t;

int case_vide(piece_t p);

void modifier_case(partie_t * pt, piece_t pc, coordonnee_t co);

void changer_joueur(partie_t * pt);

void afficher_echiquier(partie_t * pt);

void capt_piece(partie_t * p, coordonnee_t pc);

int deplacement_pion(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_tour(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_cavalier(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_fou(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_roi(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_reine(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement_valide(partie_t * pt, coordonnee_t a, coordonnee_t d);

int deplacement(partie_t * pt, coordonnee_t a, coordonnee_t d);

void annuler_deplacement(partie_t * pt);

coordonnee_t saisie_case();

partie_t * partie_creer();

void partie_detruire(partie_t * p);

void plateau_sauvegarder(partie_t * p, char * nom);

void partie_sauvegarder(partie_t * p, char * nom);

void plateaux_charger(partie_t * pt, char * nom);

partie_t * partie_charger(char * nom);

partie_t * partie_nouvelle();

void partie_jouer();

listec_t * replay_charger(char * nom);

void replay_jouer(char * nom);

#endif
