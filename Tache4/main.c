#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
int main(int argc, char **argv){
    
    if (argc < 2) {
        printf("Usage: %s <fichier_image> \n",argv[0]);
        return 1;
    }

    Image A=lire_fichier_image(argv[1]);
    int L = largeur_image(A);
    int H = hauteur_image(A);
    
    /* Déterminer le nom du fichier de sortie */
    char nom_sortie[512];
    strcpy(nom_sortie, argv[1]);
    char *point = strrchr(nom_sortie, '.'); 
    if (point != NULL) {
        *point = '\0';
    }
    strcat(nom_sortie, ".eps");
    
    /* Calculer le contour et sauvegarder le résultat dans un fichier EPS */
    Contour C = calculer_contour(A);
    sauvegarder_contour_eps(C, nom_sortie, L, H);

    /*Nettoyage*/
    supprimer_liste_Point(C);
    supprimer_image(&A);
    return 0;
}