#ifndef SIMPLIFICATION_H
#define SIMPLIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"
#include "liste.h"
#include "contour.h"


/*================================================================*/
/* PROTOTYPES DE FONCTIONS                                        */
/*================================================================*/

/* Simplification de Douglas-Peucker sur une séquence de points */
Liste_Segment simplification_douglas_peucker(Tableau_Point CONT, int j1, int j2, double d);

/* Simplification de Douglas-Peucker appliquée à une liste de contours */
Liste_Contour simplification_final(Liste_Contour L, double d);

/* Approximation par courbe de Bezier de degré 2 */
Bezier2 approx_bezier2(Tableau_Point CONT, int j1, int j2);


/* Approximation par courbe de Bezier de degré 3 */
Bezier3 approx_bezier3(Tableau_Point CONT, int j1, int j2);

/* Simplification de contour par approximation de Bezier de degré 2 */
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point CONT, int j1, int j2, double d);

/* Simplification de Douglas-Peucker Bezier2 appliquée à une liste de contours */
Liste_ContourBz simplification_final_bezier2(Liste_Contour L, double d);

/* Simplification de contour par approximation de Bezier de degré 3 */
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point CONT, int j1, int j2, double d);

/* Simplification de Douglas-Peucker Bezier3 appliquée à une liste de contours */
Liste_ContourBz simplification_final_bezier3(Liste_Contour L, double d);


#endif
