#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <string.h>


#include "../include/colors.hpp"
#include "../include/geometry.hpp"
#include "../include/personnages.hpp"
#include "../include/shape.hpp"
#include "../include/levels.hpp"
#include "../include/collisions.hpp"
#include "../include/text.hpp"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const char WINDOW_TITLE[] = "Thomas was alone";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 720;

/*Frames par seconde*/
int framesPerSecond=240;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / framesPerSecond;

/*Frames minimales entre chaque saut*/    
int framesBetweenJumps=framesPerSecond/4;


void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - D E B U T   D U   M A I N - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char** argv) 
{
    // Initialisation de la bibliothèque glut

    glutInit(&argc, argv);
    
    //* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }   
  
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    int nbBlocs;

    int currentPerso = 0;
    int nbPersos;

    Platform listedesblocs[100]; 
    Goal listedesgoals[100];
    Perso listedespersos[100];

    bool firstloop = true;


    Uint32 elapsedTime=0;

    int framesToNextJump=0;

    bool keys[]={false,false}; //enregistre les touches pressés à un instant donné

    bool changementDePerso=false;

    int level = 0;
    int nbLevel=1;

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /*VICTOIRE*/

        if(victory(nbPersos,listedespersos,listedesgoals) && level>0)
        {
            if(level==nbLevel){
                level=-2; //Victoire jeu
            }

            else{
                level=-1; //Ecran niveau suivant
            }
        }

        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - Placer ici le code de dessin - - - - - */
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        if (level == 0 || level == -1 || level == -2) {
            int b = 0;
            listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;
            nbBlocs = b;
            nbPersos=0;
        } 

        else if (level == 1) {
            glTranslated(-listedespersos[currentPerso].px, -listedespersos[currentPerso].py, 0);
            int b = 0;
            if (firstloop == true) {
                int p = 0;
                listedespersos[p] = createPerso(-140, -250, 0, 0, 50, 50, createColor(1, 0, 0)); 
                drawPerso(listedespersos[p]); 
                p++;   
                listedespersos[p] = createPerso(0, 0, 0, 0, 50, 100, createColor(0, 255, 0)); 
                drawPerso(listedespersos[p]); 
                p++;
                nbPersos = p;
            }
            listedesblocs[b] = createFond(createColor(.1, .1, .1)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, -300, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(580, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-50, -100, 0), createVector(100, 100, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-300, 240, 0), createVector(70, 130, 0)); b++;
            for (int i = 0; i < nbPersos; i++) {
                if (listedespersos[currentPerso].color.r == listedesblocs[b].color.r && listedespersos[currentPerso].color.g == listedesblocs[b].color.g && listedespersos[currentPerso].color.b == listedesblocs[b].color.b) {
                    listedesblocs[b] = maskPlatformCreatedFormCharacter(listedesblocs[b]);
                }
                if (listedespersos[currentPerso].color.r != listedespersos[i].color.r || listedespersos[currentPerso].color.g != listedespersos[i].color.g || listedespersos[currentPerso].color.b != listedespersos[i].color.b) {
                    listedesblocs[b] = solidifyCharacter(listedespersos[i]); b++;
                }
            }
            if (firstloop == true) {
                nbBlocs = b;
                firstloop = false;
            }
            int g = 0;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(140, -250, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            listedesgoals[g] = createGoal(listedespersos[g], createPoint(0, -250, 0), createVector(listedespersos[g].width, listedespersos[g].height, 0)); g++;
            
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /*DESSIN*/


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


        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/


        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        

        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/


        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT) 
			{
				loop = 0;
				break;
			}
		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0; 
				break;
			}

            switch(e.type) //pour les touches droite et gauche qui restent appuyées
            {
                /* Touche clavier */
                case SDL_KEYUP:
                    switch(e.key.keysym.sym)
                    {
                        case 100:
                            keys[1]=false;
                            break;

                        case 113:
                            keys[0]=false;
                            break;  
                            
                        default:
                            break;
                    }
            }

            switch(e.type) 
            {
                case SDL_WINDOWEVENT:
                    switch (e.window.event) 
                    {
                        /* Redimensionnement fenetre */
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);                
                            break;

                        default:
                            break; 
                    }
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (x %d, y %d)\n", e.button.x, e.button.y);
                    if (level == 0) {
                        printf("if 1");
                        if (e.button.x > 800 && e.button.x < 950 && e.button.y > 330 && e.button.y < 370) {
                            printf("if 2");
                            level = 1;
                        }
                    }
                    break;

                case SDL_KEYDOWN: // Q D pour se déplacer, Tab pour changer de perso, Espace pour sauter
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    switch(e.key.keysym.sym)
                    {
                        case 100: //d
                            keys[1]=true;
                            break;
                         case 113: //q
                            keys[0]=true;
                            break;
                        case 32: //Espace : Saut
                            if(framesToNextJump==0){
                                listedespersos[currentPerso].jump();
                                framesToNextJump+=1;
                                }
                            break;
                        case 9: //Tab : CHangement de perso
                            changementDePerso=true;
                         
                            if (currentPerso < nbPersos-1) {
                                currentPerso++;
                            }
                            else{
                                currentPerso=0;
                            }
                            break;
                        
                        case 8: //Return
                            level=0;
                            break;
                        case 49: // 1
                            if (level <= 0)
                                level = 1;
                                firstloop = true;
                            break;
                        case 1073741913: // pav. num. 1 
                            if (level <= 0)
                                level = 1;
                                firstloop = true;
                            break;
                        case 50: //2
                            if (level <= 0)
                                level=2;
                                firstloop = true;
                            break;
                        case 1073741914: // pav. num. 2
                            if (level <= 0)
                                level=2;
                                firstloop = true;
                            break;

                        default:
                        break;
                    }

                    break;
                    
                default:
                    break;
            }
        }


        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/


        /*DEPLACEMENTS ET COLLISIONS*/

        if (!changementDePerso) //ne modifiera pas les vitesses horizontales 
                                //si on change de perso pour commencer avec un perso
                                //immobile ou en chute sans conserver la vitesse du perso précédent
        {
            if(keys[0])
            {
                listedespersos[currentPerso].goLeft();   
            }

            if(keys[1])
            {
                listedespersos[currentPerso].goRight();
            }

            if (!keys[0] && !keys[1])
            {
                listedespersos[currentPerso].horizontalDeceleration();
            }
        }

        else{
            changementDePerso=false;
        }

        //Temps d'attente entre chaque saut
        if (framesToNextJump!=0 && framesToNextJump!=framesBetweenJumps)
        {
            framesToNextJump+=1;
        }
        if (framesToNextJump==framesBetweenJumps)
        {
            framesToNextJump=0;
        }


        //Gestion des collisions et déplacements
        collision(nbPersos, listedespersos, nbBlocs, listedesblocs, elapsedTime);
        listedespersos[currentPerso].move(elapsedTime);

        if(!checkGround(listedespersos[currentPerso],nbBlocs,listedesblocs))
        {
            listedespersos[currentPerso].fall(elapsedTime);
        }

        
        /* Calcul du temps ecoule */
        
        elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
        elapsedTime = SDL_GetTicks() - startTime;

    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
