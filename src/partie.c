#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "partie.h"

int case_vide(piece_t p){					/*verifie si la case est vide*/
	piece_t pc = piece_creer(".",".");			/*une case vide correspond à la piece de couleur "." et de type "."*/
	if(cmp_piece(p,pc)==1)					/*si la piece qui est dans la case est vide la fonction retourne 1*/
		return 1;					/*sinon 0*/
	return 0;
}

void modifier_case(partie_t * pt, piece_t pc, coordonnee_t co){	 /*Elle prend en parametre la piece a mettre dans les coordonnes donner*/
	 pt->echiquier[co.x][co.y] = pc;			/*Elle va aux cordonnees, donner, dans l'echiquier et met la piece voulu*/
}

void changer_joueur(partie_t * pt){				
	if(pt->joueur == 1)					/* Si le joueur est noir alors il passe au blanc */
		pt->joueur = 0;		
	else							/* Sinon l'inverse */
		pt->joueur = 1;					
}

void afficher_echiquier(partie_t * pt){
	int i, j;
	printf("\n                  NOIR\n\n");         		/*Coter du joueur noir*/
	printf("    0    1    2    3    4    5    6    7"); 		/*Pour les coordonnees y*/
	for(i=0;i<8;i++){						/*A chaque ligne on saute de ligne et on met une par une les coordonees x*/
		printf("\n\n");
		printf("%d   ",i);
		for(j=0;j<8;j++){					/*For imbriquer dans un for pour parcourir toute les cases de l'echiquier*/
			piece_afficher(pt->echiquier[i][j]);		/*On affiche la piece qui est dans la case*/
			printf("   ");					/* Puis un peu d'espace pour separer chaque piece */
		}
	}
	printf("\n\n                  BLANC\n");			/*Coter du joueur blanc*/
}

void capt_piece(partie_t * pt, coordonnee_t pc){
	piece_t v = piece_creer(".",".");				/*On creer la case vide à mettre à la place de la piece capturer*/
	piece_t p = pt->echiquier[pc.x][pc.y];				/*On recupere la piece à capturer dans l'echiquier*/
	modifier_case(pt,v,pc);						/*On met une case vide aux coordonnees de la piece capturer*/
	liste_ajouter_debut(pt->pieces_capturees,p,pc);			/*Et on rajoute à la liste des piece capturer la piece capturer avec les coordonnees de son ancien emplacement*/
}
	
int deplacement_pion(partie_t * pt, coordonnee_t a, coordonnee_t d){ /*Verifie les deplacement du pion si c'est valide elle retourne 1, si une piecce est capturer en meme temps elle retourne 2 sinon 0*/
	int i;
	if(pt->joueur == 1){								/* Si c'est le noir qui joue*/
		if(d.x == 1){								/*Si il n'a encore jamais toucher à se pion*/
			if(d.y == a.y){							/*Si il se deplace tout droit */
				if((a.x > (d.x +2)) || (a.x < d.x))			/*Si le pion avance plus de 2 fois ou recule, c'est invalide*/
					return 0;
				if((d.x +1) == a.x){					/*Si il ne se deplace que d'une case*/
					if(case_vide(pt->echiquier[a.x][a.y]) == 0)		/*si la case n'est pas vide, c'est invalide*/
						return 0;
					return 1;						/*si elle n'est pas vide, valide !*/
				}
				if((d.x +2) == a.x){					/*Si le pion avance de 2 case*/
					for(i=(d.x +1);i<=a.x;i++){			/*On verifie les 2 case*/
						if(case_vide(pt->echiquier[i][a.y]) == 0)
							return 0;
					}
					return 1;
				}
			}
			if((d.x +1) == a.x){						/*Si il se deplace en diagonal */
				if(((d.y +1) == a.y) || ((d.y -1) == a.y)){		/*Si il ne se deplace que d'une seule case*/
					if(case_vide(pt->echiquier[a.x][a.y])==0){	/*Si il y a un pion dans la case*/
						if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)  /*Si le pion est noir, invalide*/
							return 0;
						else{							/*Si le pion est blanc, valide */
							capt_piece(pt,creer_coordonnee(a.x,a.y));	/*et on capture les piece presente dans la case*/
							return 2;					/*et on retoourne 2 pour prevenir qu'une piece à etait capturer*/
						}
					}
					return 0;							/*Si la case est vide alors deplacement invalide*/
				}
				return 0;						/*Si il va plus loin qu'une case, invalide !*/
			}
		}
		else{									/*Si le pion à deja etait deplacer au moin une fois, alors on procede au meme verification effectuer precedement*/ 
			if((abs(a.x-d.x) != 1) && (abs(d.y-a.y) != 1))			/*Mais cette fois le pion pourra se deplacer que d'une seul case*/
				return 0;
			if(d.y == a.y){
				if((a.x > (d.x +1)) || (a.x < d.x))
					return 0;
				if((d.x +1) == a.x){
					if(case_vide(pt->echiquier[a.x][a.y]) == 0)
						return 0;
					return 1;
				}
			}
			if((d.x +1) == a.x){
				if(((d.y +1) == a.y) || ((d.y -1) == a.y)){
					if(case_vide(pt->echiquier[a.x][a.y])==0){
						if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)
							return 0;
						else{
							capt_piece(pt,creer_coordonnee(a.x,a.y));
							return 2;
						}
					}
					return 0;
				}
				else
					return 0;
			}
		}
	}
	else{										/*On procede exactement de la meme facon que le joueur noir*/
		if(d.x == 6){								/*Mais pour les deplacement on ira de bas en haut, ici 6 correspond a l'emplacement d'orgine d'un pion blanc*/
			if(d.y == a.y){	
				if((a.x < (d.x -2)) || (a.x > d.x))
					return 0;
				if((d.x -1) == a.x){
					if(case_vide(pt->echiquier[a.x][a.y]) == 0)
						return 0;
					return 1;
				}
				if((d.x -2) == a.x){
					for(i=(d.x -1);i>=a.x;i--){
						if(case_vide(pt->echiquier[i][a.y]) == 0)
							return 0;
						return 1;
					}
				}
			}
			if((d.x -1) == a.x){
				if(((d.y +1) == a.y) || ((d.y -1) == a.y)){
					if(case_vide(pt->echiquier[a.x][a.y])==0){
						if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)
							return 0;
						else{
							capt_piece(pt,creer_coordonnee(a.x,a.y));
							return 2;
						}
					}
					return 0;
				}
				return 0;
			}
		}
		else{
			if((abs(a.x-d.x) != 1) && (abs(d.y-a.y) != 1))
				return 0;
			if(d.y == a.y){
				if((a.x < (d.x -1)) || (a.x > d.x))
					return 0;
				if((d.x -1) == a.x){
					if(case_vide(pt->echiquier[a.x][a.y]) == 0)
						return 0;
					return 1;
				}
			}
			if((d.x -1) == a.x){
				if(((d.y +1) == a.y) || ((d.y -1) == a.y)){
					if(case_vide(pt->echiquier[a.x][a.y])==0){
						if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
							return 0;
						else{
							capt_piece(pt,creer_coordonnee(a.x,a.y));
							return 2;
						}
					}
					return 0;
				}
				return 0;
			}
		}
	}
	return 0;								/*Si se n'est ni un joueur blanc ni un joueur noir, FAUX*/
}

