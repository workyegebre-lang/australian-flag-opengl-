
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include "globals.h"


void drawStar(float cu, float cv,
              float outerR, float innerR,
              int   npts,   float angleDeg)
{
    float wx = cu * FW;
    float wy = cv * FH;
    float wz = flagWaveZ(cu, cv);   

    float rx  = outerR * FW,  ry  = outerR * FH;
    float rix = innerR * FW,  riy = innerR * FH;

    float angleOffset = angleDeg * (float)M_PI / 180.0f;
    int   total       = npts * 2;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(wx, wy, wz);  

    for (int i = 0; i <= total; ++i)
    {
        float a    = angleOffset + i * (float)M_PI / npts;
        bool outer = (i % 2 == 0);
        float ex   = outer ? rx  : rix;
        float ey   = outer ? ry  : riy;

     
        float pu = (wx + ex * cosf(a)) / FW;
        float pv = (wy + ey * sinf(a)) / FH;
        float pz = flagWaveZ(pu, pv);

        glVertex3f(wx + ex * cosf(a),
                   wy + ey * sinf(a),
                   pz);
    }
    glEnd();
}


void drawStars()
{
    glColor3f(R_WHT, G_WHT, B_WHT);

    
    drawStar(0.25f, 0.25f,  0.072f, 0.030f,  7,  -90.0f);

   
    drawStar(0.76f, 0.22f,  0.062f, 0.026f,  7,  -90.0f);
    drawStar(0.63f, 0.60f,  0.054f, 0.022f,  7,  -90.0f);
    drawStar(0.76f, 0.78f,  0.054f, 0.022f,  7,  -90.0f);
    drawStar(0.90f, 0.60f,  0.048f, 0.020f,  7,  -90.0f);
    drawStar(0.83f, 0.42f,  0.028f, 0.012f,  5,  -90.0f);
}
