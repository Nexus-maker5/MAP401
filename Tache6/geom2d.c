#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include"geom2d.h"

Point set_point(double x,double y){
    Point P={x,y};
    return P;
}

Vecteur set_vecteur(Point P1,Point P2){
    Vecteur V={P2.x-P1.x,P2.y-P1.y};
    return V;
}


Point add_point(Point P1,Point P2){
    return set_point(P1.x+P2.x,P1.y+P2.y);
}

Vecteur add_vecteur(Vecteur V1,Vecteur V2){
    Vecteur V={V1.x+V2.x,V1.y+V2.y};
    return V;
}

Point reel_point(double a, Point P){
    return set_point(a*P.x,a*P.y);
}

Vecteur reel_vecteur(double a, Vecteur V){
    Vecteur V1={a*V.x,a*V.y};
    return V1;
}

double scalaire(Vecteur V1,Vecteur V2){
    return((V1.x*V2.x)+(V1.y*V2.y));
}

double norme(Vecteur V){
    return sqrt(pow(V.x,2)+pow(V.y,2));
}

double distance_point(Point P1,Point P2){
    return sqrt(pow((P1.x-P2.x),2)+pow((P1.y-P2.y),2));
}

double distance_point_segment(Point P,Segment S){
    double d;
    if(distance_point(S.A,S.B)==0){
        Vecteur AP= set_vecteur(S.A,P);
        d=norme(AP);
    }
    else{
        double lamda;
        Vecteur AP= set_vecteur(S.A,P);
        Vecteur BP= set_vecteur(S.B,P);
        Vecteur AB= set_vecteur(S.A,S.B);
        lamda=scalaire(AP,AB)/scalaire(AB,AB);
        if(lamda < 0){
            d=norme(AP);
        }
        else if(0 <= lamda && lamda <= 1){
            Point P1= set_point(S.B.x-S.A.x,S.B.y-S.A.y);
            P1=reel_point(lamda,P1);
            Point Q=add_point(S.A,P1);
            Vecteur QP= set_vecteur(Q,P);
            d=norme(QP);
        }
        else{
            d=norme(BP);
        }
    }
    return d;
}