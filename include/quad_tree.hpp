#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <stdio.h>
#include <stdlib.h>
#include "geometry.hpp"
#include "shape.hpp"
#include "personnages.hpp"


typedef struct Quadtree {
    float qtx;
    float qty;
    float qtw;
    float qth;
    struct Quadtree *northwest_child;
    struct Quadtree *northeast_child;
    struct Quadtree *southwest_child;
    struct Quadtree *southeast_child;
    struct Quadtree *parent; 
} Quadtree;


typedef struct Map {
    float x;
    float y;
    float w;
    float h;
} Map;


Map createMap (Point3D pointHG, Vector3D taille);
Quadtree create_QuadTree (Map map);
bool if_leaf (Quadtree quadtree);
Map zoneLeaf (Map map);
bool DetectePersoInLeaf (const Perso perso, Quadtree quadtree);
int BlocsInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs);
int nbCollisionInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs, const int nbPersos, Perso listedespersos[]);
void AppliqueQuadTree (Map map, Platform listedesblocs[], const Perso perso, const int nbBlocs);

#endif