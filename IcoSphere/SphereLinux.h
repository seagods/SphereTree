//-------------------------------------------------------------------------------
// Copyright 2020 Christopher Godsalve.
// All Rights Reserved.
//
// Permission to use, copy, modify and distribute this software (if not modified) and its
// documentation for educational, research and non-profit purposes, without fee,
// and without a written agreement is hereby granted, provided that the above
// copyright notice - this paragraph - and the following three paragraphs appear in all copies.
// 
//
// To request permission to incorporate this software into commercial products
// contact Dr C. Godsalve, 42 Swainstone Road, Reading, Berks, UK or by email at
// seagods@btinternet.com or seagods@hotmail.com.
//
// IN NO EVENT SHALL CHRISTOPHER GODSALVE BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING 
// LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
// EVEN IF CHRITOPHER GODSALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// CHRISTOPHER GODSALVE SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN `AS IS' BASIS, AND CHRISTOPHER 
// GODSALVE HAS NO OBLIGATIONS TO PROVIDE MAINTAINANCE, SUPPORT, UPDATES, 
// ENHANCEMENTS, OR MODIFICATIONS IF HE CHOOSES NOT TO DO SO.
//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <sstream>

//include declarations and prototypes --- needed or not!
/***********************************************************************************/
#include <GL/gl.h>
#include <GL/glu.h>

#include "/usr/include/SDL/SDL.h"
#include "/usr/local/include/XFILESlinuxD3Dvec.h"
#include "/usr/local/include/XFILESlinuxD2Dvec.h"
#include "/usr/local/include/XFILESlinuxTriangle.h"
#include "/usr/local/include/XFILESlinuxthrowcatch.h"

double speed=50.0, angspeed=0.05;

const char* WindowTitle="Sphere!";
bool picking=false;


typedef unsigned char byte;
typedef unsigned short int USHORT;
typedef unsigned int UINT;
typedef unsigned int DWORD;  //yep, a DWORD is the same as a UINT...
                             //we use it for stuff that has DWORD
			     //or glEnum types.

const USHORT WIDTH=800, HEIGHT=600;
const USHORT SCREEN_DEPTH=16;

extern const double twopi,pi;  //initialised externally

/*********************************************************/
/*           for periodic boundary condition special case */
bool startoffx=true;
bool startoffy=true;
bool launch=true;
/*************************************************************/
bool periodic_xz=false;  //periodiv in PRESENTATION and in OpenGL coords
bool periodicbcs=false;  //actual periodic boundary conditions in xy
bool collisiontest=false;
bool foggy=false;
bool drawlines=true;
bool drawback=true;  // draw background when controls are up
bool PickTri=false;  //if false, we pick nodes and not triangles
bool Gouraud=true;    //smooth Gouraud shading
bool Picking=false;  //don't pick anyithing if false
/********************MODES***********************************/
bool twodee=false;  // camera moves in xz only

                      //One, but ONE ONLY  of these three
		      //MUST be true
bool freedom=false;      // if true viewer is free to move anywhere
bool tethered=true;   //  if true viewer is attached to fixed point by a boom
bool staked=false;    //   if true viewer is not free to move, but can look about

bool wander=false;    //one of these must be set true if free is true
bool flight=false;

bool aeroplane=false;   // if true we have aeroplane roll - pitch control

                        
bool boom=true;      //  needed for tethered only 
                      //  if boom true  make exwhyzed false
bool exwhyzed=false;   //  if tethered make boom false if exwhyzed is true
                      //  if wander must always be true
		      //  if flight can be true or false
		      //  make false if aeroplane true
		      //
bool hidemousecursor=false;      

/*************************************************************/
int iside, ihalfside;   // iside is the number of segments per side
             //not the number of nodes!
double xlength, xside, scalefac;
int ix, iz;
int ixold, izold; 
int diffx, diffz;
int diffoldx, diffoldz;
int yshiftedge, xshiftedge;
double **xshift, **yshift;
int **index1, **index2;

void SetShiftX(int);
void SetShiftY(int);

/**********************************************************************/
D3Dvec *NodeV;
Triangle* Triangles;
D3Dvec* edges1;
D3Dvec* edges2;
D3Dvec* Normals;
D3Dvec* NormalsG;
#include "/usr/local/include/XFILESlinuxList.h"
#include "/usr/local/include/XFILESlinuxNode1.h"
typedef CMyNode1<int>  ListNode;
typedef CMyNode1<char>  ListNode_char;
typedef CMyLinkedList<ListNode> intList;
typedef CMyLinkedList<ListNode_char> charList;
int const MD=4;  //MAXIMUM DEPTH OF TREE (depth ranges from 0 to MD
    intList** CollideTri; 
    int nlists;
    intList*  NodeList;  
    charList*  WhichList;  
//intList hangs is attached to a tree branch, iNodeList is attatched to a node.



#include "/usr/local/include/XFILESlinuxTriOctNode.h"
#include "/usr/local/include/XFILESlinuxTriOctTree.h"
typedef CMyOctNode <D3Dvec> ONode; //An ONode shall hold a vector
                                   //describing the compare point
				   // and a list of integers
				   // (Triangle array indexes)
typedef CMyTriOctTree<ONode> OTree;   //OctTree consists of nodes
        OTree* CollideTree;
