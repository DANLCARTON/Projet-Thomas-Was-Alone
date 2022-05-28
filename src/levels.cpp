#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "../include/geometry.hpp"
#include "../include/shape.hpp"
#include "../include/colors.hpp"
#include "../include/levels.hpp"
#include "../include/personnages.hpp"

void draw(const int level, const int nbPersos, const int nbBlocs, const Perso listedespersos[],
        const Platform listedesblocs[], const Goal listedesgoals[])
{
    for (int i = 0; i < nbBlocs; i++) {
            drawPlatform(listedesblocs[i]);
        }

        for (int i = 0; i < nbPersos; i++) {
            drawPerso(listedespersos[i]);
        }

        for(int i=0; i < nbPersos; i++)
        {
            drawGoal(listedesgoals[i]);
        }

        if (level == 0) {
            glColor3f(.5, .5, .5);
            drawString(-140, 200, 0, "Thomas Was Alone");
            drawString(-300,100,0, "Choisis ton niveau en cliquant sur les numeros de ton clavier");
            drawString(-300, 0, 0, "Level 01");
            drawString(-100, 0, 0, "Level 02");
        }

        if (level == -1) {
            glColor3f(.5, .5, .5);
            drawString(-350, 0, 0, "Bravo tu as passe le niveau, clique n'importe ou pour en choisir un autre au clavier.");
        }

        if (level == -2){
        glColor3f(.5, .5, .5);
        drawString(-140, 100, 0, "Felicitations !!");
        drawString(-500, 0, 0, "Tu a vaincu notre niveau le plus difficile. Tu peux quitter le jeu ou choisir un autre niveau avec ton clavier.");
        }
}


void drawLevel(const int level, int* nbPersos, int* nbBlocs, Perso listedespersos[], 
Platform listedesblocs[], Goal listedesgoals[],const int currentPerso, bool* firstloop)
{
    if (level<=0)
    {
        listedesblocs[0] = createFond(createColor(.1, .1, .1));
        *nbBlocs=1;
        *nbPersos=0;
    }

    else if (level==1)
    {
            glTranslated(-listedespersos[currentPerso].px, -listedespersos[currentPerso].py, 0);
            int b = 0;
            if (*firstloop == true) {
                int p = 0;
                listedespersos[p] = createPerso(-140, -250, 0, 0, 50, 50, createColor(1, 0, 0)); 
                drawPerso(listedespersos[p]); 
                p++;   
                listedespersos[p] = createPerso(100, 0, 0, 0, 50, 100, createColor(0, 255, 0)); 
                drawPerso(listedespersos[p]); 
                p++;
                *nbPersos = p;
            }
            listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, -300, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(580, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-50, -100, 0), createVector(100, 100, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-300, 220, 0), createVector(70, 130, 0)); b++;
            for (int i = 0; i < *nbPersos; i++) {
                if (listedespersos[currentPerso].color.r == listedesblocs[b].color.r && listedespersos[currentPerso].color.g == listedesblocs[b].color.g && listedespersos[currentPerso].color.b == listedesblocs[b].color.b) {
                    listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
                }
                if (listedespersos[currentPerso].color.r != listedespersos[i].color.r || listedespersos[currentPerso].color.g != listedespersos[i].color.g || listedespersos[currentPerso].color.b != listedespersos[i].color.b) {
                    listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
                }
            }
            if (*firstloop == true) {
                *nbBlocs = b;
                *firstloop = false;
            }
            int g = 0;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(-290, 270, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(140, -250, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            
    }

    else if(level==2){
    }

    draw(level, *nbPersos, *nbBlocs, listedespersos, listedesblocs, listedesgoals);
}