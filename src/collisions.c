#include "../include/shape.h"
#include "../include/personnages.h"

Platform listedesblocs[];

int checkCollision(int n, Perso perso, Platform listedesblocs[], int dir) {
    int collision = 0;
    for (int i = 0; i <= n; i++) {
        printf("nb %i\n", i);
        printf("perso x %f\n", perso.px);
        printf("perso sx %f\n", perso.width);
        printf("perso y %f\n", perso.py);
        printf("perso sy %f\n", perso.height);
        printf("bloc x %f\n", listedesblocs[i].position.x);
        printf("bloc sx %f\n", listedesblocs[i].size.x);
        printf("bloc y %f\n", listedesblocs[i].position.y);
        printf("bloc sy %f\n", listedesblocs[i].size.y);
        printf("dir %i\n", dir);
        if (dir == 100 // DROITE
            && perso.py-perso.height < listedesblocs[i].position.y 
            && perso.py > listedesblocs[i].position.y-listedesblocs[i].size.y 
            && perso.px+perso.width >= listedesblocs[i].position.x
            && perso.px < listedesblocs[i].position.x+listedesblocs[i].size.x) {
            printf("if 1\n");
            perso.px-=10;
            collision = 1;
            return collision;
        } else if (dir == 113 // GAUCHE
                    && perso.py-perso.height < listedesblocs[i].position.y 
                    && perso.py > listedesblocs[i].position.y-listedesblocs[i].size.y 
                    && perso.px <= listedesblocs[i].position.x+listedesblocs[i].size.x
                    && perso.px+perso.width > listedesblocs[i].position.x) {
            printf("if 2\n");
            perso.px+=10;
            collision = 1;
            return collision;
        } else if (dir == 122 // HAUT
                    && perso.px+perso.width > listedesblocs[i].position.x 
                    && perso.px < listedesblocs[i].position.x+listedesblocs[i].size.x 
                    && perso.py >= listedesblocs[i].position.y-listedesblocs[i].size.y
                    && perso.py-perso.height < listedesblocs[i].position.y) {
            printf("if 3\n");
            perso.py-=10;
            collision = 1;
            return collision;
        } else if (dir == 115 // BAS
                    && perso.px+perso.width > listedesblocs[i].position.x 
                    && perso.px < listedesblocs[i].position.x+listedesblocs[i].size.x 
                    && perso.py-perso.height <= listedesblocs[i].position.y
                    && perso.py > listedesblocs[i].position.y-listedesblocs[i].size.y) {
            printf("if 4\n");
            perso.py+=10;
            collision = 1;
            return collision;
        }
        printf("\n");
    }
    return collision;
}