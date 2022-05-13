#include "personnages.h"

//constante de gravitation
float g=9.81;

void fall(Perso* perso, float dt){
    perso->py=perso->py+perso->vy*dt+1/2*g*dt*dt;
    perso->vy=perso->vy+g*dt;
}
}
