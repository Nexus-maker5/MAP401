#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "geom2d.h"


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Point                                           */
/* ------------------------------------------------------------------ */

Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
    Cellule_Liste_Point *el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Point creer_liste_Point_vide(void)
{
    Liste_Point L = {0, NULL, NULL};
    return L;
}

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
    Cellule_Liste_Point *el = creer_element_liste_Point(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Liste_Point supprimer_liste_Point(Liste_Point L)
{
    Cellule_Liste_Point *el = L.first;
    while (el) {
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;
    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
    if (L.taille == 0) return L;
    Cellule_Liste_Point *e1 = L.first;
    Cellule_Liste_Point *e2 = e1->suiv;
    free(e1);
    L.first = e2;
    if (e2 == NULL)
        L.last = NULL;
    L.taille--;
    return L;
}

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
    Tableau_Point T;
    T.taille = L.taille;
    T.tab = (Point *)malloc(sizeof(Point) * T.taille);
    if (T.tab == NULL) {
        fprintf(stderr, "sequence_points_liste_vers_tableau : allocation impossible\n");
        exit(-1);
    }
    int k = 0;
    Cellule_Liste_Point *el = L.first;
    while (el) {
        T.tab[k] = el->data;
        k++;
        el = el->suiv;
    }
    return T;
}

void ecrire_contour(Liste_Point L)
{
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int nP = (int)TP.taille;
    printf("Contour avec %d points\n[", nP);
    for (int k = 0; k < nP; k++) {
        Point P = TP.tab[k];
        printf(" (%5.1f,%5.1f)", P.x, P.y);
    }
    printf("]\n");
    free(TP.tab);
}


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Contour                                         */
/* ------------------------------------------------------------------ */

Cellule_Liste_Contour *creer_element_liste_Contour(Contour v)
{
    Cellule_Liste_Contour *el = (Cellule_Liste_Contour *)malloc(sizeof(Cellule_Liste_Contour));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Contour creer_liste_Contour_vide(void)
{
    Liste_Contour L = {0, NULL, NULL};
    return L;
}

Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Contour e)
{
    Cellule_Liste_Contour *el = creer_element_liste_Contour(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

void supprimer_liste_Contour(Liste_Contour L)
{
    Cellule_Liste_Contour *el = L.first;
    while (el) {
        Cellule_Liste_Contour *suiv = el->suiv;
        supprimer_liste_Point(el->data);
        free(el);
        el = suiv;
    }
}


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Segment                                         */
/* ------------------------------------------------------------------ */

Cellule_Liste_Segment *creer_element_liste_Segment(Segment v)
{
    Cellule_Liste_Segment *el = (Cellule_Liste_Segment *)malloc(sizeof(Cellule_Liste_Segment));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Segment : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Segment creer_liste_Segment_vide(void)
{
    Liste_Segment L = {0, NULL, NULL};
    return L;
}

Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e)
{
    Cellule_Liste_Segment *el = creer_element_liste_Segment(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Liste_Segment supprimer_liste_Segment(Liste_Segment L)
{
    Cellule_Liste_Segment *el = L.first;
    while (el) {
        Cellule_Liste_Segment *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;
    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L)
{
    if (L.taille == 0) return L;
    Cellule_Liste_Segment *e1 = L.first;
    Cellule_Liste_Segment *e2 = e1->suiv;
    free(e1);
    L.first = e2;
    if (e2 == NULL)
        L.last = NULL;
    L.taille--;
    return L;
}

/* Convertir une liste de segments en contour */
Contour liste_segment_vers_contour(Liste_Segment L)
{
    Contour C = creer_liste_Point_vide();
    Cellule_Liste_Segment *el = L.first;
    while (el) {
        C = ajouter_element_liste_Point(C, el->data.A);
        if (el->suiv == NULL)
            C = ajouter_element_liste_Point(C, el->data.B);
        el = el->suiv;
    }
    return C;
}


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Bezier2                                         */
/* ------------------------------------------------------------------ */

Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 v)
{
    Cellule_Liste_Bezier2 *el = (Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Bezier2));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Bezier2 : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Bezier2 creer_liste_Bezier2_vide(void)
{
    Liste_Bezier2 L = {0, NULL, NULL};
    return L;
}

Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 e)
{
    Cellule_Liste_Bezier2 *el = creer_element_liste_Bezier2(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Liste_Bezier2 supprimer_liste_Bezier2(Liste_Bezier2 L)
{
    Cellule_Liste_Bezier2 *el = L.first;
    while (el) {
        Cellule_Liste_Bezier2 *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;
    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_Bezier3                                         */
/* ------------------------------------------------------------------ */

Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 v)
{
    Cellule_Liste_Bezier3 *el = (Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Bezier3));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_Bezier3 : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Bezier3 creer_liste_Bezier3_vide(void)
{
    Liste_Bezier3 L = {0, NULL, NULL};
    return L;
}

Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 L, Bezier3 e)
{
    Cellule_Liste_Bezier3 *el = creer_element_liste_Bezier3(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L)
{
    Cellule_Liste_Bezier3 *el = L.first;
    while (el) {
        Cellule_Liste_Bezier3 *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2)
{
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;
    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

/* Conversion d'une liste de Bezier2 vers une liste de Bezier3 */
Liste_Bezier3 conversion_Liste_Bezier2_Bezier3(Liste_Bezier2 bez)
{
    Liste_Bezier3 L = creer_liste_Bezier3_vide();
    Cellule_Liste_Bezier2 *el = bez.first;
    while (el) {
        Bezier3 bez3 = conversion_bezier2_bezier3(el->data);
        L = ajouter_element_liste_Bezier3(L, bez3);
        el = el->suiv;
    }
    return L;
}


/* ------------------------------------------------------------------ */
/* Fonctions sur Liste_ContourBz                                       */
/* ------------------------------------------------------------------ */

Cellule_Liste_ContourBz *creer_element_liste_ContourBz(ContourBz v)
{
    Cellule_Liste_ContourBz *el = (Cellule_Liste_ContourBz *)malloc(sizeof(Cellule_Liste_ContourBz));
    if (el == NULL) {
        fprintf(stderr, "creer_element_liste_ContourBz : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_ContourBz creer_liste_ContourBz_vide(void)
{
    Liste_ContourBz L = {0, NULL, NULL};
    return L;
}

Liste_ContourBz ajouter_element_liste_ContourBz(Liste_ContourBz L, ContourBz e)
{
    Cellule_Liste_ContourBz *el = creer_element_liste_ContourBz(e);
    if (L.taille == 0) {
        L.first = L.last = el;
    } else {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

/* Libère tous les éléments de la liste de ContourBz */
void supprimer_liste_ContourBz(Liste_ContourBz L)
{
    Cellule_Liste_ContourBz *el = L.first;
    while (el) {
        Cellule_Liste_ContourBz *suiv = el->suiv;
        supprimer_liste_Bezier3(el->data); /* libère les courbes du contour */
        free(el);
        el = suiv;
    }
}
