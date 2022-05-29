#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "shape.hpp"
#include "personnages.hpp"
#include "quad_tree.hpp"

int checkCollision(int n, Perso perso, Platform listedesblocs[], int dir);

bool checkGround(const Perso perso, const int nbBlocs, const Platform listedesblocs[]);

void collision(const int nbPersos, Perso listedespersos[], const int nbBlocs, const Platform listedesblocs[], const Uint32 elapsedTime, Quadtree quadtree, int currentPerso);

bool victory(const int nbPersos, const Perso listedespersos[], const Goal listedesgoals[]);

#endif