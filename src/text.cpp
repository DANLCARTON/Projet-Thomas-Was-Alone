#include <string.h>
#include <GL/glut.h>
#include "../include/geometry.hpp"
#include "../include/text.hpp"

void drawString(float x, float y, float z, char *string) {
    glRasterPos3f(x, y, z);
    for (char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}