int deplacement_tour(partie_t * pt, coordonnee_t a, coordonnee_t d){		/* Meme principe que pion pour tour (et toute les autres piece)*/
	int i;
	if(a.y != d.y && a.x != d.x)						/*Si la tour ne se deplace ni verticalement ni horizontalement, alors c'est invalide*/ 
		return 0;
	if((d.y+1 == a.y) || (d.y-1 == a.y) || (d.x+1 == a.x) || (d.x-1 == a.x)){	/*Si la tour ne se deplace que d'une seul case on verifie directement la case d'arrive*/
		if(case_vide(pt->echiquier[a.x][a.y]) == 0){				/*Meme verification que les autres pieces*/
			if(pt->joueur == 1){
				if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)
					return 0;
				else{
					capt_piece(pt,creer_coordonnee(a.x,a.y));
					return 2;
				}
			}
			else{
				if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
					return 0;
				else{
					capt_piece(pt,creer_coordonnee(a.x,a.y));
					return 2;
				}
			}
		}
	}
	if(a.y == d.y){									/*Si elle se deplace verticalement on verifie chaque case sauf la derniere*/
   	 	if(a.x > d.x){
			for(i=(d.x + 1);i<a.x;i++){
				if(case_vide(pt->echiquier[i][d.y]) == 0)
					return 0;
			}
		}
		if(a.x < d.x){
			for(i=(d.x - 1);i>a.x;i--){
				if(case_vide(pt->echiquier[i][d.y]) == 0)
					return 0;
			}
		}
	}
	if(a.x == d.x){									/*Meme chose pour horizontalement*/
		if(a.y > d.y){
			for(i=(d.y + 1);i<a.y;i++){
				if(case_vide(pt->echiquier[d.x][i]) == 0)
					return 0;
			}
			return 1;
		}
		if(a.y < d.y){
			for(i=(d.y - 1);i>a.y;i--){
				if(case_vide(pt->echiquier[d.x][i]) == 0)
					return 0;
			}
		}
	}
	if(case_vide(pt->echiquier[a.x][a.y]) == 0){	/*Apres que toute les case parcourue soit vide on verifie la case d'arrivee */
		if(pt->joueur == 1){                                    /*joueur noir*/
			if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)          /*si la case d'arriver contient une piece noir, faux*/
				return 0;
			else{
				capt_piece(pt,creer_coordonnee(a.x,a.y));               /*Sinon on capture*/
				return 2;                                               /*et on retourne 2 pour dire qu'une piece est capt*/
			}
		}
		else{                                                   /*pour le joueur blanc meme verification*/
			if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
				return 0;
			else{
				capt_piece(pt,creer_coordonnee(a.x,a.y));
				return 2;
			}
		}
	}
	return 1;                                       /* Si la case est vide on retourne 1, puisque le deplacement est valide */
}

