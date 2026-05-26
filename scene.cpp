#include <GLUT/glut.h>
#include <cmath>
#include "scene.h"
#include "app_state.h"

// Chooses the correct RGB color for an object based on the selected color mode.
void applyColor(int colorMode, float defaultR, float defaultG, float defaultB)
{
    if (colorMode == 1)
        glColor3f(0.0f, 1.0f, 1.0f);
    else if (colorMode == 2)
        glColor3f(1.0f, 0.0f, 0.0f);
    else if (colorMode == 3)
        glColor3f(0.0f, 1.0f, 0.0f);
    else if (colorMode == 4)
        glColor3f(1.0f, 0.5f, 0.0f);
    else
        glColor3f(defaultR, defaultG, defaultB);
}

// Generates a time-varying multicolor effect for iridescent coloring.
void applyIridescentColor()
{
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.002f;

    float r = 0.5f + 0.5f * sin(t);
    float g = 0.5f + 0.5f * sin(t + 2.0f);
    float b = 0.5f + 0.5f * sin(t + 4.0f);

    glColor3f(r, g, b);
}

// Draws the X, Y and Z axes of the 3D scene.
void drawAxes()
{
    glDisable(GL_LIGHTING);

    glLineWidth(2.0f);
    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);

    glEnd();

    glEnable(GL_LIGHTING);
}

// Draws the floor grid that helps show position and depth in the scene.
void drawFloor()
{
    glDisable(GL_LIGHTING);

    glColor3f(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 0.0f,  5.0f);
        glVertex3f( 5.0f, 0.0f,  5.0f);
        glVertex3f( 5.0f, 0.0f, -5.0f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for (float i = -5.0f; i <= 5.0f; i += 1.0f)
    {
        glVertex3f(i, 0.01f, -5.0f);
        glVertex3f(i, 0.01f,  5.0f);

        glVertex3f(-5.0f, 0.01f, i);
        glVertex3f( 5.0f, 0.01f, i);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

// Draws the custom cube using vertex and face arrays, with transforms, colors and lighting normals.
void drawCubeObject()
{
    GLfloat vertices[8][3] =
    {
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f}
    };

    GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {1, 5, 6, 2},
        {5, 4, 7, 6},
        {4, 0, 3, 7},
        {3, 2, 6, 7},
        {4, 5, 1, 0}
    };

    GLfloat normals[6][3] =
    {
        { 0.0f,  0.0f,  1.0f},
        { 1.0f,  0.0f,  0.0f},
        { 0.0f,  0.0f, -1.0f},
        {-1.0f,  0.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f, -1.0f,  0.0f}
    };

    float cubeHighlight = (activeObject == 1) ? 1.15f : 1.0f;

    glPushMatrix();

    glTranslatef(-2.0f, 0.5f, 0.0f);
    glRotatef(cubeRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
    glScalef(cubeScale * cubeHighlight, cubeScale * cubeHighlight, cubeScale * cubeHighlight);

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++)
    {
        glNormal3fv(normals[i]);

        if (cubeColorMode == 5)
        {
            if (i == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else if (i == 1) glColor3f(0.0f, 1.0f, 0.0f);
            else if (i == 2) glColor3f(0.0f, 0.0f, 1.0f);
            else if (i == 3) glColor3f(1.0f, 1.0f, 0.0f);
            else if (i == 4) glColor3f(1.0f, 0.0f, 1.0f);
            else glColor3f(0.0f, 1.0f, 1.0f);
        }
        else
        {
            applyColor(cubeColorMode, 0.9f, 0.2f, 0.2f);
        }

        for (int j = 0; j < 4; j++)
        {
            int index = faces[i][j];
            glVertex3fv(vertices[index]);
        }
    }
    glEnd();

    glPopMatrix();
}

// Draws the sphere object with its transforms, scale and selected color mode.
void drawSphereObject()
{
    float sphereHighlight = (activeObject == 2) ? 1.15f : 1.0f;

    glPushMatrix();

    glTranslatef(0.0f, 0.7f, 0.0f);
    glRotatef(sphereRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(sphereRotX, 1.0f, 0.0f, 0.0f);
    glScalef(sphereScale * sphereHighlight, sphereScale * sphereHighlight, sphereScale * sphereHighlight);

    if (sphereColorMode == 5)
        applyIridescentColor();
    else
        applyColor(sphereColorMode, 0.2f, 0.7f, 1.0f);

    glutSolidSphere(0.7f, 30, 30);

    glPopMatrix();
}

// Draws the 2D polygon object using mathematically generated vertices with sin() and cos().
void drawPolygonObject()
{
    float polygonHighlight = (activeObject == 3) ? 1.15f : 1.0f;

    glPushMatrix();

    glTranslatef(2.0f, 0.01f, 0.0f);
    glRotatef(polygonRotY, 0.0f, 1.0f, 0.0f);
    glRotatef(polygonRotX, 1.0f, 0.0f, 0.0f);
    glScalef(polygonScale * polygonHighlight, polygonScale * polygonHighlight, polygonScale * polygonHighlight);

    if (polygonColorMode == 5)
        applyIridescentColor();
    else
        applyColor(polygonColorMode, 1.0f, 0.08f, 1.0f);

    const float radius = 0.8f;
    const int segments = 40;

    glNormal3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.14159f * i / segments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    glPopMatrix();
}   