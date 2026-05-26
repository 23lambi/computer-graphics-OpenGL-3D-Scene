#include <GLUT/glut.h>
#include "welcome.h"
#include "scene.h"
#include "app_state.h"
#include "ui.h"
#include <cstdlib>
#include <cstdio>

int cubeColorMode = 0;
int sphereColorMode = 0;
int polygonColorMode = 0;

bool showWelcome = true;
int activeObject = 1;

float cubeRotX = 0.0f, cubeRotY = 0.0f, cubeScale = 1.0f;
float sphereRotX = 0.0f, sphereRotY = 0.0f, sphereScale = 1.0f;
float polygonRotX = 0.0f, polygonRotY = 0.0f, polygonScale = 1.0f;

bool autoRotate = false;
bool usePerspective = true;

int windowWidth = 800;
int windowHeight = 800;

float cameraDistance = 10.0f;
float orthoZoom = 8.0f;

bool isShiftZooming = false;
int lastMouseY = 0;


// Requests a redraw of the window whenever scene state changes.
void requestRedraw()
{
    glutPostRedisplay();
}

// Selects which object is currently active for transforms and color changes.
void selectObject(int objectId)
{
    activeObject = objectId;
    showWelcome = false;
    requestRedraw();
}

// Applies a selected color mode to the currently active object.
void applyColorToActiveObject(int colorMode)
{
    if (activeObject == 1)
        cubeColorMode = colorMode;
    else if (activeObject == 2)
        sphereColorMode = colorMode;
    else if (activeObject == 3)
        polygonColorMode = colorMode;

    showWelcome = false;
    requestRedraw();
}

// Turns automatic rotation on or off for the active object.
void toggleAutoRotate()
{
    autoRotate = !autoRotate;
    showWelcome = false;
    requestRedraw();
}

// Switches between perspective and orthographic projection.
void toggleProjection()
{
    usePerspective = !usePerspective;
    requestRedraw();
}

// Handles special keyboard keys (arrow keys) to rotate the active object.
void specialKeys(int key, int x, int y)
{
    if (activeObject == 1)
    {
        if (key == GLUT_KEY_LEFT)  cubeRotY -= 5.0f;
        if (key == GLUT_KEY_RIGHT) cubeRotY += 5.0f;
        if (key == GLUT_KEY_UP)    cubeRotX -= 5.0f;
        if (key == GLUT_KEY_DOWN)  cubeRotX += 5.0f;
    }
    else if (activeObject == 2)
    {
        if (key == GLUT_KEY_LEFT)  sphereRotY -= 5.0f;
        if (key == GLUT_KEY_RIGHT) sphereRotY += 5.0f;
        if (key == GLUT_KEY_UP)    sphereRotX -= 5.0f;
        if (key == GLUT_KEY_DOWN)  sphereRotX += 5.0f;
    }
    else if (activeObject == 3)
    {
        if (key == GLUT_KEY_LEFT)  polygonRotY -= 5.0f;
        if (key == GLUT_KEY_RIGHT) polygonRotY += 5.0f;
        if (key == GLUT_KEY_UP)    polygonRotX -= 5.0f;
        if (key == GLUT_KEY_DOWN)  polygonRotX += 5.0f;
    }

    requestRedraw();
}

// Draws either the welcome screen or the main 3D scene depending on program state.
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (showWelcome)
    {
        displayWelcome();
        return;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)windowWidth / (float)windowHeight;

    if (usePerspective)
    {
        gluPerspective(60.0, aspect, 1.0, 50.0);
    }
    else
    {
        if (aspect >= 1.0f)
        {
            glOrtho(-orthoZoom * aspect, orthoZoom * aspect,
                    -orthoZoom, orthoZoom,
                    -50.0f, 50.0f);
        }
        else
        {
            glOrtho(-orthoZoom, orthoZoom,
                    -orthoZoom / aspect, orthoZoom / aspect,
                    -50.0f, 50.0f);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6.0, 4.5, cameraDistance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    GLfloat lightPos[] = { 4.0f, 6.0f, 4.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    drawAxes();

    glDisable(GL_LIGHTING);
    drawFloor();
    glEnable(GL_LIGHTING);

    drawCubeObject();
    drawSphereObject();
    drawPolygonObject();

    glDisable(GL_LIGHTING);
    drawInstructions();
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

// Handles normal keyboard input for start, exit, object selection, scaling, colors, rotation toggle and projection mode.
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }

    if (showWelcome && (key == 's' || key == 'S' || key == 13))
    {
        showWelcome = false;
        requestRedraw();
        return;
    }

    if (key == '1') selectObject(1);
    if (key == '2') selectObject(2);
    if (key == '3') selectObject(3);

    if (key == '+' || key == '=')
    {
        if (activeObject == 1 && cubeScale < 2.0f) cubeScale += 0.1f;
        if (activeObject == 2 && sphereScale < 2.0f) sphereScale += 0.1f;
        if (activeObject == 3 && polygonScale < 2.0f) polygonScale += 0.1f;
        requestRedraw();
    }

    if (key == '-' || key == '_')
    {
        if (activeObject == 1 && cubeScale > 0.3f) cubeScale -= 0.1f;
        if (activeObject == 2 && sphereScale > 0.3f) sphereScale -= 0.1f;
        if (activeObject == 3 && polygonScale > 0.3f) polygonScale -= 0.1f;
        requestRedraw();
    }

    if (!showWelcome && key == ' ')
        toggleAutoRotate();

    if (key == 'c' || key == 'C') applyColorToActiveObject(1);
    if (key == 'r' || key == 'R') applyColorToActiveObject(2);
    if (key == 'g' || key == 'G') applyColorToActiveObject(3);
    if (key == 'o' || key == 'O') applyColorToActiveObject(4);
    if (key == 'm' || key == 'M') applyColorToActiveObject(5);

    if (key == 'p' || key == 'P')
        toggleProjection();
}

// Keeps the viewport and aspect ratio correct when the window size changes.
void reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);

    printf("Reshape: width=%d height=%d\n", w, h);
    requestRedraw();
}

