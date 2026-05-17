#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include <vector>
#include "globals.h"

struct Vec2 { float x, y; };

static void gh_fillCircle(float cx, float cy, float r, int seg = 256)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float a = 2.f * (float)M_PI * i / seg;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

static void gh_fillEllipse(float cx, float cy, float rx, float ry, int seg = 256)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float a = 2.f * (float)M_PI * i / seg;
        glVertex2f(cx + rx * cosf(a), cy + ry * sinf(a));
    }
    glEnd();
}

static void gh_fillSector(float cx, float cy, float r,
                           float a0, float a1, int seg = 256)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= seg; i++) {
        float a = a0 + (a1 - a0) * i / seg;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

static void gh_fillPoly(const std::vector<Vec2>& pts)
{
    glBegin(GL_TRIANGLE_FAN);
    for (auto& p : pts) glVertex2f(p.x, p.y);
    glEnd();
}

static void gh_fillTail(int seg = 256)
{
    // Almost straight diagonal arm, only very slight curl at the tip.
    // P0=root, P1 & P2 nearly on the straight line, P3=tip with tiny upward lift.
    auto spineX = [](float t) -> float {
        float u = 1.f - t;
        // P0=-0.20  P1=-0.38  P2=-0.62  P3=-0.65
        return u*u*u*(-0.20f) + 3*u*u*t*(-0.38f) + 3*u*t*t*(-0.62f) + t*t*t*(-0.65f);
    };
    auto spineY = [](float t) -> float {
        float u = 1.f - t;
        // P0=-0.48  P1=-0.62  P2=-0.55  P3=-0.28  (dips down then curls back up)
        return u*u*u*(-0.48f) + 3*u*u*t*(-0.62f) + 3*u*t*t*(-0.55f) + t*t*t*(-0.28f);
    };

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= seg; i++) {
        float t  = (float)i / seg;
        float sx = spineX(t), sy = spineY(t);

        float dt = 0.004f;
        float tc = fminf(fmaxf(t, dt), 1.f - dt);
        float tx2 = spineX(tc + dt) - spineX(tc - dt);
        float ty2 = spineY(tc + dt) - spineY(tc - dt);
        float len = sqrtf(tx2*tx2 + ty2*ty2) + 1e-6f;
        float nx = -ty2 / len, ny = tx2 / len;

        float thickness = 0.08f * (1.f - t * 0.45f);
        glVertex2f(sx + nx * thickness, sy + ny * thickness);
        glVertex2f(sx - nx * thickness, sy - ny * thickness);
    }
    glEnd();

    gh_fillCircle(spineX(0.f), spineY(0.f), 0.08f);
    gh_fillCircle(spineX(1.f), spineY(1.f), 0.08f * 0.45f);
}

void drawGitHubLogo()
{
    int W = glutGet(GLUT_WINDOW_WIDTH);
    int H = glutGet(GLUT_WINDOW_HEIGHT);

    float size = H * 0.52f;
    float cx   = W * 0.78f;
    float cy   = H * 0.50f;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, W, 0, H);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    // Apply independent logo transforms (translate → rotate → scale)
    // Use a slightly compressed Y scale to keep the body proportional
    glTranslatef(cx + logoTx, cy + logoTy, 0.0f);
    glRotatef(logoRot, 0.0f, 0.0f, 1.0f);
    glScalef(size * 0.5f * logoScale, size * 0.42f * logoScale, 1.0f);

    glColor3f(0.067f, 0.067f, 0.067f);
    gh_fillCircle(0.f, 0.f, 0.88f);

    glColor3f(0.925f, 0.925f, 0.925f);

    gh_fillTail();

    float nw = 0.20f, ntop = 0.05f, nbot = -0.68f;
    gh_fillPoly({{-nw,ntop},{nw,ntop},{nw,nbot},{-nw,nbot}});
    gh_fillCircle(0.0f, nbot, nw);
    gh_fillEllipse(0.f, 0.15f, 0.44f, 0.36f);
    gh_fillCircle(-0.25f, 0.15f, 0.20f);
    gh_fillCircle( 0.25f, 0.15f, 0.20f);
    gh_fillPoly({{-0.38f,0.35f},{-0.30f,0.65f},{-0.10f,0.45f}});
    gh_fillPoly({{ 0.38f,0.35f},{ 0.30f,0.65f},{ 0.10f,0.45f}});

    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
