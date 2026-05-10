
 // Member 1 – Window Initialisation, Camera & Main Loop
 // File: main.cpp
 #ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cstdlib>
#include "globals.h"

void drawFlagMesh();
void drawStars();
void drawGitHubLogo();
void drawPole();
void drawGround();
void drawHUD();

extern const float FW;
extern const float FH;

extern void keyboard(unsigned char, int, int);
extern void specialKey(int, int, int);

void display()
{
    int W = glutGet(GLUT_WINDOW_WIDTH);
    int H = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)W / H, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(FW * 0.5f, FH * 0.5f, 5.5f,
              FW * 0.5f, FH * 0.5f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glTranslatef(tx, 0.0f, 0.0f);

    float cx = FW * 0.5f, cy = FH * 0.5f;
    glTranslatef(cx, cy, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cx, -cy, 0.0f);

    glTranslatef(cx, cy, 0.0f);
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glTranslatef(-cx, -cy, 0.0f);

    drawGround();
    drawPole();
    drawFlagMesh();

    glDisable(GL_DEPTH_TEST);
    drawStars();
    glEnable(GL_DEPTH_TEST);

    drawHUD();
    drawGitHubLogo();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
}

void timerCB(int)
{
    waveTime += 0.02f * WAVE_SPEED * windStrength;
    glutPostRedisplay();
    glutTimerFunc(16, timerCB, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 600);
    glutCreateWindow("Simulation of a Waving Australian National Flag");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timerCB, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);

    printf("\n=== Waving Australian National Flag + GitHub Octocat ===\n");
    printf("  LEFT/RIGHT  – Translate flag    A/D – Rotate flag Y\n");
    printf("  W/S         – Scale flag        I/K – Wind strength\n");
    printf("  J/L         – Wind dir          R   – Reset   ESC – Quit\n");
    printf("\n  --- GitHub Logo Transforms ---\n");
    printf("  F/H  – Translate logo X         T/G – Translate logo Y\n");
    printf("  Q/E  – Rotate logo              Z/X – Scale logo\n\n");

    glutMainLoop();
    return 0;
}