int deplacement_cavalier(partie_t * pt, coordonnee_t a, coordonnee_t d){
	if((abs(a.y - d.y) == 1) && (abs(a.x-d.x) == 2)){       /* Si le cavalier se deplace verticalement de 2 case est horitalement d'une case*/
		if(case_vide(pt->echiquier[a.x][a.y])==0){      /*Si la case d'arriver n'est pas vide*/ 
			if(pt->joueur == 1){                           /*Joueur noir*/
				if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)           /*Si la case d'arriver contient une piece noir*/
					return 0;                                       /*Alors le deplacement est invalide*/
	 			else{                                                           /*Si elle contient une piece blanche*/
					capt_piece(pt,creer_coordonnee(a.x,a.y));               /*On capture donc la piece*/
					return 2;                               /*Et on retourne 2 pour prevenir qu'une piece à été capturé*/
				}
			}
			else{                                          /*Meme chose pour un joueur blanc*/
			    	if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
	   				return 0;
				else{
					capt_piece(pt,creer_coordonnee(a.x,a.y));
					return 2;
				}
			}
		}
		return 1;                                              /*Si la case est vide le deplacement est valide*/
	}
	if((abs(a.x - d.x) == 1) && (abs(a.y-d.y) == 2)){        /*Meme chose pour le deplacement horizontale de 2 case puis verticale d'une case*/
   	        if(case_vide(pt->echiquier[a.x][a.y])==0){
                        if(pt->joueur == 1){
				if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)
					return 0;
		 		else{  	
					capt_piece(pt,creer_coordonnee(a.x,a.y));
					return 2;
				}
			}
			else{
			    	if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
		   			return 0;
				else{
					capt_piece(pt,creer_coordonnee(a.x,a.y));
					return 2;
				}
			}
		}
		return 1;
	}
	return 0;                               /*Sinon le deplacement n'est pas valide*/
}

int deplacement_fou(partie_t * pt, coordonnee_t a, coordonnee_t d){
	int i= d.x;
	int j= d.y;
	if(abs(a.x - d.x) != abs(a.y - d.y))                    /*verifie que c'est un deplacement en diagonale*/
		return 0;                                               /*si sa ne l'est pas c'est invalide et donc on retourne 0*/
	if(a.x > d.x && a.y > d.y){                         /*Si le fou va en diagonale en bas à droite*/
		while(i < a.x-1 && j < a.y-1){                  /*On parcours toute les case sauf la derniere*/
			i++;j++;
			if(case_vide(pt->echiquier[i][j]) == 0)
				return 0;
		}
	}
	if(a.x < d.x && a.y < d.y){                         /*deplacement en bas à gauche*/
		while(i > a.x+1 && j > a.y+1){
			i--;j--;
			if(case_vide(pt->echiquier[i][j]) == 0)
				return 0;
		}
	}
	if(a.x < d.x && a.y > d.y){                         /*deplacement en haut à droite*/
		while(i > a.x+1 && j < a.y-1){
			i--;j++;
			if(case_vide(pt->echiquier[i][j]) == 0)
				return 0;
		}
	}
	if(a.x > d.x && a.y < d.y){                         /*deplacement en haut à gauche*/
		while(i < a.x-1 && j > a.y+1){
			i++;j--;
			if(case_vide(pt->echiquier[i][j]) == 0)
				return 0;
		}
	}
	if(case_vide(pt->echiquier[a.x][a.y]) == 0){        /*Puis on verifie la case darriver comme pour la tour*/
		if(pt->joueur == 1){
			if(strcmp(pt->echiquier[a.x][a.y].couleur,"NOIR")==0)
				return 0;
			else{ 	 	
				capt_piece(pt,creer_coordonnee(a.x,a.y));
				return 2;
			}
		}
		else{
			if(strcmp(pt->echiquier[a.x][a.y].couleur,"BLANC")==0)
				return 0;
			else{
				capt_piece(pt,creer_coordonnee(a.x,a.y));
				return 2;
			}
		}
	}
	return 1;
}

