#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>
#include"geom2d.h"

/*================================================================*/
/* DEFINITIONS DE TYPES                    */
/*================================================================*/

#define taillle_max 1000

/*---- Type Cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
    Point data;                        /* donnee de l'element de liste */
    struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- Type Liste de point ----*/
typedef struct Liste_Point_
{
    unsigned int taille;            /* nombre d'elements dans la liste */
    Cellule_Liste_Point *first;     /* pointeur sur le premier element de la liste */
    Cellule_Liste_Point *last;      /* pointeur sur le dernier element de la liste */
} Liste_Point;

/*---- Type Contour (alias de Liste_Point) ----*/
typedef Liste_Point Contour; 

/*---- Type Tableau de point ----*/
typedef struct Tableau_Point_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;


/*---- Type Tableau de contour ----*/
typedef struct Seq_Contour_
{
    unsigned int taille;            /* nombre d'elements dans la liste */
    Contour *C; 
} Seq_Contour;


/*================================================================*/
/* PROTOTYPES DE FONCTIONS                    */
/*================================================================*/


/* Crée une cellule de liste avec l'élément v.
   Arrête le programme si l'allocation échoue. */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* Crée une liste vide (taille 0, pointeurs NULL) */
Liste_Point creer_liste_Point_vide();

/* Ajoute l'élément e en fin de la liste L, renvoie la liste L modifiée */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* Supprime tous les éléments de la liste (libération mémoire), renvoie la liste vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* Concatène L2 à la suite de L1, renvoie la liste L1 modifiée */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* Supprime le premier élément de L si elle n'est pas vide.
   Renvoie la liste (éventuellement) modifiée */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* Crée une séquence de points sous forme d'un tableau à partir de la liste L.
   Arrête le programme si l'allocation échoue. */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* Affiche le contour L à l'écran (convertit en tableau puis affiche) */
void ecrire_contour(Liste_Point L);

#endif