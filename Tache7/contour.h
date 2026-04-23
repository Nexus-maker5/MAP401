#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"
#include "geom2d.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { Nord, Est, Sud, Ouest } Orientation;

typedef struct {
    double x, y;
    Orientation o;
} robot;

/* Trouver le pixel de départ (premier pixel noir avec pixel blanc au-dessus) */
Point trouver_pixel_depart(Image I);

/* Avancer le robot d'une case */
void avancer(robot *R);

/* Tourner à gauche */
void tourner_a_gauche(robot *R);

/* Tourner à droite */
void tourner_a_droite(robot *R);

/* Créer une image-masque */
Image creer_image_masque(Image I);

/* Mémoriser la position du robot dans le contour */
void memoriser_position(Contour *C, robot *R);

/* Nouvelle orientation du robot en fonction de l'image */
void nouvelle_orientation(Image I, robot *R);

/* Calculer le contour de l'image à partir d'un pixel de départ */
Contour calculer_contour(Image I, Image *I_masque, Point pixel);

/* Récupérer tous les contours de l'image */
Liste_Contour recuperer_contours(Image I);

/* Afficher les statistiques des contours */
void afficher_stats_contours(Liste_Contour L);

/* Afficher les contours à l'écran */
void afficher_contours(Liste_Contour L);

/* Sauvegarder les contours (points) dans un fichier EPS */
void sauvegarder_contours_eps(Liste_Contour L, char *filename, int largeur, int hauteur);

/* Sauvegarder les contours Bezier3 dans un fichier EPS */
void sauvegarder_contoursbz_eps(Liste_ContourBz L, char *filename, int largeur, int hauteur);

#endif
