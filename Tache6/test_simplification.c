#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"
#include "image.h"
#include "simplification.h"
#include "contour.h"


int main(int argc, char **argv){

    if (argc < 2) {
        printf("Usage: %s <fichier_image.pbm>\n", argv[0]);
        return 1;
    }

    Image A = lire_fichier_image(argv[1]);
    int L = largeur_image(A);
    int H = hauteur_image(A);

    Tableau_Contours tab = recuperer_contours(A);

    printf("Image: %s\n", argv[1]);
    Tableau_Contours COUNT1= simplification_final(tab, 1);
    sauvegarder_contours_eps(COUNT1, "contours_simplifies_eps_1.0.eps", L, H);
    Tableau_Contours COUNT2= simplification_final(tab, 2);
    sauvegarder_contours_eps(COUNT2, "contours_simplifies_eps_2.0.eps", L, H);

}