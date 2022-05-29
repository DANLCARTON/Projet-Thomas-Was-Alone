#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "../include/geometry.hpp"
#include "../include/shape.hpp"
#include "../include/colors.hpp"
#include "../include/levels.hpp"
#include "../include/personnages.hpp"

void draw(const int level, const int nbPersos, const int nbBlocs, const int currentPerso, const Perso listedespersos[],
        const Platform listedesblocs[], const Goal listedesgoals[])
{
    for (int i = 0; i < nbBlocs; i++) {
            drawPlatform(listedesblocs[i]);
        }

        for (int i = 0; i < nbPersos; i++) {
            drawPerso(listedespersos[i]);
        }

        if(level>0){
        drawCurrentPersoCursor(listedespersos[currentPerso]);
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
            drawString(-350, 0, 0, "Bravo tu as passe le niveau, tu peux en choisir un autre au clavier.");
        }

        if (level == -2){
        glColor3f(.5, .5, .5);
        drawString(-140, 100, 0, "Felicitations !!");
        drawString(-500, 0, 0, "Tu a vaincu notre niveau le plus difficile. Tu peux quitter le jeu ou choisir un autre niveau avec ton clavier.");
        }
}


void drawLevel(const int level, int* nbPersos, int* nbBlocs, Perso listedespersos[], 
Platform listedesblocs[], Goal listedesgoals[],int* currentPerso, bool* firstloop, const Uint32 elapsedTime)
{
    if (level<=0)
    {
        listedesblocs[0] = createFond(createColor(.1, .1, .1));
        *nbBlocs=1;
        *nbPersos=0;
    }

    else if(level==1){

        //PERSONNAGES
        if (*firstloop == true) {
            *currentPerso=0;
            int p = 0;
            listedespersos[p] = createPerso(-140, -250, 0, 0, 50, 50, createColor(1, 0, 0)); 
            drawPerso(listedespersos[p]); 
            p++;   
            listedespersos[p] = createPerso(100, 0, 0, 0, 50, 100, createColor(0, 255, 0)); 
            drawPerso(listedespersos[p]); 
            p++;
            *nbPersos = p;
        }

        //CAMERA
        glTranslated(-(listedespersos[*currentPerso].px+(listedespersos[*currentPerso].width/2)), -(listedespersos[*currentPerso].py-(listedespersos[*currentPerso].height/2)), 0);

        int b = 0;

        //FOND
        listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;

        //BORDS
        //Bord bas
        listedesblocs[b] = createPlatform(createPoint(-640, -300, 0), createVector(1280, 60, 0)); b++;
        //Bord gauche
        listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(60, 720, 0)); b++;
        //Bord droit
        listedesblocs[b] = createPlatform(createPoint(580, 360, 0), createVector(60, 720, 0)); b++;
        //Bord haut
        listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(1280, 60, 0)); b++;
        
        //PLATEFORMES
        //Plateforme bas droite
        listedesblocs[b] = createPlatform(createPoint(-50, -100, 0), createVector(100, 100, 0)); b++;
        //Plateforme haut gauche
        listedesblocs[b] = createPlatform(createPoint(-300, 220, 0), createVector(70, 130, 0)); b++;
       
        //Transforme le personnage non joué en plateforme
        for (int i = 0; i < *nbPersos; i++) {
            if (listedespersos[*currentPerso].color.r == listedesblocs[b].color.r && listedespersos[*currentPerso].color.g == listedesblocs[b].color.g && listedespersos[*currentPerso].color.b == listedesblocs[b].color.b) {
                listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
            }
            if (listedespersos[*currentPerso].color.r != listedespersos[i].color.r || listedespersos[*currentPerso].color.g != listedespersos[i].color.g || listedespersos[*currentPerso].color.b != listedespersos[i].color.b) {
                listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
            }
        }
        if (*firstloop == true) {
            *nbBlocs = b;
            *firstloop = false;
        }

        //OBJECTIFS
        int g = 0;
        listedesgoals[g] = createGoal(listedespersos[g], createPoint(-290, 270, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        listedesgoals[g] = createGoal(listedespersos[g], createPoint(140, -250, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        
    }

    else if(level==2){

        //PERSONNAGES
        if (*firstloop == true) {
            *currentPerso=0;
            int p = 0;
            listedespersos[p] = createPerso(-900, -420, 0, 0, 60, 60, createColor(1, 0, 1)); 
            drawPerso(listedespersos[p]); 
            p++;   
            listedespersos[p] = createPerso(-760, -360, 0, 0, 120, 60, createColor(1, 1, 0)); 
            drawPerso(listedespersos[p]); 
            p++;
            listedespersos[p] = createPerso(-900, -175, 0, 0, 25, 400, createColor(0, 0, 1)); 
            drawPerso(listedespersos[p]); 
            p++;
            *nbPersos = p;
        }
        
        //CAMERA
        glTranslated(-(listedespersos[*currentPerso].px+(listedespersos[*currentPerso].width/2)), -(listedespersos[*currentPerso].py-(listedespersos[*currentPerso].height/2)), 0);

        int b = 0;

        //FOND
        listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;

        //BORDS
        //Bord bas
        listedesblocs[b] = createPlatform(createPoint(-960, -480, 0), createVector(1920, 60, 0)); b++;
        //Bord gauche
        listedesblocs[b] = createPlatform(createPoint(-960, 540, 0), createVector(60, 1080, 0)); b++;
        //Bord droit
        listedesblocs[b] = createPlatform(createPoint(900, 540, 0), createVector(60, 1080, 0)); b++;
        //Bord haut
        listedesblocs[b] = createPlatform(createPoint(-960, 540, 0), createVector(1920, 60, 0)); b++;
        
        //PLATEFORMES
        // plateformes au départ du perso bleu
        listedesblocs[b] = createPlatform(createPoint(-900, -200, 0), createVector(450, 50, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(-900, 120, 0), createVector(180, 295, 0)); b++;
        // escalier
        printf("%f\n", listedespersos[*currentPerso].py);
        listedesblocs[b] = createPlatform(createPoint(-350, -350, 0), createVector(100, 100, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(-250, -250, 0), createVector(100, 200, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(-150, -150, 0), createVector(100, 300, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(-50, -50, 0), createVector(100, 400, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(50, -250, 0), createVector(100, 200, 0)); b++;
        // plateforme où il y a l'arrivée du violet
        listedesblocs[b] = createPlatform(createPoint(-900, 170, 0), createVector(180, 50, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(-900, 480, 0), createVector(120, 240, 0)); b++;
        // plateformes où il y l'arrivée du jaune
        listedesblocs[b] = createPlatform(createPoint(720, 170, 0), createVector(110, 650, 0)); b++;
        listedesblocs[b] = createPlatform(createPoint(830, 0, 0), createVector(70, 480, 0)); b++;
       
        //Transforme le personnage non joué en plateforme
        for (int i = 0; i < *nbPersos; i++) {
            if (listedespersos[*currentPerso].color.r == listedesblocs[b].color.r && listedespersos[*currentPerso].color.g == listedesblocs[b].color.g && listedespersos[*currentPerso].color.b == listedesblocs[b].color.b) {
                listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
            }
            if (listedespersos[*currentPerso].color.r != listedespersos[i].color.r || listedespersos[*currentPerso].color.g != listedespersos[i].color.g || listedespersos[*currentPerso].color.b != listedespersos[i].color.b) {
                listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
            }
        }
        if (*firstloop == true) {
            *nbBlocs = b;
            *firstloop = false;
        }

        //OBJECTIFS
        int g = 0;
        listedesgoals[g] = createGoal(listedespersos[g], createPoint(-900, 230, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        listedesgoals[g] = createGoal(listedespersos[g], createPoint(840, 120, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        listedesgoals[g] = createGoal(listedespersos[g], createPoint(-900, -455, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        
    }

    draw(level, *nbPersos, *nbBlocs, *currentPerso, listedespersos, listedesblocs, listedesgoals);
}