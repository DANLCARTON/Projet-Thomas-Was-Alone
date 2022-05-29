#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/geometry.hpp"
#include "../include/quad_tree.hpp"
#include "../include/shape.hpp"
#include "../include/personnages.hpp"


Map createMap (Point3D pointHG, Vector3D taille)
{
    Map map;
    map.x = pointHG.x;
    map.y = pointHG.y;
    map.w = taille.x;
    map.h = taille.y;
    return map;
}

Quadtree create_QuadTree (Map map)
{
    Quadtree quadtree;

    quadtree.qtx = map.x;
    quadtree.qty = map.y;
    quadtree.qtw = map.w;
    quadtree.qth = map.h;

    quadtree.northwest_child->qtx = map.x;
    quadtree.northwest_child->qty = map.y;
    quadtree.northwest_child->qtw = map.w / 2;  
    quadtree.northwest_child->qth = map.h / 2;
    
    quadtree.northeast_child->qtx = map.x + map.w / 2;
    quadtree.northeast_child->qty = map.y;
    quadtree.northeast_child->qtw = map.w / 2;  
    quadtree.northeast_child->qth = map.h / 2;
    
    quadtree.southwest_child->qtx = map.x;
    quadtree.southwest_child->qty = map.y / 2;
    quadtree.southwest_child->qtw = map.w / 2;  
    quadtree.southwest_child->qth = map.h / 2;
    
    quadtree.southeast_child->qtx = map.x + map.w / 2;
    quadtree.southeast_child->qty = map.y / 2;
    quadtree.southeast_child->qtw = map.w / 2;  
    quadtree.southeast_child->qth = map.h / 2;

    quadtree.parent->qtx = NULL;
    quadtree.parent->qty = NULL;
    quadtree.parent->qtw = NULL;
    quadtree.parent->qth = NULL;

    return quadtree;
}

