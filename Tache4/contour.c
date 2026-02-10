#include "contour.h"
#include"geom2d.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

// Trouver le pixel de depart (le premier pixel noir ayant un pixel blanc au dessus)
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
    printf("Pas de pixel candidat détecté\n");
    exit(1);
}

// Avancer le robot d'une case 
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

/* faire tourner le robot à gauche */
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
// Mettre a jour l'orientation du robot 
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
// Memoriser la position du robot
void memoriser_position(Contour *C,robot *R){
    *C = ajouter_element_liste_Point(*C, set_point(R->x,R->y));
}

// Calculer le contour de l'image
Contour calculer_contour(Image I){
    robot R;
    Contour C;
    C=creer_liste_Point_vide();
    double x0,y0;
    int cond=1;
    Point pixel=trouver_pixel_depart(I);
    y0=pixel.y-1;
    x0=pixel.x-1;
    R.x=x0;
    R.y=y0;
    R.o=Est;
    while (cond==1){
        memoriser_position(&C,&R);
        avancer(&R);
        nouvelle_orientation(I,&R);
        if(R.x==x0 && R.y==y0 && R.o==Est){
            cond=0;
        }
    }
    memoriser_position(&C,&R);
    printf("Nombre de segment : %d\n",C.taille-1);
    return C;
}

void sauvegarder_contour_eps(Contour C, char *filename, int largeur, int hauteur) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s pour écriture.\n", filename);
        exit(1);
    }
    
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    
    fprintf(f, "0 setlinewidth\n");

    Cellule_Liste_Point *courant = C.first;
    int premier_point = 1;
    while (courant != NULL) {
        Point p = courant->data;

        if (premier_point) {
            fprintf(f, "%.2f %.2f moveto\n", p.x, (double)hauteur - p.y); 
            premier_point = 0;
        } else {
            fprintf(f, "%.2f %.2f lineto\n", p.x, (double)hauteur - p.y);
        }
        courant = courant->suiv;
    }
    if(C.first->data.x == C.last->data.x && C.first->data.y == C.last->data.y) {
        printf("Choissir le type de remplissage : 1 pour remplir, 0 pour contour seulement : ");
        int choix;
        scanf("%d", &choix);
        if(choix == 1) {
            fprintf(f, "fill\n");
        }
        else {
            fprintf(f, "stroke\n");
        }
    }
    fprintf(f, "showpage\n"); // Afficher la page
    fclose(f);
    printf("Fichier %s généré avec succès.\n", filename);
}

