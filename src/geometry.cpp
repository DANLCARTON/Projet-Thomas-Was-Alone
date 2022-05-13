#include <math.h>
#include "geometry.h"
#include <stdlib.h>

// Construit le point (x, y, z)
Point3D createPoint(float x, float y, float z){
    Point3D point;
    point.x=x;
    point.y=y;
    point.z=z;
    return point;
}


// Construit le vecteur (x, y, z)
Vector3D createVector(float x, float y, float z){
    Vector3D v;
    v.x=x;
    v.y=y;
    v.z=z;
    return v;
}


// Construit le vecteur reliant les points P1 et P2
Vector3D createVectorFromPoints(Point3D p1, Point3D p2){
    Vector3D v;
    v.x=p2.x-p1.x;
    v.y=p2.y-p1.y;
    v.z=p2.z-p1.z;
    return v;
}


// Construit le point P + V (i.e. translation de P par V)
Point3D pointPlusVector(Point3D p, Vector3D v){
    p.x=p.x+v.x;
    p.y=p.y+v.y;
    p.z=p.z+v.z;
    return p;
}


// Addition et soustraction des vecteurs V1 et V2
Vector3D addVectors(Vector3D v1, Vector3D v2){
    v1.x=v1.x+v2.x;
    v1.y=v1.y+v2.y;
    v1.z=v1.z+v2.z;
    return v1;
}

Vector3D subVectors(Vector3D v1, Vector3D v2){
    v1.x=v1.x-v2.x;
    v1.y=v1.y-v2.y;
    v1.z=v1.z-v2.z;
    return v1; 
    // Crée bien une copie de v1 dans la fonction et c'est ce nouveau vecteur qui sera retourné pas un v1 modifié
}


// Multiplication et division d'un vecteur V par un scalaire a
Vector3D multVector(Vector3D v, float a){
    v.x=v.x*a;
    v.y=v.y*a;
    v.z=v.z*a;
    return v;
}


Vector3D divVector(Vector3D v, float a){
    if (a==0){
        printf("On ne peut pas diviser par 0 !\n");
    }
    else{
        v.x=v.x/a;
        v.y=v.y/a;
        v.z=v.z/a;
        return v;
    }
}


// Produit scalaire des vecteurs V1 et V2
float dot(Vector3D a, Vector3D b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}


// Norme d'un vecteur V
float norm(Vector3D v){
    return(sqrt(v.x*v.x+v.y*v.y+v.z*v.z));
}


// Construit le vecteur normalisé du vecteur V
Vector3D normalize(Vector3D v){
    if (norm(v)==0){
        return v;
    }
    else{
        v.x=v.x/norm(v);
        v.y=v.y/norm(v);
        v.z=v.z/norm(v);
    return v;
    }
}


//afficher le contenu d'un point où d'un vecteur
void printPoint3D(Point3D p){
    printf ("(%f, %f, %f) \n",p.x,p.y, p.z);
}
void printVector3D(Vector3D v){
    printf ("(%f, %f, %f) \n",v.x,v.y, v.z);
}