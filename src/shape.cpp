#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/shape.hpp"
#include "../include/colors.hpp"

void drawPlatform (Platform plat) {
    glColor3f(plat.color.r, plat.color.g, plat.color.b);
    glPushMatrix(); 
        glTranslatef(plat.position.x, plat.position.y, plat.position.z);
        glScalef(plat.size.x, plat.size.y, 1);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}

void drawGoal (Goal goal) {
    glColor3f(1, 1, 1);
    glPushMatrix(); 
        glTranslatef(goal.position.x, goal.position.y, goal.position.z);
        glScalef(goal.size.x, goal.size.y, 1);
        glBegin(GL_LINE_STRIP);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}

void drawCurrentPersoCursor(Perso perso)
{
    glColor3f(1,1,1);
    glPushMatrix(); 
        glTranslatef(perso.px+perso.width/2, perso.py+10, 0);
        glScalef(3, 3, 1);
        glBegin(GL_LINE_STRIP);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}

Platform createPlatform (Point3D pos, Vector3D size) {
    Platform rect;
    rect.position = pos;
    rect.size = size;
    rect.color = createColor(0.2, 0.2, 0.2);
    rect.solid = 1;
    rect.moving = 0;
    rect.dirMove = 0;
    rect.distanceMove = 0;
    return rect;
}

Goal createGoal (Perso perso, Point3D pos, Vector3D size) {
    Goal goal;
    goal.perso = perso;
    goal.position = pos,
    goal.size = size;
    return goal;
}

Platform createFond (ColorRGB color) {
    Platform rect;
    rect.position = createPoint(-10000, 10000, 0);
    rect.size = createVector(20000, 20000, 0);
    rect.color = color;
    rect.solid = 0;
    rect.moving = 0;
    rect.dirMove = 0;
    rect.distanceMove = 0;
    return rect;
}

Platform solidifyCharacter(Perso perso) {
    Platform rect;
    rect.position = createPoint(perso.px, perso.py, 0);
    rect.size = createVector(perso.width, perso.height, 0);
    rect.color = perso.color;
    rect.solid = 1;
    rect.moving = 0;
    rect.dirMove = 0;
    rect.distanceMove = 0;
    return rect;
}

Platform maskPlatformCreatedFormCharacter(Platform plat) {
    plat.color = createColor(0.2, 0.2, 0.2);
    plat.solid = 0;
    return plat;
}