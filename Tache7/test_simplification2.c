#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geom2d.h"
#include "liste.h"
#include "image.h"
#include "contour.h"
#include "simplification.h"


int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Usage: %s <fichier_image.pbm> <distance>\n", argv[0]);
        return 1;
    }

    Image A = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);
    int L = (int)largeur_image(A);
    int H = (int)hauteur_image(A);

    Liste_Contour tab = recuperer_contours(A);
    printf("Image: %s\n", argv[1]);
    afficher_stats_contours(tab);

    /* Construire le nom du fichier de sortie */
        char nom_sortie[512];
    strcpy(nom_sortie, argv[1]);
    char *point = strrchr(nom_sortie, '.'); 
    if (point != NULL) {
        *point = '\0';
    }
    strcat(nom_sortie, ".eps");

    /* Simplification avec la distance fournie */
    Liste_ContourBz bz = simplification_final_bezier3(tab, d);
    sauvegarder_contoursbz_eps(bz, nom_sortie, L, H);
    supprimer_liste_ContourBz(bz);

    supprimer_liste_Contour(tab);
    supprimer_image(&A);
    return 0;
}
