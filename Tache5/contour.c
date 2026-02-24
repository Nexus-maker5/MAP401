#include "contour.h"
#include"geom2d.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

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

// Faire tourner le robot à gauche
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

// Faire tourner le robot à droite
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


// Trouver le pixel de depart (le premier pixel noir ayant un pixel blanc au dessus)
Point trouver_pixel_depart(Image I){
    UINT i, j,L,H;
	Pixel P1;
	L=largeur_image(I);
	H=hauteur_image(I);
	for(j=1; j<=H; j++){
		for(i=1; i<=L; i++){
			P1=get_pixel_image(I,i,j);
			if(P1==1){
                Point pixel={i,j};
                return pixel;
            } 
		}
	}
    return set_point(-1,-1);
}

//Creer une image-masque
Image creer_image_masque(Image I){
    UINT L=largeur_image(I);
    UINT H=hauteur_image(I);
    Image I_masque= creer_image(L,H);
    for (int j=1; j<H+1;j++){
        for (int i=1;i<L+1;i++){
            Pixel P1=get_pixel_image(I,i,j);
            Pixel P2=get_pixel_image(I,i,j-1);
            if (P1==NOIR && P2==BLANC){
                set_pixel_image(I_masque,i,j,NOIR);
            }
            else{
                set_pixel_image(I_masque,i,j,BLANC);
            }
        }
    }
    return I_masque;
}


// Memoriser la position du robot
void memoriser_position(Contour *C,robot *R){
    *C = ajouter_element_liste_Point(*C, set_point(R->x,R->y));
}

// Calculer le contour de l'image
Contour calculer_contour(Image I,Image *I_masque, Point pixel){
    robot R;
    Contour C;
    C=creer_liste_Point_vide();
    double x0,y0;
    int cond=1;
    y0=pixel.y-1;
    x0=pixel.x-1;
    R.x=x0;
    R.y=y0;
    R.o=Est;
    while (cond==1){
        memoriser_position(&C,&R);
        avancer(&R);
        nouvelle_orientation(I,&R);
        if(R.o==Est){
            set_pixel_image(*I_masque,R.x+1,R.y+1,BLANC);
        }
        if(R.x==x0 && R.y==y0 && R.o==Est){
            cond=0;
        }
    }
    memoriser_position(&C,&R);
    return C;
}

// --- Gestion du Tableau de Contours ---

Tableau_Contours creer_tableau_contours_vide() {
    Tableau_Contours T;
    T.taille = 0;
    T.capacite = 50; // Capacité initiale arbitraire
    T.tab = malloc(T.capacite * sizeof(Contour));
    if (T.tab == NULL) {
        fprintf(stderr, "Erreur d'allocation initiale du tableau\n");
        exit(1);
    }
    return T;
}

void ajouter_contour(Tableau_Contours *T, Contour C) {
    if (T->taille >= T->capacite) {
        T->capacite *= 2;
        T->tab = realloc(T->tab, T->capacite * sizeof(Contour));
        if (T->tab == NULL) {
            fprintf(stderr, "Erreur de réallocation mémoire\n");
            exit(1);
        }
    }
    T->tab[T->taille] = C;
    T->taille++;
}

void liberer_tableau_contours(Tableau_Contours *T) {
    free(T->tab);
    T->tab = NULL;
    T->taille = 0;
    T->capacite = 0;
}

// --- Fonctions Principales utilisant le Tableau ---

Tableau_Contours recuperer_contours(Image I) {
    Tableau_Contours T = creer_tableau_contours_vide();
    Image I_masque = creer_image_masque(I);
    while (1) {
        Point depart = trouver_pixel_depart(I_masque);
        if (depart.x == -1 && depart.y == -1) break;
        Contour C = calculer_contour(I, &I_masque, depart);
        ajouter_contour(&T, C);
    }
    return T;
}

void afficher_stats_contours(Tableau_Contours T) {
    int total_segments = 0;
    // Parcours simple avec une boucle for
    for (unsigned int i = 0; i < T.taille; i++) {
        Contour C = T.tab[i];
        if (C.taille > 0)
            total_segments += (C.taille - 1);
    }
    printf("Nombre de contours : %d\n", T.taille);
    printf("Nombre total de segments : %d\n", total_segments);
}

void sauvegarder_contours_eps(Tableau_Contours T, char *filename, int largeur, int hauteur) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur ouverture fichier %s\n", filename);
        exit(1);
    }

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "newpath\n");
    
    for (unsigned int i = 0; i < T.taille; i++) {
        Contour C = T.tab[i];
        if (C.first != NULL) {
            Cellule_Liste_Point *pt = C.first;
            fprintf(f, "%.2f %.2f moveto\n", pt->data.x, (double)hauteur - pt->data.y);
            pt = pt->suiv;
            while (pt != NULL) {
                fprintf(f, "%.2f %.2f lineto\n", pt->data.x, (double)hauteur - pt->data.y);
                pt = pt->suiv;
            }
            fprintf(f, "closepath\n");
        }
    }
    fprintf(f, "fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
    printf("Fichier EPS généré : %s\n", filename);
}

void afficher_contours(Tableau_Contours T) {
    for (unsigned int i = 0; i < T.taille; i++) {
        Contour C = T.tab[i];
        Cellule_Liste_Point *courant = C.first;
        printf("Contour %d: ", i + 1);
        printf("(%.1f, %.1f),", courant->data.x, courant->data.y);
        courant = courant->suiv;
        while (courant != NULL) {
            Point p = courant->data;
            printf("(%.1f, %.1f)", p.x, p.y);
            courant = courant->suiv;
        }
        printf("\n");
        printf("Nombre de points : %d\n",C.taille);
        printf("Nombre de segments : %d\n",C.taille-1);
    }
}