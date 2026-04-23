#include "contour.h"
#include "geom2d.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

/* Avancer le robot d'une case */
void avancer(robot *R)
{
    switch (R->o) {
        case Nord:  R->y -= 1; break;
        case Est:   R->x += 1; break;
        case Sud:   R->y += 1; break;
        case Ouest: R->x -= 1; break;
    }
}

/* Faire tourner le robot à gauche */
void tourner_a_gauche(robot *R)
{
    switch (R->o) {
        case Nord:  R->o = Ouest; break;
        case Est:   R->o = Nord;  break;
        case Sud:   R->o = Est;   break;
        case Ouest: R->o = Sud;   break;
    }
}

/* Faire tourner le robot à droite */
void tourner_a_droite(robot *R)
{
    switch (R->o) {
        case Nord:  R->o = Est;   break;
        case Est:   R->o = Sud;   break;
        case Sud:   R->o = Ouest; break;
        case Ouest: R->o = Nord;  break;
    }
}

/* Mettre à jour l'orientation du robot selon l'image */
void nouvelle_orientation(Image I, robot *R)
{
    Pixel pG, pD;
    int rx = (int)R->x;
    int ry = (int)R->y;

    switch (R->o) {
        case Nord:
            pG = get_pixel_image(I, rx,     ry);
            pD = get_pixel_image(I, rx + 1, ry);
            break;
        case Est:
            pG = get_pixel_image(I, rx + 1, ry);
            pD = get_pixel_image(I, rx + 1, ry + 1);
            break;
        case Sud:
            pG = get_pixel_image(I, rx + 1, ry + 1);
            pD = get_pixel_image(I, rx,     ry + 1);
            break;
        case Ouest:
            pG = get_pixel_image(I, rx,     ry + 1);
            pD = get_pixel_image(I, rx,     ry);
            break;
        default:
            return;
    }

    if (pG == NOIR)
        tourner_a_gauche(R);
    else if (pD == BLANC)
        tourner_a_droite(R);
}

/* Trouver le pixel de départ */
Point trouver_pixel_depart(Image I)
{
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    for (UINT j = 1; j <= H; j++) {
        for (UINT i = 1; i <= L; i++) {
            if (get_pixel_image(I, (int)i, (int)j) == NOIR)
                return set_point((double)i, (double)j);
        }
    }
    return set_point(-1.0, -1.0);
}

/* Créer une image-masque */
Image creer_image_masque(Image I)
{
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    Image I_masque = creer_image(L, H);
    for (UINT j = 1; j <= H; j++) {
        for (UINT i = 1; i <= L; i++) {
            Pixel p1 = get_pixel_image(I, (int)i, (int)j);
            Pixel p2 = get_pixel_image(I, (int)i, (int)j - 1);
            Pixel val = (p1 == NOIR && p2 == BLANC) ? NOIR : BLANC;
            set_pixel_image(I_masque, (int)i, (int)j, val);
        }
    }
    return I_masque;
}

/* Mémoriser la position du robot dans le contour */
void memoriser_position(Contour *C, robot *R)
{
    *C = ajouter_element_liste_Point(*C, set_point(R->x, R->y));
}

/* Calculer le contour à partir d'un pixel de départ */
Contour calculer_contour(Image I, Image *I_masque, Point pixel)
{
    robot R;
    Contour C = creer_liste_Point_vide();
    double x0 = pixel.x - 1;
    double y0 = pixel.y - 1;

    R.x = x0; R.y = y0; R.o = Est;
    do {
        memoriser_position(&C, &R);
        avancer(&R);
        nouvelle_orientation(I, &R);
        if (R.o == Est)
            set_pixel_image(*I_masque, (int)R.x + 1, (int)R.y + 1, BLANC);
    } while (!(R.x == x0 && R.y == y0 && R.o == Est));

    memoriser_position(&C, &R);
    return C;
}

