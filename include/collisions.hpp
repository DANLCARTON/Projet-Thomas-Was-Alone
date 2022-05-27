#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "shape.hpp"
#include "personnages.hpp"

int checkCollision(int n, Perso perso, Platform listedesblocs[], int dir);

bool checkGround(const Perso perso, const int nbBlocs, const Platform listedesblocs[]);

void collision(const int nbPersos, Perso listedespersos[], const int nbBlocs, const Platform listedesblocs[], const Uint32 elapsedTime);

#endif