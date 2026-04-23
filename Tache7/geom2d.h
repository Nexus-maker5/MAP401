#ifndef _GEOMETRIE_H_
#define _GEOMETRIE_H_

#include <math.h>
#include <stdio.h>

typedef struct Point_
{
    double x, y;
} Point;

typedef struct Vecteur_
{
    double x, y;
} Vecteur;

typedef struct Segment_
{
    Point A, B;
} Segment;

typedef struct Bezier2_
{
    Point C0, C1, C2;
} Bezier2;

typedef struct Bezier3_
{
    Point C0, C1, C2, C3;
} Bezier3;


/* Création d'un vecteur */
Vecteur set_vecteur(Point P1, Point P2);

/* Création d'un point */
Point set_point(double x, double y);

/* Somme de deux points */
Point add_point(Point P1, Point P2);

/* Somme de deux vecteurs */
Vecteur add_vecteur(Vecteur V1, Vecteur V2);

/* Produit d'un réel par un point */
Point reel_point(double a, Point P);

/* Produit d'un réel par un vecteur */
Vecteur reel_vecteur(double a, Vecteur V);

/* Produit scalaire */
double scalaire(Vecteur V1, Vecteur V2);

/* Norme d'un vecteur */
double norme(Vecteur V);

/*fonction gamma*/
double calcul_gamma(double k, double n);

/* Distance entre 2 points */
double distance_point(Point P1, Point P2);

/* Distance entre un point et un segment */
double distance_point_segment(Point P, Segment S);

/* Calcul d'un point sur une courbe de Bezier de degré 2 */
Point calcul_point_bezier2(double t, Bezier2 bez);

/* Conversion d'une courbe de Bezier de degré 2 vers degré 3 */
Bezier3 conversion_bezier2_bezier3(Bezier2 bez);

/* Distance entre un point et une courbe de Bezier de degré 2 */
double distance_point_bezier2(Point P, Bezier2 bez, double ti);

/* Calcul d'un point sur une courbe de Bezier de degré 3 */
Point calcul_point_bezier3(double t, Bezier3 bez);

/* Distance entre un point et une courbe de Bezier de degré 3 */
double distance_point_bezier3(Point P, Bezier3 bez, double ti);

#endif
