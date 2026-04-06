#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/* test de la lecture d'une image et de son affichage à l'ecran */

int main(int argc, char **argv){
    
    if (argc < 2) {
        printf("Usage: %s <fichier_image> \n",argv[0]);
        return 1;
    }
    /*Image de base*/
    Image A=lire_fichier_image(argv[1]);
    printf("Image lue:\n");
    ecrire_image(A);

    /*Negation*/
    Image Aneg=negatif_image(A);
    printf("Negation:\n");
    ecrire_image(Aneg);

}