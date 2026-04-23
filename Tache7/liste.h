#ifndef LISTE_H
#define LISTE_H

#include "geom2d.h"
#include <stdio.h>
#include <stdlib.h>


/*================================================================*/
/* DEFINITIONS DE TYPES                                           */
/*================================================================*/

#define TAILLE_MAX 1000

/*================================================================*/
/* Liste de points                                                */
/*================================================================*/
typedef struct Cellule_Liste_Point_
{
    Point data;
    struct Cellule_Liste_Point_ *suiv;
} Cellule_Liste_Point;

typedef struct Liste_Point_
{
    unsigned int taille;
    Cellule_Liste_Point *first;
    Cellule_Liste_Point *last;
} Liste_Point;

/* Alias : un contour est une liste de points */
typedef Liste_Point Contour;


/*================================================================*/
/* Tableau de points                                              */
/*================================================================*/
typedef struct Tableau_Point_
{
    unsigned int taille;
    Point *tab;
} Tableau_Point;


/*================================================================*/
/* Liste de contours                                              */
/*================================================================*/
typedef struct Cellule_Liste_Contour_
{
    Contour data;
    struct Cellule_Liste_Contour_ *suiv;
} Cellule_Liste_Contour;

typedef struct Liste_Contour_
{
    unsigned int taille;
    Cellule_Liste_Contour *first;
    Cellule_Liste_Contour *last;
} Liste_Contour;


/*================================================================*/
/* Liste de segments                                              */
/*================================================================*/
typedef struct Cellule_Liste_Segment_
{
    Segment data;
    struct Cellule_Liste_Segment_ *suiv;
} Cellule_Liste_Segment;

typedef struct Liste_Segment_
{
    unsigned int taille;
    Cellule_Liste_Segment *first;
    Cellule_Liste_Segment *last;
} Liste_Segment;


/*================================================================*/
/* Liste de Bezier2                                               */
/*================================================================*/
typedef struct Cellule_Liste_Bezier2_
{
    Bezier2 data;
    struct Cellule_Liste_Bezier2_ *suiv;
} Cellule_Liste_Bezier2;

typedef struct Liste_Bezier2_
{
    unsigned int taille;
    Cellule_Liste_Bezier2 *first;
    Cellule_Liste_Bezier2 *last;
} Liste_Bezier2;


/*================================================================*/
/* Liste de Bezier3                                               */
/*================================================================*/
typedef struct Cellule_Liste_Bezier3_
{
    Bezier3 data;
    struct Cellule_Liste_Bezier3_ *suiv;
} Cellule_Liste_Bezier3;

typedef struct Liste_Bezier3_
{
    unsigned int taille;
    Cellule_Liste_Bezier3 *first;
    Cellule_Liste_Bezier3 *last;
} Liste_Bezier3;

/* Alias : un contour Bezier est une liste de Bezier3 */
typedef Liste_Bezier3 ContourBz;


/*================================================================*/
/* Liste de ContourBz                                             */
/*================================================================*/
typedef struct Cellule_Liste_ContourBz_
{
    ContourBz data;
    struct Cellule_Liste_ContourBz_ *suiv;
} Cellule_Liste_ContourBz;

typedef struct Liste_ContourBz_
{
    unsigned int taille;
    Cellule_Liste_ContourBz *first;
    Cellule_Liste_ContourBz *last;
} Liste_ContourBz;


/*================================================================*/
/* PROTOTYPES DE FONCTIONS                                        */
/*================================================================*/

/* --- Liste_Point --- */
Cellule_Liste_Point *creer_element_liste_Point(Point v);
Liste_Point          creer_liste_Point_vide(void);
Liste_Point          ajouter_element_liste_Point(Liste_Point L, Point e);
Liste_Point          supprimer_liste_Point(Liste_Point L);
Liste_Point          concatener_liste_Point(Liste_Point L1, Liste_Point L2);
Liste_Point          supprimer_premier_element_liste_Point(Liste_Point L);
Tableau_Point        sequence_points_liste_vers_tableau(Liste_Point L);
void                 ecrire_contour(Liste_Point L);

/* --- Liste_Contour --- */
Cellule_Liste_Contour *creer_element_liste_Contour(Contour v);
Liste_Contour          creer_liste_Contour_vide(void);
Liste_Contour          ajouter_element_liste_Contour(Liste_Contour L, Contour e);
void                   supprimer_liste_Contour(Liste_Contour L);

/* --- Liste_Segment --- */
Cellule_Liste_Segment *creer_element_liste_Segment(Segment v);
Liste_Segment          creer_liste_Segment_vide(void);
Liste_Segment          ajouter_element_liste_Segment(Liste_Segment L, Segment e);
Liste_Segment          supprimer_liste_Segment(Liste_Segment L);
Liste_Segment          concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2);
Liste_Segment          supprimer_premier_element_liste_Segment(Liste_Segment L);
Contour                liste_segment_vers_contour(Liste_Segment L);

/* --- Liste_Bezier2 --- */
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v);
Liste_Bezier2          creer_liste_Bezier2_vide(void);
Liste_Bezier2          ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 e);
Liste_Bezier2          supprimer_liste_Bezier2(Liste_Bezier2 L);
Liste_Bezier2          concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);

/* --- Liste_Bezier3 --- */
Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 v);
Liste_Bezier3          creer_liste_Bezier3_vide(void);
Liste_Bezier3          ajouter_element_liste_Bezier3(Liste_Bezier3 L, Bezier3 e);
Liste_Bezier3          supprimer_liste_Bezier3(Liste_Bezier3 L);
Liste_Bezier3          concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2);

/* Conversion d'une liste de Bezier2 vers une liste de Bezier3 */
Liste_Bezier3 conversion_Liste_Bezier2_Bezier3(Liste_Bezier2 bez);

/* --- Liste_ContourBz --- */
Cellule_Liste_ContourBz *creer_element_liste_ContourBz(ContourBz v);
Liste_ContourBz          creer_liste_ContourBz_vide(void);
Liste_ContourBz          ajouter_element_liste_ContourBz(Liste_ContourBz L, ContourBz e);
void                     supprimer_liste_ContourBz(Liste_ContourBz L);

#endif
