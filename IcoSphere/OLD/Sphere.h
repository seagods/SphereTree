#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "/usr/include/SDL/SDL.h"
#include "D3Dvec.h"
#include "Triangle.h"

#include "throwcatch.h"

extern const double twopi,pi;
extern double angx, angy;
extern double angxcum, angycum;
//const unsigned short int SCREEN_DEPTH=16;
#define SCREEN_DEPTH 16
/*   #define SCREEN_WIDTH  1024 */
     #define SCREEN_WIDTH  800 
/*   #define SCREEN_HEIGHT 768  */
#define SCREEN_HEIGHT 600

double W=50000;
double H=50000;
double D=50000;
double xx1=-W;
double xx2=W;
double yy1=-H;
double yy2=H;
double zz1=-D;
double zz2=D;


double X,Y,Z;


//For 3D Points
int*  npoint3Darray;
double **xarray,**yarray,**zarray;

#include "Camera.h"
#include "gl2ps.h"

extern int VideoFlags;
extern SDL_Surface * MainWindow;

extern int width,height;
extern const double speed;
extern const double acceleration;
extern const double convert;

extern int DisplayListID;


typedef unsigned char byte;

// Prototypes for functions
void EventLoop(CCam  & Camera1);
void RenderScene(CCam  & Camera1);
void SetUp();
void ToggleWindow(void);
void MakeWindow(const char *Name, int width, int height, int VideoFlags);
void SizeOpenGLScreen(int, int);
void Init();
void InitialiseGL(int, int);
void HandleKeyPress(SDL_keysym * );
void HandleKeyRelease(SDL_keysym *);
void CheckMove(CCam &);
int Screenshot(SDL_Surface *screen, char *filename);

void CreateTexture(unsigned int textureArray[], char *strFilename, int textureID);

#include "Init.h"

