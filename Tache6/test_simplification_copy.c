#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom2d.h"
#include "image.h"
#include "simplification.h"
#include "contour.h"


int main(int argc, char **argv){

    if (argc < 3) {
        printf("Usage: %s <fichier_image.pbm> <distance>\n", argv[0]);
        return 1;
    }

    Image A = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);
    int L = largeur_image(A);
    int H = hauteur_image(A);

    Liste_Contour tab = recuperer_contours(A);

    /* Déterminer le nom du fichier de sortie */
    char nom_sortie1[512];
    strcpy(nom_sortie1, argv[1]);
    char *point = strrchr(nom_sortie1, '.'); 
    if (point != NULL) {
        *point = '\0';
    }
    strcat(nom_sortie1, ".eps");



    printf("Image: %s\n", argv[1]);

    Liste_Contour COUNT1= simplification_final(tab, d);
    sauvegarder_contours_eps(COUNT1, nom_sortie1, L, H);
    afficher_stats_contours(COUNT1);
    supprimer_liste_Contour(COUNT1);
    
    supprimer_liste_Contour(tab);
    supprimer_image(&A);

}