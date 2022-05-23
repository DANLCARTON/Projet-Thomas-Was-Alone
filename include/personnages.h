#ifndef PERSONNAGES_H
#define PERSONNAGES_H

#include "colors.h"

typedef struct perso
{
    //position
    float px;
    float py;

    //vitesse
    float vx;
    float vy;

    //hauteur
    float height;
    float width;

    //true si on joue se cube là
    int isPlaying;
    int index; // numero du personnage

    ColorRGB color;  
}Perso;


Perso createPerso (float px, float py, float vx, float vy, float height, float width, int isPlaying, ColorRGB color, int index);
void drawPerso(Perso perso);
void fall (Perso perso, const float dt);
void jump (Perso perso, const float dt);
void goRight (Perso perso);
void goLeft (Perso perso);
void horizontalDeceleration (Perso perso);
void solidFiction (Perso perso);
void move (Perso perso, const float dt);  

#endif