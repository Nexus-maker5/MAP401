#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geom2d.h"

/* Création d'un vecteur */
Vecteur set_vecteur(Point P1, Point P2)
{
    Vecteur V = {P2.x - P1.x, P2.y - P1.y};
    return V;
}

/* Création d'un point */
Point set_point(double x, double y)
{
    Point P = {x, y};
    return P;
}

/* Somme de deux points */
Point add_point(Point P1, Point P2)
{
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

/* Somme de deux vecteurs */
Vecteur add_vecteur(Vecteur V1, Vecteur V2)
{
    Vecteur V = {V1.x + V2.x, V1.y + V2.y};
    return V;
}

/* Produit d'un réel par un point */
Point reel_point(double a, Point P)
{
    return set_point(a * P.x, a * P.y);
}

/* Produit d'un réel par un vecteur */
Vecteur reel_vecteur(double a, Vecteur V)
{
    Vecteur V1 = {a * V.x, a * V.y};
    return V1;
}

/* Produit scalaire */
double scalaire(Vecteur V1, Vecteur V2)
{
    return (V1.x * V2.x) + (V1.y * V2.y);
}

/* Norme d'un vecteur */
double norme(Vecteur V)
{
    return sqrt(pow(V.x, 2) + pow(V.y, 2));
}

/* Distance entre 2 points */
double distance_point(Point P1, Point P2)
{
    return sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
}

/* Distance entre un point et un segment */
double distance_point_segment(Point P, Segment S)
{
    double d;

    if (distance_point(S.A, S.B) == 0) {
        Vecteur AP = set_vecteur(S.A, P);
        d = norme(AP);
    } else {
        Vecteur AP = set_vecteur(S.A, P);
        Vecteur BP = set_vecteur(S.B, P);
        Vecteur AB = set_vecteur(S.A, S.B);
        double lambda = scalaire(AP, AB) / scalaire(AB, AB);

        if (lambda < 0) {
            d = norme(AP);
        } else if (lambda <= 1) {
            Point proj = add_point(S.A, reel_point(lambda, set_point(S.B.x - S.A.x, S.B.y - S.A.y)));
            Vecteur QP = set_vecteur(proj, P);
            d = norme(QP);
        } else {
            d = norme(BP);
        }
    }
    return d;
}

/* Conversion d'une courbe de Bezier de degré 2 vers degré 3 */
Bezier3 conversion_bezier2_bezier3(Bezier2 bez)
{
    Bezier3 bez3;
    bez3.C0 = bez.C0;
    bez3.C1 = reel_point(1.0 / 3.0, add_point(bez.C0, reel_point(2.0, bez.C1)));
    bez3.C2 = reel_point(1.0 / 3.0, add_point(bez.C2, reel_point(2.0, bez.C1)));
    bez3.C3 = bez.C2;
    return bez3;
}

/*fonction gamma*/
double calcul_gamma(double k, double n){
        double result = 6 * pow(k, 4) - 8 *n *pow(k, 3) + 6 * pow(k, 2) - 4 * n * k + pow(n, 4) - pow(n, 2);
        return result;
}


/* Calcul d'un point sur une courbe de Bezier de degré 2 */
Point calcul_point_bezier2(double t, Bezier2 bez)
{
    Point B = reel_point(pow(1 - t, 2), bez.C0);
    B = add_point(B, reel_point(2 * t * (1 - t), bez.C1));
    B = add_point(B, reel_point(pow(t, 2), bez.C2));
    return B;
}

/* Distance entre un point et une courbe de Bezier de degré 2 */
double distance_point_bezier2(Point P, Bezier2 bez, double ti)
{
    Point B = calcul_point_bezier2(ti, bez);
    return distance_point(P, B);
}


/* Calcul d'un point sur une courbe de Bezier de degré 3 */
Point calcul_point_bezier3(double t, Bezier3 bez)
{
    Point B = reel_point(pow(1 - t, 3), bez.C0);
    B = add_point(B, reel_point(3 * t * pow(1 - t, 2), bez.C1));
    B = add_point(B, reel_point(3 * pow(t, 2) * (1 - t), bez.C2));
    B = add_point(B, reel_point(pow(t, 3), bez.C3));
    return B;
}

/* Distance entre un point et une courbe de Bezier de degré 3 */
double distance_point_bezier3(Point P, Bezier3 bez, double ti)
{
    Point B = calcul_point_bezier3(ti, bez);
    return distance_point(P, B);
}
