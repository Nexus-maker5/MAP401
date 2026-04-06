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

/*---- Type Tableau de segemnt ----*/
typedef struct Tableau_Segment_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Segment *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Segment;



/*================================================================*/
/* PROTOTYPES DE FONCTIONS                    */
/*================================================================*/


/* Crée une cellule de liste avec l'élément v.
   Arrête le programme si l'allocation échoue. */
Cellule_Liste_Segment *creer_element_liste_Segment(Segment v);

/* Crée une liste vide (taille 0, pointeurs NULL) */
Liste_Segment creer_liste_Segment_vide();

/* Ajoute l'élément e en fin de la liste L, renvoie la liste L modifiée */
Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e);

/* Supprime tous les éléments de la liste (libération mémoire), renvoie la liste vide */
Liste_Segment supprimer_liste_Segment(Liste_Segment L);

/* Concatène L2 à la suite de L1, renvoie la liste L1 modifiée */
Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2);

/* Supprime le premier élément de L si elle n'est pas vide.
   Renvoie la liste (éventuellement) modifiée */
Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L);

/* Crée une séquence de segments sous forme d'un tableau à partir de la liste L.
   Arrête le programme si l'allocation échoue. */
Tableau_Segment sequence_segments_liste_vers_tableau(Liste_Segment L);

//fonction de simplification de contour
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT ,int j1 , int j2, double d  );

Contour liste_segment_vers_contour(Liste_Segment L);

//Sequence de contour sous forme de liste de segment
Tableau_Contours simplification_final( Tableau_Contours C, double d);

#endif