int deplacement_roi(partie_t * pt, coordonnee_t a, coordonnee_t d){
	int i= d.x;
	int j= d.y;
	if(abs(a.x - d.x) != 1 && abs(a.y - d.y) != 1 )         /*Verifie que le roi ne doit bouger qu'une d'une seule case*/
		return 0;
	if(a.x == d.x && a.y < d.y){                    /*Si il va à gauche*/
		j--;                                       /*meme verification que les autres piece*/
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}	
		}
		return 1;
	}
	if(a.x == d.x && a.y > d.y){                /*deplacement à droite*/
		j++;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}	
		}
		return 1;
	}
	if(a.x > d.x && a.y == d.y){            /*deplacement vers le bas*/
		i++;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}	
		}
		return 1;
	}
	if(a.x < d.x && a.y == d.y){            /*vers le haut*/
		i--;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
		}
		return 1;
	}
	if(a.x < d.x && a.y < d.y){             /*en haut à gauche*/
		j--;
		i--;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
		}
		return 1;
	}
	if(a.x > d.x && a.y < d.y){             /*en bas à gauche*/
		j--;
		i++;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
					
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}	
		}
		return 1;
	}
	if(a.x < d.x && a.y > d.y){         /*en haut à droite*/
		j++;
		i--;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
		}
		return 1;
	}
	if(a.x > d.x && a.y > d.y){        /*en bas à droite*/
		j++;
		i++;
		if(case_vide(pt->echiquier[i][j]) == 0){
				if(pt->joueur == 1){
					if(strcmp(pt->echiquier[i][j].couleur,"NOIR")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
				}
				else{
					if(strcmp(pt->echiquier[i][j].couleur,"BLANC")==0)
						return 0;
					else{	
						capt_piece(pt,creer_coordonnee(i,j));
						return 2;
					}
						
				}		
		}
		return 1;
	}
	return 0;
}

int deplacement_reine(partie_t * pt, coordonnee_t a, coordonnee_t d){   /*le deplacement de la reine correspond au deplacement du fou & du roi*/
	int i = deplacement_fou(pt,a,d);                /*on recupere le resultat de deplacement fou*/
	if(i==0)                                        /*si il n'est pas valide*/
		return deplacement_tour(pt,a,d);            /*on retourne le resultat de tour*/
	return i;                                       /*si deplacement fou est valide alors on retourne son resultat 1 ou 2*/
}

int deplacement_valide(partie_t * pt, coordonnee_t a, coordonnee_t d){
	piece_t p = pt->echiquier[d.x][d.y];
	if((pt->joueur==1) && (strcmp(pt->echiquier[d.x][d.y].couleur,"BLANC")==0)) /*si le joueur est noir et il veux deplacer une piece blanche*/
		return 0;                                                                   /*Alors c'est faux*/
	if((pt->joueur==0) && (strcmp(pt->echiquier[d.x][d.y].couleur,"NOIR")==0))  /*meme chose pour le joueur blanc*/
		return 0;
	if(strcmp(p.type,"f")==0 || strcmp(p.type,"F")==0)             /*si la piece est un fou*/ 
		return deplacement_fou(pt,a,d);                     /*alors on retourne le resultat de deplacement fou*/
	if(strcmp(p.type,"r")==0 || strcmp(p.type,"R")==0)                  /*meme systeme que pour les autres piece*/
		return deplacement_roi(pt,a,d);
	if(strcmp(p.type,"e")==0 || strcmp(p.type,"E")==0)
		return deplacement_reine(pt,a,d);
	if(strcmp(p.type,"p")==0 || strcmp(p.type,"P")==0)
		return deplacement_pion(pt,a,d);
	if(strcmp(p.type,"c")==0 || strcmp(p.type,"C")==0)
		return deplacement_cavalier(pt,a,d);
	if(strcmp(p.type,"t")==0 || strcmp(p.type,"T")==0)
		return deplacement_tour(pt,a,d);
	return 0;                                           /*si jamais aucune condition n'est verifier*/
}

int deplacement(partie_t * pt, coordonnee_t a, coordonnee_t d){
	coups_t c;
	piece_t v = piece_creer(".",".");
	piece_t p = pt->echiquier[d.x][d.y];               /*on recupere la piece à deplacer*/
	int i = deplacement_valide(pt,a,d);             /*on recupere le resultat de deplacement valide*/
	if(i==1){                                       /*si le deplacement est valide sans capture*/
		modifier_case(pt,p,a);                      /*on met la piece dans la case d'arriver*/
		modifier_case(pt,v,d);                      /*on met une piece vide (cad case vide) dans la case de depart*/
		c = creer_coups(d,a,0);                     /*on creer le coups et on precise qu'aucune piece n'a etait capturer*/
		listec_ajouter_debut(pt->coups_joues,c);        /*on rajoute le coups à la liste des coups jouee*/
	}
	if(i==2){                                       /*si le deplacement est valide avec capture*/
		modifier_case(pt,p,a);                      
		modifier_case(pt,v,d);
		c = creer_coups(d,a,1);                     /*on creer le coups et on precise qu'une piece a etait capturer*/
		listec_ajouter_debut(pt->coups_joues,c);
	}
	if(i==0){                                       /*si le deplacement n'est pas invalide*/
		printf("\nImpossible.\n");	                /*On previent le joueur qu'il ne peux pas se deplacer*/
		return 0;                       
	}
	return 1; /*si le deplacement est valide*/
}

