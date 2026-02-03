#ifndef _CONTOUR_H_
#define _CONTOUR_H_
#include "image.h"
#include <stdio.h>
#include"geom2d.h"
#include "liste.h"



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

void calculer_contour(Image I);

















#endif