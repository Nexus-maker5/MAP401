#include<stdio.h>
#include<stdlib.h>
#include "liste.h"


/* creer une cellule de liste avec l'element v
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L.taille == 0)
	{
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
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	if (L1.taille == 0) return L2;
	if (L2.taille == 0) return L1;
	
	L1.last->suiv = L2.first;
	L1.last = L2.last;
	L1.taille += L2.taille;
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L
   si la liste est vide, la fonction ne fait rien
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;
	Cellule_Liste_Point *e2=e1->suiv;
	
	free(e1);
	
	L.first = e2;
	if (e2 == NULL)
		L.last = NULL;
	L.taille--;
	return L;
}

/* creer une sequence de points sous forme d'un tableau de points
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	T.taille = L.taille;
	
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	int k = 0;
	Cellule_Liste_Point *el = L.first;
	while (el) 
	{
		T.tab[k] = el->data;
		k++;
		el = el->suiv;
	}
	
	return T;
}

/* ecrire le contour L a l'ecran */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour avec %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k];
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	}
	printf("]\n");
	
	free(TP.tab);
}

/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Contour                                         */
/* ------------------------------------------------------------------ */

/* creer une cellule de liste de contour avec l'element v */
Cellule_Liste_Contour *creer_element_liste_Contour(Contour v)
{
	Cellule_Liste_Contour *el;
	el = (Cellule_Liste_Contour *)malloc(sizeof(Cellule_Liste_Contour));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* creer une liste de contours vide */
Liste_Contour creer_liste_Contour_vide()
{
	Liste_Contour L = {0, NULL, NULL};
	return L;
}

/* ajouter le contour e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Contour e)
{
	Cellule_Liste_Contour *el = creer_element_liste_Contour(e);
	if (L.taille == 0)
	{
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

/* supprimer tous les elements de la liste de contours (liberation memoire
   des points de chaque contour et des cellules), renvoie la liste vide */
Liste_Contour supprimer_liste_Contour(Liste_Contour L)
{
	Cellule_Liste_Contour *el = L.first;
	while (el)
	{
		Cellule_Liste_Contour *suiv = el->suiv;
		supprimer_liste_Point(el->data); /* libere les points du contour */
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL;
	L.taille = 0;
	return L;
}