/**********************************************************************/
#include "/usr/local/include/XFILESlinuxDmatrix.h"
//#include "/usr/local/include/XFILESlinuxSolver.h"
/**********************************************************************/
//void Solver(int &dim, double &maxerr, Dmatrix& Matrix, Dvector& rhs, Dvector& SolveVec);
int myGaussElim(int& dimen , double** Matr , double* VexRhs, double* VexLhs );
/**********************************************************************/

D3Dvec RealCamPos;  //periodic boundary conditions
                    //CamPos thinks it  wanders in infinite space
		    //But RealCamPos knows about the pbc.
double X1, X2, Y1, Y2, Z1, Z2;
#include "/usr/local/include/XFILESlinuxCamera.h"
#include "/usr/local/include/XFILESlinuxgl2ps.h"

extern int VideoFlags;
extern SDL_Surface * MainWindow;

extern double speed;
extern const double convert;


// Prototypes for functions
void EventLoop(CCam  & Camera1);
void EventLoop();
void RenderScene(CCam  & Camera1);
void PickObjects();
void ProcessHitsLP(int, UINT *);
void ProcessHitsLC(int, UINT *);
void ProcessHitsLB(int, UINT *);
void ProcessHitsMC(int, UINT *);
void ProcessHitsDT(int, UINT *);
void ProcessHitsPC1(int, UINT *);
void ProcessHitsLeg(int, UINT *);
void ProcessTriangleHits(int, UINT *);
void ProcessNodeHits(int, UINT *);
void SetUp();
void ToggleWindow(void);
void MakeWindow(const char *Name, 
		const USHORT WIDTH,
	        const USHORT HEIGHT,
		 int VideoFlags);
void SizeOpenGLScreen(const USHORT, const USHORT);
void Init();
void InitialiseGL(int, int);
void HandleKeyPress(SDL_keysym * );
void HandleKeyRelease(SDL_keysym *);
void CheckMove(CCam &);
int Screenshot(SDL_Surface *screen, char *filename);

void CreateTexture(unsigned int textureArray[], char *strFilename, int textureID);

void OrthoMode(double , double , double, double);
void PerspectiveMode();
void DrawLightPos(bool);
void DrawLightCol(bool);
void DrawMatCol(bool);
void DrawLogicBox(bool);
void DrawTextMove(bool);
void DrawCurveCol(bool);
void DrawLegend(bool);

extern UINT base;
//bitmap font functions
void buildFont(void); 
void QuitFont(int );    
void KillFont();
void glPrint( char *);

void SetShiftX(int);
void SetShiftY(int);

void DrawScene(CCam &, bool);
/**********************************************************************************/



int arg_count;
char **arg_list;

#include "/usr/local/include/XFILESlinuxInit.h"

int nplots;   
const int nplotsmax=40;
int *ndata, *ntype, *ncol, *nstyle, *npoint;
// ntype=1 for line 0 for point, npoint is the line thickness or pointsize

double **x;  //the data
double **y;
double **z;

double xmin,xmax,xrange;
double ymin,ymax,yrange;
double zmin,zmax,zrange;

double xexp,yexp,zexp;
double xfact,yfact,zfact;
double xrange_scale, yrange_scale, zrange_scale;
bool xmin_zero=false, ymin_zero=false, xmax_zero=false, ymax_zero=false;
bool zmin_zero=false, zmax_zero;
bool xboth=false, yboth=false, zboth;

double xminexp,yminexp,zminexp;
double xminfact,yminfact,zminfact;
double xmin_scale,ymin_scale,zmin_scale;;

bool  xaddsubtract=false, yaddsubtract=false,zaddsubtract;

int ixnumb, iynumb, iznumb;  //number of major tick marks and axis numbers
int ixnumb2,iynumb2, iznumb2;  //number of minor tickmarks

double xminshift,xstep,xstep_scale,x_start,xsubtract;  //different to xstart in SetUp.h
double yminshift,ystep,ystep_scale,y_start,ysubtract;
double zminshift,zstep,zstep_scale,z_start,zsubtract;  
double x_start2,y_start2, z_start2,xstep2,ystep2,zstep2; //minor tickmarks

double xnumbers[13], ynumbers[13], znumbers[13];
double xnumbers2[130], ynumbers2[130], znumbers2[130]; //for minor ticks algorithm
string xstrings[13], ystrings[13], zstrings[13];

//keep 2d bounding box the same
//Camera is at  (0,0,3000) OpenGL coords
double xlow=-800.0,zlow=-800.,ylow=-800.,xhigh=800.0,yhigh=800,zhigh=800.0;

int smallticksx,smallticksy,smallticksz;

string xtext,xunits,xaxistext,ytext,yunits,yaxistext,ztext,zunits,zaxistext;
int ixtext,ixunits,iytext,iyunits,iztext,izunits;
string xtextmod, ytextmod, ztextmod;
bool xtimesdiv, ytimesdiv, ztimesdiv;

double shift1;  // shift all x axis numbers left  x 1&4, y 2&5, z 3&6
double shift2;  // shift all y axis numbers out
double shift3;  // shift all z axis numbers down
double shift4;  // shift all x numbers  out/in
double shift5;  // shift all y numbers  left/right
double shift6;  // shift all z  numbers  up/down
double shift7;  // shift x axis text left
double shift8;  // shift x axis text in/out
double shift9; // shift y axis text in/out
double shift10; // shift y axis text  left/right
double shift11; // shift z axis text  up/down
double shift12; // shift z axis text  radially

bool LegendExists;
string *LegendStrings;


#include "/usr/local/include/XFILESlinuxnumbers_xyz.h"




