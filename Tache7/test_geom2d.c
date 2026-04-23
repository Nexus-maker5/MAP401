#include <stdio.h>
#include <math.h>
#include "geom2d.h"

int main(void)
{
    Point P, A, B;

    printf("Entrez les coordonnees du point P (x y) : ");
    scanf("%lf %lf", &P.x, &P.y);

    printf("Entrez les coordonnees du point A (x y) : ");
    scanf("%lf %lf", &A.x, &A.y);

    printf("Entrez les coordonnees du point B (x y) : ");
    scanf("%lf %lf", &B.x, &B.y);

    Segment S;
    S.A = A;
    S.B = B;

    double d = distance_point_segment(P, S);
    printf("Distance entre P et S = %.2f\n", d);

    printf("\n===== FIN DES TESTS =====\n");
    return 0;
}
