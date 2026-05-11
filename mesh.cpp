
// Member 2 – Flag Mesh & Wave Mathematics
 //File: mesh.cpp
 #ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include "globals.h"

void bgColour(float cu, float cv, float &r, float &g, float &b);

// Shared wave function — used by both the mesh and the stars
float flagWaveZ(float u, float v)
{
    float x = u * FW;
    float y = v * FH;

    float damping   = powf(sinf((float)M_PI * u * 0.5f), DAMP_POWER);
    float windPhase = (x * windDirX + y * windDirZ);
    float wave1     = sinf(BASE_FREQ   * windPhase - waveTime);
    float wave2     = 0.5f * sinf(SECOND_FREQ * windPhase - waveTime * 1.5f);
    float noise     = 0.2f * sinf(NOISE_FREQ  * windPhase + waveTime * 2.0f);

    return WAVE_AMP * windStrength * damping * (wave1 + wave2 + noise);
}

void flagVtx(float u, float v)
{
    glVertex3f(u * FW, v * FH, flagWaveZ(u, v));
}

void drawFlagMesh()
{
    float du = 1.0f / COLS;
    float dv = 1.0f / ROWS;

    for (int j = 0; j < ROWS; ++j)
    {
        float v0 = j * dv, v1 = v0 + dv;

        for (int i = 0; i < COLS; ++i)
        {
            float u0 = i * du, u1 = u0 + du;
            float r, g, b;

            glBegin(GL_QUADS);

            bgColour(u0, v0, r, g, b); glColor3f(r, g, b); flagVtx(u0, v0);

            bgColour(u1, v0, r, g, b); glColor3f(r, g, b); flagVtx(u1, v0);

            bgColour(u1, v1, r, g, b); glColor3f(r, g, b); flagVtx(u1, v1);

            bgColour(u0, v1, r, g, b); glColor3f(r, g, b); flagVtx(u0, v1);

            glEnd();
        }
    }
}