#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include"geom2d.h"
#include "image.h"
#include "contour.h"
#include "liste.h"

/*---- Type segment ----*/
typedef struct Cellule_Liste_Segment_
{
    Segment data;                        /* donnee de l'element de liste */
    struct Cellule_Liste_Segment_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Segment ;

/*---- Type Liste de segment ----*/
typedef struct Liste_Segment_
{
    unsigned int taille;            /* nombre d'elements dans la liste */
    Cellule_Liste_Segment *first;     /* pointeur sur le premier element de la liste */
    Cellule_Liste_Segment *last;      /* pointeur sur le dernier element de la liste */
} Liste_Segment;

/*---- Type Tableau de segment ----*/
typedef struct Tableau_Segment_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Segment *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Segment;



/*================================================================*/
/* PROTOTYPES DE FONCTIONS                    */
/*================================================================*/

/* Cree une cellule de liste avec l'element v.
   Arrete le programme si l'allocation echoue. */
Cellule_Liste_Segment *creer_element_liste_Segment(Segment v);

/* Cree une liste vide (taille 0, pointeurs NULL) */
Liste_Segment creer_liste_Segment_vide();

/* Ajoute l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e);

/* Supprime tous les elements de la liste (liberation memoire), renvoie la liste vide */
Liste_Segment supprimer_liste_Segment(Liste_Segment L);

/* Concatene L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2);

/* Supprime le premier element de L si elle n'est pas vide.
   Renvoie la liste (eventuellement) modifiee */
Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L);

/* Cree une sequence de segments sous forme d'un tableau a partir de la liste L.
   Arrete le programme si l'allocation echoue. */
Tableau_Segment sequence_segments_liste_vers_tableau(Liste_Segment L);

/* Fonction de simplification de contour */
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d);

/* Convertir une liste de segments en contour */
Contour liste_segment_vers_contour(Liste_Segment L);

/* Simplification de Douglas-Peucker appliquee a une liste de contours */
Liste_Contour simplification_final(Liste_Contour L, double d);

#endif
