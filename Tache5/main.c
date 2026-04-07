#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Usage: %s <fichier_image.pbm>\n", argv[0]);
        return 1;
    }

    Image A = lire_fichier_image(argv[1]);
    int L = largeur_image(A);
    int H = hauteur_image(A);

    Liste_Contour tab = recuperer_contours(A);

    printf("Image: %s\n", argv[1]);

    /* Déterminer le nom du fichier de sortie */
    char nom_sortie[512];
    strcpy(nom_sortie, argv[1]);
    char *point = strrchr(nom_sortie, '.'); 
    if (point != NULL) {
        *point = '\0';
    }
    strcat(nom_sortie, ".eps");

    sauvegarder_contours_eps(tab, nom_sortie, L, H);
    
    /*Nettoyage*/
    supprimer_liste_Contour(tab);
    supprimer_image(&A);
    return 0;
}