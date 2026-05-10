
  //globals.h  –  Shared globals & constants
 //Created by Member 1
 #ifndef GLOBALS_H
#define GLOBALS_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern const float FW;
extern const float FH;

extern const int COLS;
extern const int ROWS;

extern const float WAVE_AMP;
extern const float WAVE_SPEED;
extern const float BASE_FREQ;
extern const float SECOND_FREQ;
extern const float NOISE_FREQ;
extern const float DAMP_POWER;

extern float waveTime;
extern float windDirX;
extern float windDirZ;
extern float windStrength;

extern float tx;
extern float rotY;
extern float scaleFactor;

// GitHub logo independent transforms
extern float logoTx;
extern float logoTy;
extern float logoRot;
extern float logoScale;

// Wave Z value at a given UV position (shared by mesh and stars)
extern float flagWaveZ(float u, float v);

#define R_BLUE  (0.0f/255.0f)
#define G_BLUE  (0.0f/255.0f)
#define B_BLUE  (139.0f/255.0f)

#define R_RED   (204.0f/255.0f)
#define G_RED   0.0f
#define B_RED   0.0f

#define R_WHT   1.0f
#define G_WHT   1.0f
#define B_WHT   1.0f

#endif