/* Récupérer tous les contours de l'image */
Liste_Contour recuperer_contours(Image I)
{
    Liste_Contour L = creer_liste_Contour_vide();
    Image I_masque = creer_image_masque(I);

    while (1) {
        Point depart = trouver_pixel_depart(I_masque);
        if (depart.x == -1.0 && depart.y == -1.0)
            break;
        Contour C = calculer_contour(I, &I_masque, depart);
        L = ajouter_element_liste_Contour(L, C);
    }
    supprimer_image(&I_masque);
    return L;
}

/* Afficher les statistiques des contours */
void afficher_stats_contours(Liste_Contour L)
{
    int total_segments = 0;
    Cellule_Liste_Contour *cel = L.first;
    while (cel != NULL) {
        if (cel->data.taille > 0)
            total_segments += (int)(cel->data.taille - 1);
        cel = cel->suiv;
    }
    printf("Nombre de contours : %u\n", L.taille);
    printf("Nombre total de segments : %d\n", total_segments);
}

/* Afficher les contours */
void afficher_contours(Liste_Contour L)
{
    unsigned int i = 1;
    Cellule_Liste_Contour *cel = L.first;
    while (cel != NULL) {
        Contour C = cel->data;
        Cellule_Liste_Point *courant = C.first;
        printf("Contour %u: ", i);
        while (courant != NULL) {
            printf("(%.1f, %.1f)", courant->data.x, courant->data.y);
            if (courant->suiv != NULL)
                printf(", ");
            courant = courant->suiv;
        }
        printf("\n");
        i++;
        cel = cel->suiv;
    }
}

/* Sauvegarder les contours (points) dans un fichier EPS */
void sauvegarder_contours_eps(Liste_Contour L, char *filename, int largeur, int hauteur)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur ouverture fichier %s\n", filename);
        exit(1);
    }
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "newpath\n");

    Cellule_Liste_Contour *cel = L.first;
    while (cel != NULL) {
        Contour C = cel->data;
        if (C.first != NULL) {
            Cellule_Liste_Point *pt = C.first;
            fprintf(f, "%.2f %.2f moveto\n", pt->data.x, (double)hauteur - pt->data.y);
            pt = pt->suiv;
            while (pt != NULL) {
                fprintf(f, "%.2f %.2f lineto\n", pt->data.x, (double)hauteur - pt->data.y);
                pt = pt->suiv;
            }
            fprintf(f, "closepath\n");
        }
        cel = cel->suiv;
    }
    fprintf(f, "fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
    printf("Fichier EPS genere : %s\n", filename);
}

/* Sauvegarder les contours Bezier3 dans un fichier EPS
   Utilise la commande PostScript "curveto" pour les courbes de Bezier cubiques.
   Syntaxe : x1 y1 x2 y2 x3 y3 curveto
   où (x1,y1)=C1, (x2,y2)=C2, (x3,y3)=C3 ; C0 est le point courant. */
void sauvegarder_contoursbz_eps(Liste_ContourBz L, char *filename, int largeur, int hauteur)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur ouverture fichier %s\n", filename);
        exit(1);
    }
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "newpath\n");

    Cellule_Liste_ContourBz *cel = L.first;
    while (cel != NULL) {
        ContourBz C = cel->data;
        if (C.first != NULL) {
            Cellule_Liste_Bezier3 *pt = C.first;
            /* Positionner au point de départ C0 de la première courbe */
            fprintf(f, "%.2f %.2f moveto\n",
                    pt->data.C0.x, (double)hauteur - pt->data.C0.y);
            /* Émettre une commande curveto pour chaque courbe Bezier3 */
            while (pt != NULL) {
                fprintf(f, "%.2f %.2f %.2f %.2f %.2f %.2f curveto\n",
                        pt->data.C1.x, (double)hauteur - pt->data.C1.y,
                        pt->data.C2.x, (double)hauteur - pt->data.C2.y,
                        pt->data.C3.x, (double)hauteur - pt->data.C3.y);
                pt = pt->suiv;
            }
            fprintf(f, "closepath\n");
        }
        cel = cel->suiv;
    }
    fprintf(f, "fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
    printf("Fichier EPS genere : %s\n", filename);
}