// return True if the node is a leaf (it has no children)
bool is_leaf (Quadtree quadtree)
{
    if (quadtree.northwest_child == nullptr && quadtree.northeast_child == nullptr && quadtree.southwest_child == nullptr && quadtree.southeast_child == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// determine la zone dans laquelle se situe la feuille
Map zoneLeaf (Map map)
{
    Quadtree quadtree = create_QuadTree (map);

    if (is_leaf (quadtree) == false)
    {
        return map;
    }
    else
    {
        quadtree.qtx = map.x;
        quadtree.qty = map.y;
        quadtree.qtw = map.w;
        quadtree.qth = map.h;

        return map;
    }
}


bool DetectePersoInLeaf (const Perso perso, Quadtree quadtree)
{
    if (is_leaf (quadtree) == false)
    {
        return false;
    }
    else 
    {
        if ((perso.px + perso.width > quadtree.qtx || perso.px <= quadtree.qtx + quadtree.qtw) && (perso.py - perso.height <= quadtree.qty || perso.py >= quadtree.qty - quadtree.qth))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


// trouve le nombre de bloc dans la feuille
int BlocsInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs)
{
    if (is_leaf (quadtree) == false)
    {
        return -1;
    }
    else
    {
        int BlocL = 0;
        for (int i = 0; i < nbBlocs; i++)
        {
            if ((listedesblocs[i].position.x + listedesblocs[i].size.x >= quadtree.qtx || listedesblocs[i].position.x <= quadtree.qtx + quadtree.qtw) && (listedesblocs[i].position.y - listedesblocs[i].size.y <= quadtree.qty || listedesblocs[i].position.y >= quadtree.qty - quadtree.qth))
            {
                BlocL ++;
            }
        }
        return BlocL;
    }

}



int nbCollisionInLeaf(Platform listedesblocs[], Quadtree quadtree, const int nbBlocs, const int nbPersos, Perso listedespersos[])
{
    if (is_leaf (quadtree) == false)
    {
        return -1;
    }
    else
    {
        // maximun 4 * BlocsInLeaf
        int CollisionL = 0;
        for (int i = 0; i < BlocsInLeaf(listedesblocs, quadtree, nbBlocs); i++)
        {
            if (listedesblocs[i].position.x > quadtree.qtx && listedesblocs[i].position.x + listedesblocs[i].size.x < quadtree.qtx + quadtree.qtw && listedesblocs[i].position.y < quadtree.qty && listedesblocs[i].position.y - listedesblocs[i].size.y > quadtree.qty - quadtree.qth)
            {
                CollisionL += 4; // problème du placement du bloc par rapport au sol et au plafond donc potentiellement 3 dans certains cas
            }

            if (listedesblocs[i].position.x > quadtree.qtx && listedesblocs[i].position.x + listedesblocs[i].size.x < quadtree.qtx + quadtree.qtw && (listedesblocs[i].position.y - listedesblocs[i].size.y < quadtree.qty || listedesblocs[i].position.y > quadtree.qty - quadtree.qth) || (listedesblocs[i].position.y < quadtree.qty && listedesblocs[i].position.y - listedesblocs[i].size.y > quadtree.qty - quadtree.qth) && (listedesblocs[i].position.x + listedesblocs[i].size.x > quadtree.qtx || listedesblocs[i].position.x < quadtree.qtx + quadtree.qtw))
            {
                CollisionL += 3; // problème du placement du bloc par rapport au sol et au plafond donc potentiellement 2 dans certains cas
            }

            if ((listedesblocs[i].position.x < quadtree.qtx && listedesblocs[i].position.x + listedesblocs[i].size.x > quadtree.qtx && listedesblocs[i].position.y > quadtree.qty && listedesblocs[i].position.y - listedesblocs[i].size.y < quadtree.qty) || (listedesblocs[i].position.x < quadtree.qtx + quadtree.qtw && listedesblocs[i].position.x + listedesblocs[i].size.x > quadtree.qtx + quadtree.qtw && listedesblocs[i].position.y > quadtree.qty && listedesblocs[i].position.y - listedesblocs[i].size.y < quadtree.qty) || (listedesblocs[i].position.x < quadtree.qtx && listedesblocs[i].position.x + listedesblocs[i].size.x > quadtree.qtx && listedesblocs[i].position.y > quadtree.qty - quadtree.qth && listedesblocs[i].position.y - listedesblocs[i].size.y < quadtree.qty - quadtree.qth) || (listedesblocs[i].position.x < quadtree.qtx + quadtree.qtw && listedesblocs[i].position.x + listedesblocs[i].size.x > quadtree.qtx + quadtree.qtw && listedesblocs[i].position.y > quadtree.qty - quadtree.qth && listedesblocs[i].position.y - listedesblocs[i].size.y < quadtree.qty - quadtree.qth))
            {
                CollisionL += 2; // ici pas de soucis c'est 2 pas de doute
            }

            if ((listedesblocs[i].position.x + listedesblocs[i].size.x == quadtree.qtx) || (listedesblocs[i].position.x == quadtree.qtx + quadtree.qtw) || (listedesblocs[i].position.y - listedesblocs[i].size.y == quadtree.qty) || (listedesblocs[i].position.y == quadtree.qty - quadtree.qth))
            {
                CollisionL ++ ;
            }
        }
        for (int n = 0; n < nbPersos; n++)
        {
            Perso* perso=&listedespersos[n];

            if (perso[n].px > quadtree.qtx && perso[n].px + perso[n].width < quadtree.qtx + quadtree.qtw && perso[n].py < quadtree.qty && perso[n].py - perso[n].height > quadtree.qty - quadtree.qth)
            {
                CollisionL += 4; // problème du placement du bloc par rapport au sol et au plafond donc potentiellement 3 dans certains cas
            }

            if (perso[n].px > quadtree.qtx && perso[n].px + perso[n].width < quadtree.qtx + quadtree.qtw && (perso[n].py - perso[n].height < quadtree.qty || perso[n].py > quadtree.qty - quadtree.qth) || (perso[n].py < quadtree.qty && perso[n].py - perso[n].height > quadtree.qty - quadtree.qth) && (perso[n].px+ perso[n].width > quadtree.qtx || perso[n].px < quadtree.qtx + quadtree.qtw))
            {
                CollisionL += 3; // problème du placement du bloc par rapport au sol et au plafond donc potentiellement 2 dans certains cas
            }

            if ((perso[n].px < quadtree.qtx && perso[n].px + perso[n].width > quadtree.qtx && perso[n].py > quadtree.qty && perso[n].py - perso[n].height < quadtree.qty) || (perso[n].px < quadtree.qtx + quadtree.qtw && perso[n].px + perso[n].width > quadtree.qtx + quadtree.qtw && perso[n].py > quadtree.qty && perso[n].py - perso[n].height < quadtree.qty) || (perso[n].px < quadtree.qtx && perso[n].px + perso[n].width > quadtree.qtx && perso[n].py > quadtree.qty - quadtree.qth && perso[n].py - perso[n].height < quadtree.qty - quadtree.qth) || (perso[n].px < quadtree.qtx + quadtree.qtw && perso[n].px + perso[n].width > quadtree.qtx + quadtree.qtw && perso[n].py > quadtree.qty - quadtree.qth && perso[n].py - perso[n].height < quadtree.qty - quadtree.qth))
            {
                CollisionL += 2; // ici pas de soucis c'est 2 pas de doute
            }

            if (perso[n].px + perso[n].width == quadtree.qtx || perso[n].px == quadtree.qtx + quadtree.qtw || perso[n].py - perso[n].height == quadtree.qty || perso[n].py == quadtree.qty - quadtree.qth)
            {
                CollisionL ++;
            }
        }
        return CollisionL;
    }
}


//void AppliqueQuadTree (Map map, Platform listedesblocs[], const Perso perso, const int nbBlocs, const int nbPersos)
//{
    //Quadtree quadtree = create_QuadTree (map);
    //nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos);
//
//}
//


// Quadtree *new_quad_tree(int x, int y)
// {
//     Quadtree *tr = malloc(sizeof(*tr));

//     if (tr == NULL)
//     {
//         fprintf(stderr, "Erreur allocation.\n");
//         exit(EXIT_FAILURE);
//     }

//     else
//     {
//         tr.qtx = x;
//         tr.qty = y;
//         tr->northwest_child = NULL;
//         tr->northeast_child = NULL;
//         tr->southwest_child = NULL;
//         tr->southeast_child = NULL;
//         tr->parent = NULL;  
//     }
    
//     return tr;
// }


// void clean_tree (Quadtree *tr)
// {
//     if ( tr == NULL)
//     {
//         return;
//     }
//     clean_tree(tr->northwest_child);
//     clean_tree(tr->northeast_child);
//     clean_tree(tr->southwest_child);
//     clean_tree(tr->southeast_child);
//     free(tr);
// }


// Quadtree *join_tree(Quadtree *northwest_child, Quadtree *northeast_child, Quadtree *southwest_child, Quadtree southeast_child, int node)
// {
//     Quadtree *tr = new_quad_tree(node);

//     tr->northwest_child = northwest_child;
//     tr->northeast_child = northeast_child;
//     tr->southwest_child = southwest_child;
//     tr->southeast_child = southeast_child;

//     if (northwest_child != NULL)
//     {
//         northwest_child->parent = tr;
//     }
//     if (northeast_child != NULL)
//     {
//         northeast_child->parent = tr;
//     }
//     if (southeast_child != NULL)
//     {
//         southwest_child->parent = tr;
//     }
//     if (southeast_child != NULL)
//     {
//         southesat_child->parent = tr;
//     }
//     return tr;
// }

// void print_tree (Quadtree *tr)
// {
//     if (tr == NULL)
//     {
//         return;
//     }

//     if (tr->parent != NULL)
//     {
//         printf("(%d) -> %d\n"), tr->parent->value, tr->value);    
//     }
//     else
//     {
//         printf("(%d)\n", tr->value)
//     }

//     if (tr->northwest_child != NULL)
//     {
//         print_tree (tr->northwest_child);
//     }
//     if (tr->northeast_child != NULL)
//     {
//         print_tree (tr->northeast_child);
//     }
//     if (tr->southwest_child != NULL)
//     {
//         print_tree (tr->southwest_child);
//         tr->
//     }
//     if (tr->southeast_child != NULL)
//     {
//         print_tree (tr->southeast_child);
// }


// int nodesCount (Quadtree *tr)
// {
//     if (tr->northwest_child != NULL && tr->northeast_child != NULL && tr->southwest_child != NULL && tr->southeast_child != NULL)
//     {
//         return (tr->northwest_child->nodesCount() + tr->northeast_child->nodesCount() + tr->southwest_child->nodesCount() + tr->southeast_child->nodesCount() + 1); 
//     }
//     else if (tr->northwest_child != NULL)
//     {
//         return (tr->northwest_child->nodesCount() + 1);
//     }
//     else if (tr->northeast_child != NULL)
//     {
//         return (tr->northeast_child->nodesCount() + 1);
//     }
//     else if (tr->southwest_child != NULL)
//     {
//         return (tr->southwest_child->nodesCount() + 1);
//     }
//     else if (tr->southeast_child != NULL)
//     {
//         return (tr->southeast_child->nodesCount() + 1);
//     }
//     else
//     {
//         return 1;
//     }
// }