// Handles mouse button events and starts zoom interaction when Shift + left click is used.
void mouse(int button, int state, int x, int y)
{
    printf("Mouse: button=%d state=%d x=%d y=%d\n", button, state, x, y);

    int modifiers = glutGetModifiers();

    if (button == GLUT_LEFT_BUTTON && (modifiers & GLUT_ACTIVE_SHIFT))
    {
        if (state == GLUT_DOWN)
        {
            isShiftZooming = true;
            lastMouseY = y;
            printf("Shift zoom start\n");
        }
        else if (state == GLUT_UP)
        {
            isShiftZooming = false;
            printf("Shift zoom end\n");
        }
    }
}

// Handles mouse movement during Shift + drag zooming.
void motion(int x, int y)
{
    if (isShiftZooming)
    {
        int dy = y - lastMouseY;

        if (usePerspective)
        {
            cameraDistance += dy * 0.05f;

            if (cameraDistance < 4.0f)
                cameraDistance = 4.0f;
            if (cameraDistance > 25.0f)
                cameraDistance = 25.0f;

            printf("Perspective zoom: cameraDistance=%.2f x=%d y=%d\n", cameraDistance, x, y);
        }
        else
        {
            orthoZoom += dy * 0.05f;

            if (orthoZoom < 2.0f)
                orthoZoom = 2.0f;
            if (orthoZoom > 20.0f)
                orthoZoom = 20.0f;

            printf("Orthographic zoom: orthoZoom=%.2f x=%d y=%d\n", orthoZoom, x, y);
        }

        lastMouseY = y;
        requestRedraw();
    }
}

// Continuously updates automatic rotation and keeps the scene redrawn.
void idle()
{
    if (autoRotate)
    {
        if (activeObject == 1)
            cubeRotY += 0.2f;
        else if (activeObject == 2)
            sphereRotY += 0.2f;
        else if (activeObject == 3)
            polygonRotY += 0.2f;
    }

    requestRedraw();
}

// Handles right-click menu actions for object selection, color changes and rotation toggle.
void menu(int value)
{
    switch (value)
    {
        case 1:  selectObject(1); break;
        case 2:  selectObject(2); break;
        case 3:  selectObject(3); break;
        case 10: applyColorToActiveObject(1); break;
        case 11: applyColorToActiveObject(2); break;
        case 12: applyColorToActiveObject(3); break;
        case 13: applyColorToActiveObject(4); break;
        case 14: applyColorToActiveObject(5); break;
        case 20: toggleAutoRotate(); break;
    }
}

// Initializes GLUT, OpenGL settings, callbacks and the right-click menu, then starts the main loop.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("OpenGL 3D Scene");
    glClearColor(0.08f, 0.10f, 0.14f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    GLfloat lightPos[] = { 4.0f, 6.0f, 4.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    int objectMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Cube", 1);
    glutAddMenuEntry("Sphere", 2);
    glutAddMenuEntry("2D Shape", 3);

    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Cyan", 10);
    glutAddMenuEntry("Red", 11);
    glutAddMenuEntry("Green", 12);
    glutAddMenuEntry("Orange", 13);
    glutAddMenuEntry("Multicolor / Iridescent", 14);

    int rotationMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Auto Rotate", 20);

    glutCreateMenu(menu);
    glutAddSubMenu("Select Object", objectMenu);
    glutAddSubMenu("Select Color", colorMenu);
    glutAddSubMenu("Rotation", rotationMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}