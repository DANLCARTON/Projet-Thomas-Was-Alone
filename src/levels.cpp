#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "../include/geometry.hpp"
#include "../include/shape.hpp"
#include "../include/colors.hpp"
#include "../include/levels.hpp"
#include "../include/personnages.hpp"

//durée d'un demiCycle de plateforme mobile en seconde
int demiCycleTime=2; //doit être un multiple de 4 si les images par seconde ne le sont pas
                    //ce qui n'arrive pas avec 30 fps, 60, 120, 240,...

float maxSpeedPlateform=0.2;

//Dessin du niveau

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
            drawString(100, 0, 0, "Level 03");
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

//Crée le niveau et appelle la fonction draw
void drawLevel(const int level, int* nbPersos, int* nbBlocs, Perso listedespersos[], 
Platform listedesblocs[], Goal listedesgoals[],int* currentPerso, bool* firstloop, 
int framesPerSecond, int* cycle, int* dirCycle, Uint32 elapsedTime)
{
    if (level<=0)
    {
        listedesblocs[0] = createFond(createColor(.1, .1, .1));
        *nbBlocs=1;
        *nbPersos=0;
    }

    else if(level==1){

        int b; 

        if (*firstloop) {

            //PERSONNAGES
            *currentPerso=0;
            int p = 0;
            listedespersos[p] = createPerso(-140, -250, 0, 0, 50, 50, createColor(1, 0, 0)); 
            p++;   
            listedespersos[p] = createPerso(100, 0, 0, 0, 50, 100, createColor(0, 255, 0)); 
            p++;
            *nbPersos = p;

            b = 0;

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


            //OBJECTIFS
            int g = 0;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(-290, 270, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(140, -250, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        }

        //CAMERA
        glTranslated(-(listedespersos[*currentPerso].px+(listedespersos[*currentPerso].width/2)), -(listedespersos[*currentPerso].py-(listedespersos[*currentPerso].height/2)), 0);

        if(!*firstloop)
        {
            b=*nbBlocs-1;
        }

        //Transforme le personnage non joué en plateforme
        for (int i = 0; i < *nbPersos; i++) {
            if (listedespersos[*currentPerso].color.r == listedesblocs[b].color.r && listedespersos[*currentPerso].color.g == listedesblocs[b].color.g && listedespersos[*currentPerso].color.b == listedesblocs[b].color.b) {
                listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
            }
            if (listedespersos[*currentPerso].color.r != listedespersos[i].color.r || listedespersos[*currentPerso].color.g != listedespersos[i].color.g || listedespersos[*currentPerso].color.b != listedespersos[i].color.b) {
                listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
            }
        }
        if (*firstloop) {
            *nbBlocs = b;
            *firstloop = false;
        }
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

    else if(level==3)
    {

        int b;
        
        if (*firstloop) {

            //PERSONNAGES
            *currentPerso=0;
            int p = 0;
            listedespersos[p] = createPerso(-340, -250, 0, 0, 50, 50, createColor(0, 250, 250)); 
            p++;   
            listedespersos[p] = createPerso(100, -250, 0, 0, 50, 200, createColor(250, 0, 0)); 
            p++;
            *nbPersos = p;

            b = 0;
            
            //FOND
            listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;

            //BORDS
            //Bord bas
            listedesblocs[b] = createPlatform(createPoint(-640, -300, 0), createVector(1280, 60, 0)); b++;
            //Bord gauche
            listedesblocs[b] = createPlatform(createPoint(-640, 1080, 0), createVector(60, 1440, 0)); b++;
            //Bord droit
            listedesblocs[b] = createPlatform(createPoint(580, 1080, 0), createVector(60, 1440, 0)); b++;
            //Bord haut
            listedesblocs[b] = createPlatform(createPoint(-640, 1080, 0), createVector(1280, 60, 0)); b++;
     
            //PLATEFORMES MOUVANTES
            //Plateforme bas droite
            listedesblocs[b] = createPlatform(createPoint(-50, -100, 0), createVector(200, 10, 0)); b++;
            //Plateforme milieu gauche
            listedesblocs[b] = createPlatform(createPoint(-300, 100, 0), createVector(70,10, 0)); b++;
            //Plateforme haut droit
            listedesblocs[b] = createPlatform(createPoint(0, 200, 0), createVector(70,10, 0)); b++;

            //PLATEFORME FIXE
            listedesblocs[b] = createPlatform(createPoint(-300, 220, 0), createVector(70,10, 0)); b++;
            //Finale
            listedesblocs[b] = createPlatform(createPoint(200, 500, 0), createVector(400,50, 0)); b++;

            //OBJECTIFS
            int g = 0;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(-290, 270, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(300, 550, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
        
        }
        
        //CAMERA
        glTranslated(-(listedespersos[*currentPerso].px+(listedespersos[*currentPerso].width/2)), -(listedespersos[*currentPerso].py-(listedespersos[*currentPerso].height/2)), 0);


        ///////////////////////////////////////////////
        //PLATEFORMES MOBILES

        float offset=0;

        if (*cycle < demiCycleTime*framesPerSecond/2)
        {
            offset+=*cycle * maxSpeedPlateform/(demiCycleTime*framesPerSecond/2);
            *cycle +=1;
        }

        else if (*cycle == demiCycleTime*framesPerSecond/2){
            offset=maxSpeedPlateform;
            *dirCycle= -*dirCycle;
            *cycle+=1;
        }

        else if(*cycle > demiCycleTime*framesPerSecond/2
        && *cycle < demiCycleTime*framesPerSecond)
        {
            offset-=(demiCycleTime*framesPerSecond - *cycle) * maxSpeedPlateform/(demiCycleTime*framesPerSecond/2);
            *cycle +=1;
        }
        else if (*cycle == demiCycleTime*framesPerSecond)
        {
        *cycle=0;
        }

        if(*dirCycle==-1)
        {
            offset=-offset;
        }

        listedesblocs[5].position.x+=offset*elapsedTime;

        listedesblocs[6].position.x+=-offset*elapsedTime;

        listedesblocs[7].position.x+=-offset*elapsedTime;

        ///////////////////////////////////////////////


        //Transforme le personnage non joué en plateforme
        if(!*firstloop)
        {
            b=*nbBlocs-1;
        }
        for (int i = 0; i < *nbPersos; i++) {
            if (listedespersos[*currentPerso].color.r == listedesblocs[b].color.r && listedespersos[*currentPerso].color.g == listedesblocs[b].color.g && listedespersos[*currentPerso].color.b == listedesblocs[b].color.b) {
                listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
            }
            if (listedespersos[*currentPerso].color.r != listedespersos[i].color.r || listedespersos[*currentPerso].color.g != listedespersos[i].color.g || listedespersos[*currentPerso].color.b != listedespersos[i].color.b) {
                listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
            }
        }

        if (*firstloop) {
            *nbBlocs = b;
            *firstloop = false;
        }
    }


    draw(level, *nbPersos, *nbBlocs, *currentPerso, listedespersos, listedesblocs, listedesgoals);
}