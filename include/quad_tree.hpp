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

typedef struct DataNode {
    int Xmap;
    int Ymap;
    Point3D NOpoint;
    Point3D NEpoint;
    Point3D SOpoint;
    Point3D SEpoint;
    int capacite;
} DataNode;

typedef struct Map {
    float x;
    float y;
    float w;
    float h;
} Map;


// Quadtree *new_quad_tree (int x, int y);
// void clean_tree (Quadtree *tr);
// Quadtree *join_tree(Quadtree *northwest_child, Quadtree *northeast_child, Quadtree *southwest_child, Quadtree southeast_child, int node);
// void print_tree (Quadtree *tr);
// int nodesCount (Quadtree *tr);
Map createMap (Point3D pointHG, Vector3D taille);
Quadtree create_QuadTree (Map map);
bool if_leaf (Quadtree quadtree);
Map zoneLeaf (Map map);
bool DetectePersoInLeaf (const Perso perso, Quadtree quadtree);
int BlocsInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs);
int nbCollisionInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs, const int nbPersos, Perso listedespersos[]);
void AppliqueQuadTree (Map map, Platform listedesblocs[], const Perso perso, const int nbBlocs);

#endif