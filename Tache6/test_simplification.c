#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    /* Déterminer le nom du fichier de sortie */
    char nom_sortie1[512];
    char nom_sortie2[512];
    strcpy(nom_sortie1, argv[1]);
    char *point = strrchr(nom_sortie1, '.'); 
    if (point != NULL) {
        *point = '\0';
    }
    strcpy(nom_sortie2, nom_sortie1);
    strcat(nom_sortie1, "_1.0.eps");
    strcat(nom_sortie2, "_2.0.eps");


    printf("Image: %s\n", argv[1]);
    Tableau_Contours COUNT1= simplification_final(tab, 1);
    sauvegarder_contours_eps(COUNT1, nom_sortie1, L, H);
    liberer_tableau_contours(&COUNT1);
    Tableau_Contours COUNT2= simplification_final(tab, 2);
    sauvegarder_contours_eps(COUNT2, nom_sortie2, L, H);
    liberer_tableau_contours(&COUNT2);
    
    liberer_tableau_contours(&tab);
    supprimer_image(&A);

}