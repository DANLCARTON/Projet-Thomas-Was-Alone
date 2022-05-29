#ifndef PERSONNAGES_HPP
#define PERSONNAGES_HPP

#include "colors.hpp"
#include "personnages.hpp"
#include <SDL2/SDL.h>

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

    ColorRGB color;

    //Déplacement
    //dt est le temps écoulé entre chaque frame (= elapsedTime de App.cpp)
    void jump();

    void fall(const Uint32 dt);

    void goRight();

    void goLeft();

    void horizontalDeceleration();

    void solidFriction();

    void move(const Uint32 dt);
    
}Perso;


Perso createPerso (float px, float py, float vx, float vy, float height, float width, ColorRGB color);
void drawPerso(Perso perso);


#endif