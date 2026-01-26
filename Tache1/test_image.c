#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Usage: %s <fichier_image> \n",argv[0]);
        return 1;
    }
    Image A=lire_fichier_image(argv[1]);
    ecrire_image(A);
    Image Aneg=negatif_image(A);
    printf("Negation:\n");
    ecrire_image(Aneg);

}