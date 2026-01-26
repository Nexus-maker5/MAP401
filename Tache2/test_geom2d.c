#include <stdio.h>
#include <math.h>
#include "geom2d.h"

int main() {

    Point P1, P2, P3;
    Vecteur V1, V2, V3;
    double a;

    printf("Entrez les coordonnees du point P1 (x y) : ");
    scanf("%lf %lf", &P1.x, &P1.y);

    printf("Entrez les coordonnees du point P2 (x y) : ");
    scanf("%lf %lf", &P2.x, &P2.y);

    V1 = set_vecteur(P1, P2);
    printf("\nVecteur V1 = P1P2 = (%.2f, %.2f)\n", V1.x, V1.y);

    P3 = add_point(P1, P2);
    printf("Addition des points : P1 + P2 = (%.2f, %.2f)\n", P3.x, P3.y);

    printf("\nEntrez les coordonnees du vecteur V2 (x y) : ");
    scanf("%lf %lf", &V2.x, &V2.y);

    /* --- add_vecteur --- */
    V3 = add_vecteur(V1, V2);
    printf("Addition des vecteurs : V1 + V2 = (%.2f, %.2f)\n", V3.x, V3.y);

    printf("\nEntrez un reel a : ");
    scanf("%lf", &a);

    Point P4 = reel_point(a, P1);
    printf("a * P1 = (%.2f, %.2f)\n", P4.x, P4.y);

    Vecteur V4 = reel_vecteur(a, V1);
    printf("a * V1 = (%.2f, %.2f)\n", V4.x, V4.y);

    double s = scalaire(V1, V2);
    printf("\nProduit scalaire <V1 , V2> = %.2f\n", s);

    double n = norme(V1);
    printf("Norme de V1 = %.2f\n", n);

    double d = distance_point(P1, P2);
    printf("Distance entre P1 et P2 = %.2f\n", d);

    printf("\n===== FIN DES TESTS =====\n");

    return 0;
}
