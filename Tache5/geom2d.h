#ifndef _GEOMETRIE_H_
#define _GEOMETRIE_H_
#include <stdio.h>


typedef struct Point_
{
    double x,y;	 
} Point;

typedef struct Vecteur_
{
    double x,y;	 
} Vecteur;

/*Création d'un vecteur*/
Vecteur set_vecteur(Point P1,Point P2);

/*Création d'un point*/
Point set_point(double x,double y);

/*Somme de deux points*/
Point add_point(Point P1,Point P2);

/*Somme de deux vecteurs*/
Vecteur add_vecteur(Vecteur V1,Vecteur V2);

/*Produit d'un reel par un point*/
Point reel_point(double a, Point P);

/*Produit d'un reel par un vecteur*/
Vecteur reel_vecteur(double a, Vecteur V);

/*Produit scalaire*/
double scalaire(Vecteur V1,Vecteur V2);

/*Norme d'un vecteur*/
double norme(Vecteur V);

/*Distance entre 2 point*/
double distance_point(Point P1,Point P2);

#endif