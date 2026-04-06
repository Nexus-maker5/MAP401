#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "liste.h"
#include "simplification.h"


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Segment *creer_element_liste_Segment(Segment v)
{
	Cellule_Liste_Segment *el;
	el = (Cellule_Liste_Segment *)malloc(sizeof(Cellule_Liste_Segment));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Segment : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Segment creer_liste_Segment_vide()
{
	Liste_Segment L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e)
{
	Cellule_Liste_Segment *el;
	
	el = creer_element_liste_Segment(e);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Segment supprimer_liste_Segment(Liste_Segment L)
{
	Cellule_Liste_Segment *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Segment *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Segment *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Segment *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de segments L */
Tableau_Segment sequence_segments_liste_vers_tableau(Liste_Segment L)
{
	Tableau_Segment T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Segment */
	T.tab = malloc(sizeof(Segment) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_segments_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Segment *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

/*convertir une liste de segments en contour*/
Contour liste_segment_vers_contour(Liste_Segment L){
	Contour C=creer_liste_Point_vide();
	Cellule_Liste_Segment *el=L.first;
	while (el) {
		C=ajouter_element_liste_Point(C, el->data.A);
		if(el->suiv==NULL){ /* si c'est le dernier segment de la liste, on ajoute aussi le point B du segment */
			C=ajouter_element_liste_Point(C, el->data.B);
		}
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	return C;
}


/*Simplification de Douglas-Peucker pour une séquence de points*/
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT ,int j1 , int j2, double d  ){
    Liste_Segment  L= creer_liste_Segment_vide();

    Segment S= {CONT.tab[j1], CONT.tab[j2]};
    double dmax=0;
    int k=j1;
    for (int j=j1+1; j<j2; j++){
        double dj = distance_point_segment(CONT.tab[j], S);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }
    if (dmax <= d) {
        L=ajouter_element_liste_Segment(L, S);
    }
    else{
        Liste_Segment L1 = simplification_douglas_peucker(CONT, j1, k, d);
        Liste_Segment L2 = simplification_douglas_peucker(CONT, k, j2, d);
        L=concatener_liste_Segment(L1,L2);
    }  
    return L;  
}

/*Simplication de Douglas-Peucker pour un tableau de contours*/
Tableau_Contours simplification_final(Tableau_Contours C, double d)
{
    Tableau_Contours seq=creer_tableau_contours_vide();
    for (int i = 0; i < C.taille; i++)
    {	
		Tableau_Point COUNT=sequence_points_liste_vers_tableau(C.tab[i]);
		Liste_Segment L=simplification_douglas_peucker(COUNT, 0, COUNT.taille-1, d);
		Contour cont=liste_segment_vers_contour(L);
		ajouter_contour(&seq, cont);
		free(COUNT.tab);
		supprimer_liste_Segment(L);
    }
    return seq;
}