void annuler_deplacement(partie_t * pt){
	maillonc_t * arn = listec_extraire_debut(pt->coups_joues); /*Extrait le maillon contenant le coups precedemment joue*/
	coups_t ca = arn->val;						/*Recupere le coups du maillon*/
	piece_t v = piece_creer(".",".");
	piece_t p = pt->echiquier[ca.arrivee.x][ca.arrivee.y];		/*Recupere la piece deplacer*/
	modifier_case(pt,p,ca.depart);				/*remet la piece à sa place avant deplacement*/
	if(ca.piece == 1){					/*Si une piece à etait capturer*/
		maillon_t * pm = liste_extraire_debut(pt->pieces_capturees);	/*on extrait le maillon contenant la piece capture*/
		piece_t pr = pm->val;					/*Recupere la piece*/
		coordonnee_t cm = pm->p;				/*recupere les coordonnees de la piece*/
		modifier_case(pt,pr,cm);				/*remet la piece capturer dans la case*/
	}
	else	
		modifier_case(pt,v,ca.arrivee);				/*sinon mettre la piece vide*/
}

coordonnee_t saisie_case(){
	coordonnee_t quitter = creer_coordonnee(9,9); /*creer les coordonnee quitter au cas ou le joueur decide de quitter la partie*/
	coordonnee_t co;
	int x, y;
	int r=0;
	while(r!=1){			/*tant que le joueur ne veux pas quitter*/
		printf("\nTaper 0 pour deplacer une piece\nTaper 1 pour quitter la partie\n");
		scanf("%d",&r);			/*on lui demande de joueur ou de quitter*/
		if(r==0){
			do{
				printf("\nEntre les coordonnees de depart :\nx= "); /*il rentre les coordonne x et y de depart*/
				scanf("%d",&x);
				printf("y= ");
				scanf("%d",&y);
			}while(x<0 || x>7);		/*si elle ne sont pas comprise dans l'eschiquier on repete la demande*/
			co = creer_coordonnee(x,y);		/*si no on creer la coordonnee et la retourne*/
			return co;
		}
		if(r==1){		/*si le joueur veux quitter*/
			printf("Etes vous sur de vouloir quitter ? Oui 1 Non 0.\n");
			scanf("%d",&r); 	/*on confirme et r prendra la valeur 1 si il veux quitter et 0 si il annule*/
		}
	}
	return quitter;		/*retourne la coordonnee quitter */
}			

partie_t * partie_creer(){
	partie_t * p = malloc(sizeof(partie_t));	/*Alloue de l'espace memoire pour une partie*/
	p->pieces_capturees = liste_initialiser();
	p->coups_joues = listec_initialiser();
	return p;					/*retourne le poiteur vers l'espace memoire allouer*/
}

void partie_detruire(partie_t * p){
	liste_detruire(p->pieces_capturees);  
	listec_detruire(p->coups_joues);
	free(p);					/*libere l'espace alouer pour la partie */
}

void plateau_sauvegarder(partie_t * p, char * nom){
	char chemin[27] = "../Plateaux/";
	char * format = ".plt";
	int i,j;
	FILE * f;
	strcat(chemin,nom);		/*colle le nom choisie au chemin du fichier plateaux*/
	strcat(chemin,format);		/*puis colle le format du fichier au chemin (qui est maintenant composer du nom de la partie*/
	if((f=fopen(chemin,"w+"))!=NULL){	/*creer le fichier ou sera sauvegarder la partie*/
		fprintf(f,"PL");		/*Informe que le fichier contient un plateaux*/
		for(i=0;i<8;i++){		
			fprintf(f,"\n");	/*reviens a la ligne apres avoir inscris la 1er ligne de l'echiquier*/
			for(j=0;j<8;j++)	/*parcours toute les case de l'echiquier*/
				fprintf(f,"%s",p->echiquier[i][j].type);	/*inscris le type de la piece*/
		}
		fprintf(f,"\n");	
		fclose(f);		/*ferme le fichier*/
	}
}

void partie_sauvegarder(partie_t * p, char * nom){
	char chemin[27] = "../Parties/";
	char * format = ".part";
	FILE * f;
	maillon_t * i;
	maillonc_t * j;
	strcat(chemin,nom);			/*meme chose que plateaux mais pour parties*/
	strcat(chemin,format);
	if((f=fopen(chemin,"w+"))!=NULL){
		fprintf(f,"%d\n",p->joueur);			/*inscris le joueur qui à decider de quitter la partie*/
		fprintf(f,"%d\n",p->coups_joues->taille);	/*inscris la taille de la liste des coups jouer*/
		for(j=p->coups_joues->premier; j != NULL;j=j->suivant){		/*On inscris chaque coups de la liste*/
			fprintf(f,"%d\n",j->val.depart.x);			/*le x de depart*/
			fprintf(f,"%d\n",j->val.depart.y);			/*y de depart*/
			fprintf(f,"%d\n",j->val.arrivee.x);
			fprintf(f,"%d\n",j->val.arrivee.y);
			fprintf(f,"%d\n",j->val.piece);				/*et si une piece à etait capturer*/
		}
		fprintf(f,"%d\n",p->pieces_capturees->taille);		/*inscris la taille de la liste des pieces captures*/
		for(i=p->pieces_capturees->premier; i != NULL;i=i->suivant){	/*On inscris chaque piece de la liste*/
			if(strcmp(i->val.couleur,"BLANC")==0)	
				fprintf(f,"0\n");			/*si c'est une piece blanche on inscrit 0*/
			else
				fprintf(f,"1\n");			/*sinon 1*/
			fprintf(f,"%s\n",i->val.type);			/*on affiche le type de la piece*/
			fprintf(f,"%d\n",i->p.x);			/*ancienne coordonnee x*/
			fprintf(f,"%d\n",i->p.y);			/*y*/
		}
		fclose(f);
	}
	plateau_sauvegarder(p,nom);  /*lance la fonction pour sauvegarder aussi le plateaux*/
}

