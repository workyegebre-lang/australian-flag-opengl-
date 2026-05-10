
// globals.cpp  –  Definitions for all shared global variables
 // Created by Member 1
 #include "globals.h"

const float FW = 4.0f;
const float FH = 2.0f;

const int COLS = 200;
const int ROWS = 120;

const float WAVE_AMP    = 0.14f;
const float WAVE_SPEED  = 2.0f;
const float BASE_FREQ   = 2.2f;
const float SECOND_FREQ = 4.0f;
const float NOISE_FREQ  = 7.5f;
const float DAMP_POWER  = 1.5f;

float waveTime     = 0.0f;
float windDirX     = 1.0f;
float windDirZ     = 0.3f;
float windStrength = 1.2f;

float tx          = 0.0f;
float rotY        = 0.0f;
float scaleFactor = 1.0f;

// GitHub logo independent transforms
float logoTx    = 0.0f;
float logoTy    = 0.0f;
float logoRot   = 0.0f;
float logoScale = 1.0f;