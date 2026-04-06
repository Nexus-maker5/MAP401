#ifndef _CONTOUR_H_
#define _CONTOUR_H_
#include "image.h"
#include"geom2d.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {Nord,Est,Sud,Ouest} Orientation;

typedef struct {
  double x,y;
  Orientation o;
} robot;


/*---- Type Tableau de contour ----*/
typedef struct {
    unsigned int taille;     // Nombre actuel de contours stockÃ©s
    unsigned int capacite;   // CapacitÃ© totale du tableau avant redimensionnement
    Contour *tab;            // Pointeur vers le tableau de Contours
} Tableau_Contours;

/*Creer un tableau de contour vide*/
Tableau_Contours creer_tableau_contours_vide();

/*Ajouter un contour dans le tableau de contour*/
void ajouter_contour(Tableau_Contours *T, Contour C);

/*Recuperer les contours de l'image*/
Tableau_Contours recuperer_contours(Image I);

/*Afficher les statistiques des contours*/
void afficher_stats_contours(Tableau_Contours T);

/*creer un fichier eps pour chaque contour*/
void sauvegarder_contours_eps(Tableau_Contours T, char *filename, int largeur, int hauteur);

/*Liberer la memoire du tableau de contour*/
void liberer_tableau_contours(Tableau_Contours *T);

/* Trouver le pixel de depart (le premier pixel noir ayant un pixel blanc au dessus) */
Point trouver_pixel_depart(Image I);

/*avancer le robot d'une case*/
void avancer(robot *R);

/*tourner a gauche*/
void tourner_a_gauche(robot *R);

/*tourner a droite*/
void tourner_a_droite(robot *R);

/*Creer une image-masque*/
Image creer_image_masque(Image I);

/*memoriser la position du robot dans le contour*/
void memoriser_position(Contour *C,robot *R);

/*nouvelle orientation du robot en fonction de l'image*/
void nouvelle_orientation(Image I,robot *R);

/*Afficher les contours*/
void afficher_contours(Tableau_Contours T);

/*Calculer le contour de l'image*/
Contour calculer_contour(Image I,Image *I_masque, Point pixel);

#endif