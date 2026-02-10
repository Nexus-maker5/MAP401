#include <stdio.h>
#include <stdlib.h>
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
    ecrire_image(A);
    Contour C = calculer_contour(A);
    sauvegarder_contour_eps(C, "contour_resultat.eps", L, H);
    return 0;
}