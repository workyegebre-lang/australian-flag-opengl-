
 #ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "globals.h"

void drawPole()
{
    glColor3f(0.60f, 0.60f, 0.60f);
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -0.8f,       0.0f);
    glVertex3f(0.0f,  FH + 0.5f,  0.0f);
    glEnd();
    glLineWidth(1.0f);

    glPointSize(12.0f);
    glColor3f(1.0f, 0.85f, 0.0f);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, FH + 0.5f, 0.0f);
    glEnd();
    glPointSize(1.0f);
}

void drawGround()
{
    glColor3f(0.25f, 0.50f, 0.15f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.5f, -0.8f, 0.0f);
    glVertex3f( 6.0f, -0.8f, 0.0f);
    glEnd();
    glLineWidth(1.0f);
}

void drawHUD()
{
    int W = glutGet(GLUT_WINDOW_WIDTH);
    int H = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, W, 0, H);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glColor3f(0.0f, 0.0f, 0.0f);

    auto str = [](float x, float y, const char *s) {
        glRasterPos2f(x, y);
        while (*s) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s++);
    };

    char buf[256];

    str(10, H - 18,
        "Simulation of a Waving Australian National Flag  |  GitHub Octocat");

    str(10, 38, "Flag Transforms:");

    snprintf(buf, sizeof(buf),
             "  Translation X: %.2f  (LEFT / RIGHT)", tx);
    str(10, 25, buf);

    snprintf(buf, sizeof(buf),
             "  Rotation Y: %.1f deg  (A / D)    Scale: %.2f  (W / S)",
             rotY, scaleFactor);
    str(10, 13, buf);

    snprintf(buf, sizeof(buf),
             "  Wind strength: %.1f (I/K)   Wind dir: %.1f (J/L)"
             "   R=Reset   ESC=Quit",
             windStrength, windDirX);
    str(10, 1, buf);

    // Logo transform info (top-right area)
    str(W - 420, H - 18, "Logo Transforms:");

    snprintf(buf, sizeof(buf),
             "  Translate: (%.0f, %.0f)  (F/H, T/G)", logoTx, logoTy);
    str(W - 420, H - 31, buf);

    snprintf(buf, sizeof(buf),
             "  Rotate: %.1f deg  (Q/E)    Scale: %.2f  (Z/X)",
             logoRot, logoScale);
    str(W - 420, H - 44, buf);

    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'a': case 'A': rotY -= 3.0f; break;
        case 'd': case 'D': rotY += 3.0f; break;

        case 'w': case 'W': scaleFactor += 0.05f; break;
        case 's': case 'S': scaleFactor = fmaxf(0.1f, scaleFactor - 0.05f); break;

        case 'i': case 'I': windStrength += 0.1f; break;
        case 'k': case 'K': windStrength = fmaxf(0.1f, windStrength - 0.1f); break;

        case 'j': case 'J': windDirX -= 0.1f; break;
        case 'l': case 'L': windDirX += 0.1f; break;

        // GitHub logo transforms
        case 'f': case 'F': logoTx -= 10.0f; break;
        case 'h': case 'H': logoTx += 10.0f; break;
        case 't': case 'T': logoTy += 10.0f; break;
        case 'g': case 'G': logoTy -= 10.0f; break;
        case 'q': case 'Q': logoRot += 5.0f;  break;
        case 'e': case 'E': logoRot -= 5.0f;  break;
        case 'z': case 'Z': logoScale = fmaxf(0.1f, logoScale - 0.05f); break;
        case 'x': case 'X': logoScale += 0.05f; break;

        case 'r': case 'R':
            tx = 0.0f;
            rotY = 0.0f;
            scaleFactor = 1.0f;
            windStrength = 1.2f;
            windDirX = 1.0f;
            logoTx    = 0.0f;
            logoTy    = 0.0f;
            logoRot   = 0.0f;
            logoScale = 1.0f;
            break;

        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

void specialKey(int key, int, int)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:  tx -= 0.1f; break;
        case GLUT_KEY_RIGHT: tx += 0.1f; break;
    }
    glutPostRedisplay();
}