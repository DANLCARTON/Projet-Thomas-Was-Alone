#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/personnages.hpp"
#include "../include/colors.hpp"

void drawPerso(Perso perso) {
    glColor3f(perso.color.r, perso.color.g, perso.color.b);
    glPushMatrix(); 
        glTranslatef(perso.px, perso.py, 0);
        glScalef(perso.width, perso.height, 1);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}

Perso createPerso (float px, float py, float vx, float vy, float height, float width, ColorRGB color) {
    Perso perso;
    perso.px = px;
    perso.py = py;
    perso.vx = vx;
    perso.vy = vy;
    perso.height = height;
    perso.width = width;
    perso.color = color;
    drawPerso(perso);
    return perso;
}


//VARIABLES

//nombre frames pour l'accélération horizontale linéaire
int n=60; //ici 1/4s
//vitesse horizontale maximale
int hVmax=1* 2*n; //DOIT ETRE DIVISIBLE PAR 2*n
//Accélération horizontale par frame
int hAcc=hVmax/n;

//constante de gravitation
float g=0.01f*n;

//accélération verticale saut
float jumpAcc=300*g;

void Perso::fall(const Uint32 dt) //dt est le temps entre chaque image
{ 
    this->vy-=g*dt;
}

void Perso::jump()
{
    this->vy+=jumpAcc;
}

void Perso::goRight()
{
    if (this->vx<hVmax)
    {
        this->vx+=hAcc; //permet une accélération linéaire sur n frames
    }
}

void Perso::goLeft()
{
    if (this->vx>-hVmax)
    {
        this->vx-=hAcc;
    }
}

//Décélère à la même vitesse qu'il accélère
void Perso::horizontalDeceleration()
{
    if (this->vx>0)
    {
        this->vx-=hAcc;
    }
    else if(this->vx<0)
    {
        this->vx+=hAcc;
    }
}

//déplace le personnage en fonction de ses vitesses verticale et horizontale
void Perso::move(const Uint32 dt)
{
    this->px+=this->vx*dt/(2*n);
    this->py+=this->vy*dt/(2*n);
}