void plateaux_charger(partie_t * pt, char * nom){
	char chemin[27] = "../Plateaux/";
	char * format = ".plt";
	int i,j;
	FILE * f;
	char u[3];
	char t[2];
	char tt;
	piece_t p;
	strcat(chemin,nom);
	strcat(chemin,format);
	if((f=fopen(chemin,"r"))!=NULL){
		fscanf(f,"%s",u);
		u[2] = '\0';
		if(strcmp(u,"PL")!=0)
			return;			/*Si ce n'est pas de forme PL =, on quitte*/
		for(i=0;i<8;i++){
			fscanf(f,"\n");		
			for(j=0;j<8;j++){
				fscanf(f,"%c\n",&tt);		/*on recupere la piece*/
				t[0]= tt;
				t[1] = '\0';
				if(64<tt && tt<91)			/*si elle est en majuscule*/
					p = piece_creer("NOIR",t);	/*Alors c'est une piece noir*/
				else
					p = piece_creer("BLANC",t);	/*sinon blanc*/
				pt->echiquier[i][j]=p;			/*et on place cette piece dans l'echiquier*/
			}
		}
		fclose(f);
	}
}

partie_t * partie_charger(char * nom){
	char chemin[27] = "../Parties/";
	char * format = ".part";
	FILE * f;
	partie_t * pt = partie_creer();
	char t[2];
	char tt;
	int c, np, nc, i, j, x, y, x2, y2, cp, jo;
	piece_t p;
	coordonnee_t co, co2;
	coups_t cs;
	strcat(chemin,nom);
	strcat(chemin,format);
	if((f=fopen(chemin,"r"))!=NULL){
		fscanf(f,"%d\n",&jo);
		pt->joueur = jo;			/*recupere le joueur qui joue et le stock dans la partie*/
		fscanf(f,"%d\n",&nc);			/*recupere la taille de la liste des coups jouer*/
		for(j=0;j<nc;j++){			
			fscanf(f,"%d\n",&x);	/*recuper x de depart*/
			fscanf(f,"%d\n",&y);	/*y de depart*/
			co = creer_coordonnee(x,y);		/*cree la coordonnee de depart*/
			fscanf(f,"%d\n",&x2);
			fscanf(f,"%d\n",&y2);
			co2 = creer_coordonnee(x2,y2);		/*cree coordonne d'arrivee*/
			fscanf(f,"%d\n",&cp);			/*recuper le booleen pour piece capture*/
			cs = creer_coups(co,co2,cp);		/*cree le coups*/
			listec_ajouter_fin(pt->coups_joues,cs);	/*le met dans la liste*/
		}
		fscanf(f,"%d\n",&np);			/*recupere la taille de la liste des piece capt*/
		for(i=0;i<np;i++){
			fscanf(f,"%d\n",&c);		/*recupere la couleur de la piece*/
			fscanf(f,"%c\n",&tt);		/*recupere le type de la piece*/
			t[0]= tt;
			t[1] = '\0';
			if(c==0)
				p = piece_creer("BLANC",t);	/*si c'est un blanc alors on cree une piece blanche du type recuperer*/
			else
				p = piece_creer("NOIR",t);	/*sinon on cree piece noire*/
			fscanf(f,"%d\n",&x);			/*recupere la coordonne x de l'emplacement de la piece*/
			fscanf(f,"%d\n",&y);			/*y*/
			co = creer_coordonnee(x,y);		/*creer la coordonne de l'ancienne emplacement de la piece*/
			liste_ajouter_debut(pt->pieces_capturees,p,co);		/*rajoute la piece à la liste des pieces capt*/
		}
	}
	fclose(f);
	plateaux_charger(pt,nom);		/*lance la fonction pour charger aussi le plateau*/
	return pt;			/*retourne la partie charger*/
}

