#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#include "../include/colors.hpp"
#include "../include/geometry.hpp"
#include "../include/personnages.hpp"
#include "../include/shape.hpp"
#include "../include/levels.hpp"
#include "../include/collisions.hpp"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const char WINDOW_TITLE[] = "Thomas was alone";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 720;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 240;


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



int main(int argc, char** argv) 
{
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

    int camx = 0;
    int camy = 0;

    int nbBlocs;

    int currentPerso = 0;
    int maxPersos;
    int loopcreateperso = 0;


    Uint32 elapsedTime=0;
    
    int framesBetweenJumps=30;

    int framesToNextJump=0;

    bool keys[]={false,false}; //enregistre les touches pressés à un instant donné

    bool changementDePerso=false;

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
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

        // glTranslatef(camx, camy, 0);

        int level = 1;

        Platform listedesblocs[100]; // on verra combien quand ce sera fait
        Goal listedesgoals[100]; // meme chose
        Perso listedespersos[100]; //ehoui


        if (level == 1) {
            int b = 0;
            int g = 0;
            if (loopcreateperso == 0) {
                int p = 0;
                listedespersos[p] = createPerso(-140, -250, 0, 0, 50, 50, createColor(1, 0, 0)); 
                drawPerso(listedespersos[p]); 
                p++;   
                listedespersos[p] = createPerso(0, 0, 0, 0, 50, 100, createColor(0, 255, 0)); 
                drawPerso(listedespersos[p]); 
                p++;
                maxPersos = p;
                loopcreateperso = 1;
            }
            drawPerso(listedespersos[0]);
            drawPerso(listedespersos[1]);
            listedesblocs[b] = createPlatform(createPoint(-640, -300, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(580, 360, 0), createVector(60, 720, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-640, 360, 0), createVector(1280, 60, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-50, -100, 0), createVector(100, 100, 0)); b++;
            listedesblocs[b] = createPlatform(createPoint(-300, 240, 0), createVector(70, 130, 0)); b++;
            nbBlocs = b;
            listedesgoals[g] = createGoal(listedespersos[0], createPoint(140, -250, 0), createVector(listedespersos[0].width, listedespersos[0].height, 0)); g++;
        }

        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/
        /* - - - - - - - - - - - - - - - - - - - - - - - - -*/

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
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

            switch(e.type)
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
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
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
                            if (currentPerso < maxPersos-1) {
                                currentPerso++;
                            }
                            else{
                                currentPerso=0;
                            }
                            break;
                        default:
                        break;
                    }

                    break;
                    
                default:
                    break;
            }
        }


        /*DEPLACEMENTS*/
        if (!changementDePerso) //ne modifiera pas les vitesses horizontales 
                                //si on change de perso
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
        collision(maxPersos, listedespersos, nbBlocs, listedesblocs, elapsedTime);
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
