#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/shape.h"
#include "../include/colors.h"

void drawPlatform (Platform plat) {
    glColor3f(plat.color.r, plat.color.g, plat.color.b);
    glPushMatrix(); // je pense qu'il faudra virer ça après
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

Platform createPlatform (Point3D pos, Vector3D size) {
    Platform rect;
    rect.position = pos;
    rect.size = size;
    rect.color = createColor(0.2, 0.2, 0.2);
    rect.solid = 1;
    rect.moving = 0;
    rect.dirMove = 0;
    rect.distanceMove = 0;
    drawPlatform(rect);
    return rect;
}