void partie_jouer(){
	coordonnee_t quitter = creer_coordonnee(9,9);		/*la coordonnee quitter*/
	coordonnee_t rep = creer_coordonnee(10,10);	/*une coordonne quelquonque differente de quitter pour rentre dans la boucle*/
	char nom[11];
	char nr[11];
	char n[11];
	int r, x, y, q;
	partie_t * pt;
	int m=1;
	while(m!=2){
		do{
			printf("Taper 0 pour une nouvelle partie.\nTaper 1 pour charger une partie existante.\nTaper 2 pour replay une partie existante.\nTaper 3 pour quitter.\n");
    			scanf("%d",&r);
		}while(r!=1 && r!=0 && r!=2 && r!=3);
		if(r==1){
	    		printf("\nEntree le nom de sauvegarde de la partie à charger : ");
	    		scanf("%s",n);
	    		n[10] = '\0';
	    		pt = partie_charger(n);
	    		if(pt->joueur == 1)
	    			printf("\n                            Au joueur NOIR !\n");
	    		else
	    			printf("\n                            Au joueur BLANC !\n");
			m=2;
		}
		if(r==0){
		    	pt = partie_nouvelle();
		    	pt->joueur=0;
		    	printf("\nLe joueur BLANC commence la partie !\n");
			m=2;
		}
		if(r==2){
		    	printf("Entree le nom de la partie à rejouer : ");
		    	scanf("%s",nr);
		    	nr[10] = '\0';
		    	replay_jouer(nr);
		}
		if(r==3){
        	    q=1;
        	    m=2;
		}
	}
    	if(q!=1){
		afficher_echiquier(pt);
		while(coordonnee_cmp(quitter,rep)!=1){
			if(m!=2){
	    			if(pt->joueur == 1){
	    				pt->joueur=0;
	    				printf("\n                            Au joueur BLANC !\n");
	    			}	
	    			else{
	    				pt->joueur=1;
	    				printf("\n                            Au joueur NOIR !\n");
	    			}
	    		}
	    		while(m!=1){
	    			coordonnee_cpy(&rep,saisie_case());
	    			if(coordonnee_cmp(quitter,rep)==1){
	    				coordonnee_cpy(&rep,quitter);
	    				m=1;
	    			}
	    			else{
	    				do{
	    					printf("Entre les coordonnees d'arrivee :\nx= ");
	    					scanf("%d",&x);
	    					printf("y= ");
	    					scanf("%d",&y);
	    				}while(x<0 || x>7);
	    				m = deplacement(pt,creer_coordonnee(x,y),rep);
	    			}
	    		}
	    		if(coordonnee_cmp(quitter,rep)!=1){
	    			do{
	    				afficher_echiquier(pt);
	    				printf("\nTaper 2 pour annuler le deplacement\nTaper 3 pour passer au joueur suivant\n");
	    				scanf("%d",&m);
	    				if(m==2){
	    					annuler_deplacement(pt);
	    					afficher_echiquier(pt);
	    				}
	    			}while(m!=3 && m!=2);
	    		}
    		}
    		do{
			printf("\nVoulez vous afficher les pieces capturees ? Oui 1 Non 0.\n");
		    	scanf("%d",&r);
		    	if(r==1){
		    		liste_afficher(pt->pieces_capturees);
		    	}
		}while(r!=0 && r!=1);
		printf("Voulez vous sauvegarder la partie ? Oui taper 1 sinon 0.\n");
		scanf("%d",&m);
		if(m==1){
			printf("Entree le nom de sauvegarde de maximum 9 caracteres : ");
			scanf("%s",nom);
			nom[10] = '\0';
			partie_sauvegarder(pt,nom);
		}
		do{
			printf("\nVoulez vous replay votre partie ? Oui 1 Non 0.\n");
			scanf("%d",&r);
			if(r==1){
				replay_jouer(nom);
			}
		}while(r!=0 && r!=1);
	}
}  

listec_t * replay_charger(char * nom ){		/*recupere seleument la liste des coups joue et le joueur qui à quitter la partie*/ 
	char chemin[27] = "../Parties/";
	char * format = ".part";
	FILE * f;
	partie_t * pt = partie_nouvelle();
	int nc, j, x, y, x2, y2, cp, jo;
	coordonnee_t co, co2;
	coups_t cs;
	strcat(chemin,nom);
	strcat(chemin,format);
	if((f=fopen(chemin,"r"))!=NULL){
		fscanf(f,"%d\n",&jo);
		fscanf(f,"%d\n",&nc);
		for(j=0;j<nc;j++){
			fscanf(f,"%d\n",&x);
			fscanf(f,"%d\n",&y);
			co = creer_coordonnee(x,y);
			fscanf(f,"%d\n",&x2);
			fscanf(f,"%d\n",&y2);
			co2 = creer_coordonnee(x2,y2);
			fscanf(f,"%d\n",&cp);
			cs = creer_coups(co,co2,cp);
			listec_ajouter_fin(pt->coups_joues,cs);
		}
	}
	fclose(f);
	return pt->coups_joues;		/*retourne la liste charger*/
}

void replay_jouer(char * nom){
	listec_t * l = replay_charger(nom);	/*recupere la liste des coups joue*/
	partie_t * p = partie_nouvelle();	/* cree un echiquier de depart*/
	maillonc_t * m;
	coups_t cp;
	int r;
	while(listec_vide(*l)!=1){	/*tant que la liste n'est pas vide*/
		m = listec_extraire_fin(l);	/*on extrait le maillon*/
		cp = m->val;
		deplacement(p,cp.arrivee,cp.depart);	/*effectue le deplacement avec les coordonnee du coups extrait dans la nouvelle partie*/
		if(p->joueur == 1)			/*si le joueur est noir*/
			p->joueur = 0;			/*passer au blanc*/
		else
			p->joueur = 1;			/*sinon passer au noir*/
		printf("\nCoup joué : ");		
		coups_afficher(cp);			/*Affiche le coups joue*/
		afficher_echiquier(p);			/*Avec l'echiquier*/
		printf("\nContinuer ? Oui taper 1 sinon 0.\n");	/*si l'utilisateur veux continuer à voir la partie joue*/
		scanf("%d",&r);			/*il tape 1 sinon 0*/
		if(r==0)			/*si il decide de quitter*/
			l->taille=0;		/*Alors on initialise la liste à 0 pour quitter le while*/
	}
	liste_afficher(p->pieces_capturees);	/*et on affiche la liste des piece capturer durant la partie*/
}

