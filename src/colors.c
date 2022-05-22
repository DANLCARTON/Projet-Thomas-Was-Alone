#include "../include/colors.h"
#include <stdlib.h>
#include <stdio.h>


// Construit la couleur (r, g, b)
ColorRGB createColor(float r, float g, float b){
    ColorRGB c;
    c.r=r;
    c.g=g;
    c.b=b;
    return c;
}


// Addition, soustraction et multiplication des couleurs C1 et C2
ColorRGB addColors(ColorRGB c1, ColorRGB c2){
    c1.r=c1.r+c2.r;
    c1.g=c1.g+c2.g;
    c1.b=c1.b+c2.b;
    return c1;
}

ColorRGB subColors(ColorRGB c1, ColorRGB c2){
    c1.r=c1.r-c2.r;
    c1.g=c1.g-c2.g;
    c1.b=c1.b-c2.b;
    return c1;
}

ColorRGB multColors(ColorRGB c1, ColorRGB c2){
    c1.r=c1.r*c2.r;
    c1.g=c1.g*c2.g;
    c1.b=c1.b*c2.b;
    return c1;
}


// Multiplication et division d une couleur C par un scalaire a
ColorRGB multColor(ColorRGB c, float a){
    c.r=c.r*a;
    c.g=c.g*a;
    c.b=c.b*a;
    return c;
}

ColorRGB divColor(ColorRGB c, float a){
    if (a==0){
        printf("On ne peut pas diviser par 0 !\n");
    }
    else{
        c.r=c.r/a;
        c.g=c.g/a;
        c.b=c.b/a;
        return c;
    }
}