#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom2d.h"
#include "liste.h"
#include "image.h"
#include "contour.h"
#include "simplification.h"


int main(void)
{
    Tableau_Point CONT;

    printf("Entrez le nombre de points du contour : ");
    scanf("%d",&CONT.taille);
    CONT.tab = malloc (CONT.taille * sizeof(Point));
    for(int i=0; i<CONT.taille; i++){
        printf("Point P%d (x,y):",i);
        scanf("%lf %lf", &CONT.tab[i].x, &CONT.tab[i].y);
    }
    Bezier2 bez= approx_bezier2(CONT,0,(int)CONT.taille - 1);
    printf("Les points de controles :\n");
    printf("C0=(%.2f,%.2f)\n",bez.C0.x,bez.C0.y);
    printf("C1=(%.2f,%.2f)\n",bez.C1.x,bez.C1.y);
    printf("C2=(%.2f,%.2f)\n",bez.C2.x,bez.C2.y);

}
