#include <GLUT/glut.h>
#include "welcome.h"

// Calculates the width of a bitmap text string so it can be centered on screen.
int getTextWidth(const char* text, void* font)
{
    int width = 0;

    while (*text != '\0')
    {
        width += glutBitmapWidth(font, *text);
        text++;
    }

    return width;
}

// Draws a line of text centered horizontally at the given y position.
void drawCenteredText(float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_18)
{
    int textWidth = getTextWidth(text, font);
    float x = (800.0f - textWidth) / 2.0f;

    glRasterPos2f(x, y);

    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

// Draws the initial welcome screen with title, student information and start instructions.
void displayWelcome()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.95f, 0.88f, 0.55f);
    drawCenteredText(560, "OpenGL 3D Scene Project", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(0.72f, 0.86f, 1.0f);
    drawCenteredText(500, "Lampros Patas", GLUT_BITMAP_HELVETICA_18);
    drawCenteredText(470, "A.M. 2890", GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.88f, 0.95f, 1.0f);
    drawCenteredText(400, "Press S to start", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.72f, 0.72f);
    drawCenteredText(370, "Press ESC to exit", GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}