partie_t * partie_nouvelle(){				/*creer un ichiquier de debut*/
	partie_t * p = partie_creer();			/*Alloue l'espace necessaire et et rempli chaque case de l'echiquier*/
	p->echiquier[0][0] = piece_creer("NOIR","T");
	p->echiquier[0][1] = piece_creer("NOIR","C");
	p->echiquier[0][2] = piece_creer("NOIR","F");
	p->echiquier[0][3] = piece_creer("NOIR","R");
	p->echiquier[0][4] = piece_creer("NOIR","E");
	p->echiquier[0][5] = piece_creer("NOIR","F");
	p->echiquier[0][6] = piece_creer("NOIR","C");
	p->echiquier[0][7] = piece_creer("NOIR","T");
	p->echiquier[1][0] = piece_creer("NOIR","P");
	p->echiquier[1][1] = piece_creer("NOIR","P");
	p->echiquier[1][2] = piece_creer("NOIR","P");
	p->echiquier[1][3] = piece_creer("NOIR","P");
	p->echiquier[1][4] = piece_creer("NOIR","P");
	p->echiquier[1][5] = piece_creer("NOIR","P");
	p->echiquier[1][6] = piece_creer("NOIR","P");
	p->echiquier[1][7] = piece_creer("NOIR","P");
	p->echiquier[2][0] = piece_creer(".",".");
	p->echiquier[2][1] = piece_creer(".",".");
	p->echiquier[2][2] = piece_creer(".",".");
	p->echiquier[2][3] = piece_creer(".",".");
	p->echiquier[2][4] = piece_creer(".",".");
	p->echiquier[2][5] = piece_creer(".",".");
	p->echiquier[2][6] = piece_creer(".",".");
	p->echiquier[2][7] = piece_creer(".",".");
	p->echiquier[3][0] = piece_creer(".",".");
	p->echiquier[3][1] = piece_creer(".",".");
	p->echiquier[3][2] = piece_creer(".",".");
	p->echiquier[3][3] = piece_creer(".",".");
	p->echiquier[3][4] = piece_creer(".",".");
	p->echiquier[3][5] = piece_creer(".",".");
	p->echiquier[3][6] = piece_creer(".",".");
	p->echiquier[3][7] = piece_creer(".",".");
	p->echiquier[4][0] = piece_creer(".",".");
	p->echiquier[4][1] = piece_creer(".",".");
	p->echiquier[4][2] = piece_creer(".",".");
	p->echiquier[4][3] = piece_creer(".",".");
	p->echiquier[4][4] = piece_creer(".",".");
	p->echiquier[4][5] = piece_creer(".",".");
	p->echiquier[4][6] = piece_creer(".",".");
	p->echiquier[4][7] = piece_creer(".",".");
	p->echiquier[5][0] = piece_creer(".",".");
	p->echiquier[5][1] = piece_creer(".",".");
	p->echiquier[5][2] = piece_creer(".",".");
	p->echiquier[5][3] = piece_creer(".",".");
	p->echiquier[5][4] = piece_creer(".",".");
	p->echiquier[5][5] = piece_creer(".",".");
	p->echiquier[5][6] = piece_creer(".",".");
	p->echiquier[5][7] = piece_creer(".",".");
	p->echiquier[6][0] = piece_creer("BLANC","p");
	p->echiquier[6][1] = piece_creer("BLANC","p");
	p->echiquier[6][2] = piece_creer("BLANC","p");
	p->echiquier[6][3] = piece_creer("BLANC","p");
	p->echiquier[6][4] = piece_creer("BLANC","p");
	p->echiquier[6][5] = piece_creer("BLANC","p");
	p->echiquier[6][6] = piece_creer("BLANC","p");
	p->echiquier[6][7] = piece_creer("BLANC","p");
	p->echiquier[7][0] = piece_creer("BLANC","t");
	p->echiquier[7][1] = piece_creer("BLANC","c");
	p->echiquier[7][2] = piece_creer("BLANC","f");
	p->echiquier[7][3] = piece_creer("BLANC","r");
	p->echiquier[7][4] = piece_creer("BLANC","e");
	p->echiquier[7][5] = piece_creer("BLANC","f");
	p->echiquier[7][6] = piece_creer("BLANC","c");
	p->echiquier[7][7] = piece_creer("BLANC","t");
	return p;
}
