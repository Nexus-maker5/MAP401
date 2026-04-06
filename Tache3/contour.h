#ifndef _CONTOUR_H_
#define _CONTOUR_H_
#include "image.h"
#include"geom2d.h"
#include "liste.h"
#include <stdio.h>

typedef enum {Nord,Est,Sud,Ouest} Orientation;

typedef struct {
  double x,y;
  Orientation o;
} robot;

/*Trouver le pixel de depart (le premier pixel noir ayant un pixel blanc au dessus)*/
Point trouver_pixel_depart(Image I);

/*Avancer le robot d'une case */
void avancer(robot *R);

/* faire tourner le robot à gauche */
void tourner_a_gauche(robot *R);

/* faire tourner le robot à droite */
void tourner_a_droite(robot *R);

/*Mettre a jour l'orientation du robot */
void nouvelle_orientation(Image I,robot *R);

/*Memoriser la position du robot*/
void memoriser_position(Contour *C,robot *R);

/*Calculer le contour de l'image*/
void calculer_contour(Image I);

















#endif