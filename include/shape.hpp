#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "geometry.hpp"
#include "colors.hpp"
#include "personnages.hpp"

typedef struct Rectangle {
    Point3D position;
    Vector3D size;
    ColorRGB color; // les plateformes ont toutes la même couleur
    int solid; // sert pour l'HUD, 0 = non | 1 = oui
    int moving; // 0 = non | 1 = oui
    int dirMove; // 0 = haut-bas | 1 = gauche-droite mais on verra ça une fois qu'on aura des plateforme qui bougent pas et qui marchent
    int distanceMove; // 0 si elle bouge pas, X étant de combien elle bouge.
} Platform, HUD;

typedef struct Goal {
    Perso perso; // perso rattaché au goal
    Point3D position;
    Vector3D size;
}Goal;

Platform createPlatform(Point3D pos, Vector3D size);
Platform createMovingPlatform(Point3D pos, Vector3D size);
Goal createGoal(Perso perso, Point3D pos, Vector3D size);

#endif