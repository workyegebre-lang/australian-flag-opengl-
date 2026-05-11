//* Member 3 – Australian Flag Colours & Union Jack Canton 
//* File: colours.cpp
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include "globals.h"

static void unionJack(float x, float y, float &r, float &g, float &b)
{
    r = R_BLUE; g = G_BLUE; b = B_BLUE;

    float cx = x - 0.5f;
    float cy = y - 0.5f;

    const float DIAG_WHITE = 0.14f;
    const float DIAG_RED   = 0.06f;
    const float CROSS_WHT  = 0.18f;
    const float CROSS_RED  = 0.11f;

    float d1 = (cx - cy) / 1.41421f;
    float d2 = (cx + cy) / 1.41421f;

    if (fabsf(d1) < DIAG_WHITE || fabsf(d2) < DIAG_WHITE)
    {
        r = R_WHT; g = G_WHT; b = B_WHT;
    }

    if (fabsf(d1) < DIAG_WHITE)
    {
        float offset = (cy >= 0.f) ? +DIAG_RED : -DIAG_RED;
        if (fabsf(d1 - offset) < DIAG_RED)
            { r = R_RED; g = G_RED; b = B_RED; }
    }

    if (fabsf(d2) < DIAG_WHITE)
    {
        float offset = (cx >= 0.f) ? +DIAG_RED : -DIAG_RED;
        if (fabsf(d2 - offset) < DIAG_RED)
            { r = R_RED; g = G_RED; b = B_RED; }
    }

    float ax = fabsf(cx);
    float ay = fabsf(cy);

    if (ax < CROSS_WHT || ay < CROSS_WHT)
    {
        r = R_WHT; g = G_WHT; b = B_WHT;
        if (ax < CROSS_RED || ay < CROSS_RED)
            { r = R_RED; g = G_RED; b = B_RED; }
    }
}

void bgColour(float cu, float cv, float &r, float &g, float &b)
{
    r = R_BLUE; g = G_BLUE; b = B_BLUE;

    if (cu < 0.5f && cv > 0.5f)
    {
        float x = cu / 0.5f;
        float y = (cv - 0.5f) / 0.5f;
        unionJack(x, y, r, g, b);
    }
}

