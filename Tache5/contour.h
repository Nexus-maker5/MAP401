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


/*Creer une liste de contours vide*/
Liste_Contour creer_liste_contours_vide();

/*Ajouter un contour dans la liste de contours*/
void ajouter_contour(Liste_Contour *L, Contour C);

/*Recuperer les contours de l'image*/
Liste_Contour recuperer_contours(Image I);

/*Afficher les statistiques des contours*/
void afficher_stats_contours(Liste_Contour L);

/*creer un fichier eps pour chaque contour*/
void sauvegarder_contours_eps(Liste_Contour L, char *filename, int largeur, int hauteur);

/*Liberer la memoire de la liste de contours*/
void liberer_liste_contours(Liste_Contour *L);

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
void afficher_contours(Liste_Contour L);

/*Calculer le contour de l'image*/
Contour calculer_contour(Image I,Image *I_masque, Point pixel);

#endif
