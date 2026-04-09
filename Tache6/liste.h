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

/*---- Type Cellule de liste de contour ----*/
typedef struct Cellule_Liste_Contour_
{
    Contour data;                          /* donnee de l'element de liste */
    struct Cellule_Liste_Contour_* suiv;   /* pointeur sur l'element suivant */
} Cellule_Liste_Contour;

/*---- Type Liste de contour ----*/
typedef struct Liste_Contour_
{
    unsigned int taille;            /* nombre d'elements dans la liste */
    Cellule_Liste_Contour *first;   /* pointeur sur le premier element de la liste */
    Cellule_Liste_Contour *last;    /* pointeur sur le dernier element de la liste */
} Liste_Contour;


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


/*================================================================*/
/* PROTOTYPES DE FONCTIONS                    */
/*================================================================*/

/* Cree une cellule de liste avec l'element v.
   Arrete le programme si l'allocation echoue. */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* Cree une liste vide (taille 0, pointeurs NULL) */
Liste_Point creer_liste_Point_vide();

/* Ajoute l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* Supprime tous les elements de la liste (liberation memoire), renvoie la liste vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* Concatene L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* Supprime le premier element de L si elle n'est pas vide.
   Renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* Cree une sequence de points sous forme d'un tableau a partir de la liste L.
   Arrete le programme si l'allocation echoue. */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* Affiche le contour L a l'ecran (convertit en tableau puis affiche) */
void ecrire_contour(Liste_Point L);

/* Cree une cellule de liste de contour avec l'element v.
   Arrete le programme si l'allocation echoue. */
Cellule_Liste_Contour *creer_element_liste_Contour(Contour v);

/* Cree une liste de contours vide (taille 0, pointeurs NULL) */
Liste_Contour creer_liste_Contour_vide();

/* Ajoute le contour e en fin de la liste L, renvoie la liste L modifiee */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Contour e);

/* Supprime tous les elements de la liste de contours (liberation memoire des
   contours et des cellules), renvoie la liste vide */
void supprimer_liste_Contour(Liste_Contour L);

#endif
