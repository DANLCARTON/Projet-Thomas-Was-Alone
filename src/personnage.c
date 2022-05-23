#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/personnages.h"
#include "../include/colors.h"

void drawPerso(Perso perso) {
    glColor3f(perso.color.r, perso.color.g, perso.color.b);
    glPushMatrix(); // je pense qu'il faudra virer ça après ou peut-être pas en fait
        glTranslatef(perso.px, perso.py, 0);
        glScalef(perso.height, perso.width, 1);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}

Perso createPerso (float px, float py, float vx, float vy, float height, float width, int isPlaying, ColorRGB color, int index) {
    Perso perso;
    perso.px = px;
    perso.py = py;
    perso.vx = vx;
    perso.vy = vy;
    perso.height = height;
    perso.width = width;
    perso.isPlaying = isPlaying;
    perso.color = color;
    perso.index = index;
    drawPerso(perso);
    return perso;
}

//VARIABLES

//constante de gravitation
const float g = 9.81;

//accélération verticale saut
float jumpAcc = 3.0*g;

//vitesse horizontale maximale
const float hVmax=100.0;
//nombre frames pour l'accélération horizontale linéaire
const float n=30.0;
//Accélération horizontale par frame
const float hAcc = hVmax/n;

//Décélération en cas de contact avec une plateforme
float solidDec=hAcc*10;

void fall(Perso perso, const float dt) //dt est le temps entre chaque image
{ 
    perso.vy-=g*dt;
}

void jump(Perso perso, const float dt)
{
    perso.vy+=jumpAcc*dt;
}

void goRight(Perso perso)
{
    if (perso.vx<hVmax)
    {   
        perso.vx+=hAcc; //permet une accélération linéaire sur n frames
    }
    return perso;
}

void goLeft(Perso perso)
{
    if (perso.vx>-hVmax)
    {
        perso.vx-=hAcc;
    }
}

//dans le vide, décélère à la même vitesse qu'il accélère pour faire une belle cloche
void horizontalDeceleration(Perso perso)
{
    if (perso.vx>0)
    {
        perso.vx-=hAcc;
    }
    else if(perso.vx<0)
    {
        perso.vx+=hAcc;
    }
}

//en cas de contact avec une plateforme
void solidFiction(Perso perso) 
{
    if (perso.vx>0)
    {   
        if(perso.vx-solidDec>=0) //évite une accélération dans l'autre sens
        {
            perso.vx-=solidDec;
        }
        else
        {
            perso.vx=0;
        }
    }
    else if(perso.vx<0)
    {
        if(perso.vx-solidDec<=0) //évite une accélération dans l'autre sens
        {
            perso.vx+=solidDec;
        }
        else
        {
            perso.vx=0;
        }
    }
}

void move(Perso perso, const float dt)
{
    perso.px+=perso.vx*dt;
    perso.py+=perso.vy*dt;
}