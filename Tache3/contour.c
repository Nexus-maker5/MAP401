#include "contour.h"
#include <stdio.h>
#include <stdlib.h>

Point trouver_pixel_depart(Image I){
    UINT i, j,L,H;
	Pixel P1,P2;
	L=largeur_image(I);
	H=hauteur_image(I);
	for(j=1; j<=H; j++){
		for(i=1; i<=L; i++){
			P1=get_pixel_image(I,i,j);
            P2=get_pixel_image(I,i,j-1);
			if(P1==1 && P2==0){
                Point pixel={i,j};
                return pixel;
            } 
		}
	}
    printf("Pas de pixel candidat detecter");
    exit(1);
}


void avancer(robot *R){
    switch(R->o){
        case Nord:
            R->y = R->y - 1;
            break;
        case Est:
            R->x = R->x + 1;
            break;
        case Sud:
            R->y = R->y + 1;
            break;
        case Ouest:
            R->x = R->x - 1;
            break;
        }
    }

void tourner_a_gauche(robot *R) {
  switch (R->o) {
  case Nord:
    R->o = Ouest;
    break;
  case Est:
    R->o = Nord;
    break;
  case Sud:
    R->o = Est;
    break;
  case Ouest:
    R->o = Sud;
    break;
  }
}

/* faire tourner le robot à droite */
void tourner_a_droite(robot *R) {
  switch (R->o) {
  case Nord:
    R->o = Est;
    break;
  case Est:
    R->o = Sud;
    break;
  case Sud:
    R->o = Ouest;
    break;
  case Ouest:
    R->o = Nord;
    break;
  }
}
void nouvelle_orientation(Image I,robot *R){
    Pixel pD;
    Pixel pG;
    double rx = R->x; // Position grille x
    double ry = R->y; // Position grille y
    
    switch(R->o) {
        case Nord:
            pG = get_pixel_image(I, rx, ry); 
            pD = get_pixel_image(I, rx + 1, ry);
            break;
        case Est:
            pG = get_pixel_image(I, rx + 1, ry);
            pD = get_pixel_image(I, rx + 1, ry + 1);
            break;
        case Sud:
            pG = get_pixel_image(I, rx + 1, ry + 1);
            pD = get_pixel_image(I, rx, ry + 1);
            break;
        case Ouest:
            pG = get_pixel_image(I, rx, ry + 1);
            pD = get_pixel_image(I, rx, ry);
            break;
    }

    if(pG==NOIR) tourner_a_gauche(R);
    else if(pD==BLANC) tourner_a_droite(R);
}

void memoriser_position(robot *R){
    printf("(%.1f,%.1f)",R->x,R->y);
}

void calculer_contour(Image I){
    robot R;
    double x0,y0;
    int cond=1;
    Point pixel=trouver_pixel_depart(I);
    y0=pixel.y-1;
    x0=pixel.x-1;
    R.x=x0;
    R.y=y0;
    R.o=Est;
    while (cond==1){
        printf("{");
        memoriser_position(&R);
        printf(",");
        avancer(&R);
        nouvelle_orientation(I,&R);
        if(R.x==x0 && R.y==y0 && R.o==Est){
            cond=0;
        }
    }
    memoriser_position(&R);
    printf("}\n");
}