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


Point trouver_pixel_depart(Image I);

void avancer(robot *R);

void tourner_a_gauche(robot *R);

void tourner_a_droite(robot *R);

void memoriser_position(Contour *C,robot *R);

void nouvelle_orientation(Image I,robot *R);

void contour_final(Image I);

Image creer_image_masque(Image I);

void afficher_contour(Contour C);

Contour calculer_contour(Image I,Image *I_masque, Point pixel);

void sauvegarder_contour_eps(Contour C, char *filename, int largeur, int hauteur);

















#endif