#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include "simplification.h"


/* creer une cellule de liste avec l'element v */
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
	if (L1.taille == 0) return L2;
	if (L2.taille == 0) return L1;
	
	L1.last->suiv = L2.first;
	L1.last = L2.last;
	L1.taille += L2.taille;
	return L1;
}

/* supprimer le premier element de la liste */
Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L)
{
	if (L.taille == 0) return L;
	
	Cellule_Liste_Segment *e1=L.first;
	Cellule_Liste_Segment *e2=e1->suiv;
	
	free(e1);
	
	L.first = e2;
	if (e2 == NULL)
		L.last = NULL;
	L.taille--;
	return L;
}

/*convertir une liste de segments en contour*/
Contour liste_segment_vers_contour(Liste_Segment L){
	Contour C=creer_liste_Point_vide();
	Cellule_Liste_Segment *el=L.first;
	while (el) {
		C=ajouter_element_liste_Point(C, el->data.A);
		if(el->suiv==NULL){
			C=ajouter_element_liste_Point(C, el->data.B);
		}
		el = el->suiv;
	}
	return C;
}


/*Simplification de Douglas-Peucker pour une sequence de points*/
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d){
    Liste_Segment L = creer_liste_Segment_vide();

    Segment S = {CONT.tab[j1], CONT.tab[j2]};
    double dmax = 0;
    int k = j1;
    for (int j = j1+1; j < j2; j++){
        double dj = distance_point_segment(CONT.tab[j], S);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }
    if (dmax <= d) {
        L = ajouter_element_liste_Segment(L, S);
    }
    else{
        Liste_Segment L1 = simplification_douglas_peucker(CONT, j1, k, d);
        Liste_Segment L2 = simplification_douglas_peucker(CONT, k, j2, d);
        L = concatener_liste_Segment(L1, L2);
    }
    return L;
}

/*Simplification de Douglas-Peucker appliquee a une liste de contours*/
Liste_Contour simplification_final(Liste_Contour L, double d)
{
    Liste_Contour resultat = creer_liste_Contour_vide();
    Cellule_Liste_Contour *cel = L.first;
    while (cel != NULL)
    {
        Tableau_Point COUNT = sequence_points_liste_vers_tableau(cel->data);
        Liste_Segment seg = simplification_douglas_peucker(COUNT, 0, COUNT.taille - 1, d);
        Contour cont = liste_segment_vers_contour(seg);
        resultat = ajouter_element_liste_Contour(resultat, cont);
        free(COUNT.tab);
        supprimer_liste_Segment(seg);
        cel = cel->suiv;
    }
    return resultat;
}
