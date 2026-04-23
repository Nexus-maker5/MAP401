#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"
#include "math.h"
#include "liste.h"
#include "simplification.h"


/* Simplification de Douglas-Peucker pour une séquence de points */
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d)
{
    Liste_Segment L = creer_liste_Segment_vide();
    Segment S = {CONT.tab[j1], CONT.tab[j2]};
    double dmax = 0.0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++) {
        double dj = distance_point_segment(CONT.tab[j], S);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
        L = ajouter_element_liste_Segment(L, S);
    } else {
        Liste_Segment L1 = simplification_douglas_peucker(CONT, j1, k, d);
        Liste_Segment L2 = simplification_douglas_peucker(CONT, k, j2, d);
        L = concatener_liste_Segment(L1, L2);
    }
    return L;
}

/* Simplification de Douglas-Peucker appliquée à une liste de contours */
Liste_Contour simplification_final(Liste_Contour L, double d)
{
    Liste_Contour resultat = creer_liste_Contour_vide();
    Cellule_Liste_Contour *cel = L.first;

    while (cel != NULL) {
        Tableau_Point T = sequence_points_liste_vers_tableau(cel->data);
        Liste_Segment seg = simplification_douglas_peucker(T, 0, (int)T.taille - 1, d);
        Contour cont = liste_segment_vers_contour(seg);
        resultat = ajouter_element_liste_Contour(resultat, cont);
        free(T.tab);
        supprimer_liste_Segment(seg);
        cel = cel->suiv;
    }
    return resultat;
}

/* Approximation par courbe de Bezier de degré 2 */
Bezier2 approx_bezier2(Tableau_Point CONT, int j1, int j2)
{
    Bezier2 bez;
    bez.C0 = CONT.tab[j1];
    bez.C2 = CONT.tab[j2];

    int n = j2 - j1;
    if (n == 1) {
        bez.C1 = reel_point(0.5, add_point(bez.C0, bez.C2));
    } else {
        double dn = (double)n;
        double alpha = (3 * dn) / (dn * dn - 1.0);
        double beta  = (1 - 2 * dn) / (2 * (dn + 1));

        bez.C1 = set_point(0, 0);
        for (int i = j1 + 1; i < j2; i++)
            bez.C1 = add_point(bez.C1, CONT.tab[i]);

        bez.C1 = reel_point(alpha, bez.C1);
        bez.C1 = add_point(bez.C1, reel_point(beta, add_point(bez.C0, bez.C2)));
    }
    return bez;
}


/* Approximation par courbe de Bezier de degré 3 */
Bezier3 approx_bezier3(Tableau_Point CONT, int j1, int j2)
{
    Bezier3 bez;
    
    double n = j2 - j1;
    if (n < 3) {
        Bezier2 bez2 = approx_bezier2(CONT, j1, j2);
        bez = conversion_bezier2_bezier3(bez2);
    } else {
        bez.C0 = CONT.tab[j1];
        bez.C3 = CONT.tab[j2];
        bez.C1 = set_point(0, 0);
        bez.C2 = set_point(0, 0);
        double alpha = ((-15 * pow(n, 3)) +  (5 *pow(n, 2)) + (2*n) + 4 )/ (3 *(n+2) *(3*pow(n, 2) + 1));
        double beta  = ((10 * pow(n, 3)) - (15 *pow(n, 2)) + n + 2 )/ (3 *(n+2) *(3*pow(n, 2) + 1));
        double lambda = (70 *n) / (3 *(pow(n, 2)-1) * (pow(n, 2)-4) * (3*pow(n, 2) + 1));
        double gamma;
        for (int i = 1; i <= (int)n-1; i++){
            gamma=calcul_gamma((double)i, n);
            bez.C1 = add_point(bez.C1, reel_point(gamma, CONT.tab[j1+i]));
            gamma=calcul_gamma((double)(n-i), n);
            bez.C2 = add_point(bez.C2, reel_point(gamma, CONT.tab[j1+i]));
        }
        bez.C1 = reel_point(lambda, bez.C1);
        bez.C2 = reel_point(lambda, bez.C2);
        bez.C1 = add_point(bez.C1, reel_point(alpha, CONT.tab[j1]));
        bez.C1 = add_point(bez.C1, reel_point(beta, CONT.tab[j2]));
        bez.C2 = add_point(bez.C2, reel_point(beta, CONT.tab[j1]));
        bez.C2 = add_point(bez.C2, reel_point(alpha, CONT.tab[j2]));
        
    }
    return bez;
}


/* Simplification de contour par approximation de Bezier de degré 2 */
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, double d)
{
    Liste_Bezier2 L = creer_liste_Bezier2_vide();
    int n = j2 - j1;
    Bezier2 bez = approx_bezier2(CONT, j1, j2);
    double dmax = 0.0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++) {
        int i = j - j1;
        double ti = (double)i / (double)n;
        double dj = distance_point_bezier2(CONT.tab[j], bez, ti);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
        L = ajouter_element_liste_Bezier2(L, bez);
    } else {
        Liste_Bezier2 L1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d);
        Liste_Bezier2 L2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d);
        L = concatener_liste_Bezier2(L1, L2);
    }
    return L;
}

/* Simplification de Douglas-Peucker Bezier2 appliquée à une liste de contours */
Liste_ContourBz simplification_final_bezier2(Liste_Contour L, double d)
{
    Liste_ContourBz resultat = creer_liste_ContourBz_vide();
    Cellule_Liste_Contour *cel = L.first;
    int i=0;
    while (cel != NULL) {
        Tableau_Point T = sequence_points_liste_vers_tableau(cel->data);
        Liste_Bezier2 bez = simplification_douglas_peucker_bezier2(T, 0, (int)T.taille - 1, d);
        i+=bez.taille;
        ContourBz cont = conversion_Liste_Bezier2_Bezier3(bez);
        resultat = ajouter_element_liste_ContourBz(resultat, cont);
        free(T.tab);
        supprimer_liste_Bezier2(bez);
        cel = cel->suiv;
    }
    printf("Le nombre de courbes de bezier est:%d\n",i);
    return resultat;
}


/* Simplification de contour par approximation de Bezier de degré 3 */
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point CONT, int j1, int j2, double d)
{
    Liste_Bezier3 L = creer_liste_Bezier3_vide();
    int n = j2 - j1;
    Bezier3 bez = approx_bezier3(CONT, j1, j2);
    double dmax = 0.0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++) {
        int i = j - j1;
        double ti = (double)i / (double)n;
        double dj = distance_point_bezier3(CONT.tab[j], bez, ti);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
        L = ajouter_element_liste_Bezier3(L, bez);
    } else {
        Liste_Bezier3 L1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d);
        Liste_Bezier3 L2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d);
        L = concatener_liste_Bezier3(L1, L2);
    }
    return L;
}


/* Simplification de Douglas-Peucker Bezier3 appliquée à une liste de contours */
Liste_ContourBz simplification_final_bezier3(Liste_Contour L, double d)
{
    Liste_ContourBz resultat = creer_liste_ContourBz_vide();
    Cellule_Liste_Contour *cel = L.first;
    int i=0;
    while (cel != NULL) {
        Tableau_Point T = sequence_points_liste_vers_tableau(cel->data);
        Liste_Bezier3 bez = simplification_douglas_peucker_bezier3(T, 0, (int)T.taille - 1, d);
        i+=bez.taille;
        resultat = ajouter_element_liste_ContourBz(resultat, bez);
        free(T.tab);
        cel = cel->suiv;
    }
    printf("Le nombre de courbes de bezier est:%d\n",i);
    return resultat;
}
