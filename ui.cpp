#include <GLUT/glut.h>
#include "ui.h"
#include "app_state.h"


// Draws a text string at a specific 2D screen position using a GLUT bitmap font.
void drawUIText(float x, float y, const char *text, void *font = GLUT_BITMAP_HELVETICA_12)
{
    glRasterPos2f(x, y);

    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

// Draws a semi-transparent rectangular panel behind interface text.
void drawPanel(float x1, float y1, float x2, float y2, float r, float g, float b, float alpha)
{
    glColor4f(r, g, b, alpha);

    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}


// Draws the on-screen UI with controls, color shortcuts, current status and student information.
void drawInstructions()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float leftPanelX1 = 10.0f;
    float leftPanelX2 = 285.0f;
    float leftPanelY2 = (float)windowHeight - 10.0f;
    float leftPanelY1 = leftPanelY2 - 215.0f;

    float rightPanelX1 = (float)windowWidth - 225.0f;
    float rightPanelX2 = (float)windowWidth - 10.0f;
    float rightPanelY2 = (float)windowHeight - 10.0f;
    float rightPanelY1 = rightPanelY2 - 155.0f;

    float statusPanelX1 = 10.0f;
    float statusPanelX2 = 300.0f;
    float statusPanelY1 = 10.0f;
    float statusPanelY2 = 110.0f;

    drawPanel(leftPanelX1, leftPanelY1, leftPanelX2, leftPanelY2, 0.05f, 0.07f, 0.10f, 0.72f);
    drawPanel(rightPanelX1, rightPanelY1, rightPanelX2, rightPanelY2, 0.05f, 0.07f, 0.10f, 0.72f);
    drawPanel(statusPanelX1, statusPanelY1, statusPanelX2, statusPanelY2, 0.05f, 0.07f, 0.10f, 0.72f);

    float padX = 14.0f;
    float line = 22.0f;

    float leftTextX = leftPanelX1 + padX;
    float leftTitleY = leftPanelY2 - 24.0f;
    float leftStartY = leftTitleY - 28.0f;

    float rightTextX = rightPanelX1 + padX;
    float rightTitleY = rightPanelY2 - 24.0f;
    float rightStartY = rightTitleY - 28.0f;

    float statusTextX = statusPanelX1 + padX;
    float statusTopY = statusPanelY2 - 24.0f;

    glColor3f(0.85f, 0.92f, 1.0f);
    drawUIText(leftTextX, leftTitleY, "Controls", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawUIText(leftTextX, leftStartY - 0 * line, "1/2/3  Select object");
    drawUIText(leftTextX, leftStartY - 1 * line, "Arrows  Rotate");
    drawUIText(leftTextX, leftStartY - 2 * line, "+ / -   Scale");
    drawUIText(leftTextX, leftStartY - 3 * line, "Space   Auto Rotate");
    drawUIText(leftTextX, leftStartY - 4 * line, "Shift+Drag  Zoom");
    drawUIText(leftTextX, leftStartY - 5 * line, "P  Projection");
    drawUIText(leftTextX, leftStartY - 6 * line, "Esc  Exit");

    glColor3f(0.85f, 0.92f, 1.0f);
    drawUIText(rightTextX, rightTitleY, "Colors", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawUIText(rightTextX, rightStartY - 0 * line, "C  Cyan");
    drawUIText(rightTextX, rightStartY - 1 * line, "R  Red");
    drawUIText(rightTextX, rightStartY - 2 * line, "G  Green");
    drawUIText(rightTextX, rightStartY - 3 * line, "O  Orange");
    drawUIText(rightTextX, rightStartY - 4 * line, "M  Multicolor");

    glColor3f(1.0f, 1.0f, 1.0f);

    if (activeObject == 1)
        drawUIText(statusTextX, statusTopY - 0 * line, "Active: Cube");
    else if (activeObject == 2)
        drawUIText(statusTextX, statusTopY - 0 * line, "Active: Sphere");
    else
        drawUIText(statusTextX, statusTopY - 0 * line, "Active: 2D Shape");

    if (autoRotate)
        drawUIText(statusTextX, statusTopY - 1 * line, "Rotation: ON");
    else
        drawUIText(statusTextX, statusTopY - 1 * line, "Rotation: OFF");

    if (usePerspective)
        drawUIText(statusTextX, statusTopY - 2 * line, "Projection: Perspective");
    else
        drawUIText(statusTextX, statusTopY - 2 * line, "Projection: Orthographic");

    drawUIText(statusTextX, statusTopY - 3 * line, "Lampros Patas | A.M. 2890");

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}