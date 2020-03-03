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
#include "UnivPlotz.h"



int arg_count;
char **arg_list;

#include "C:\myIncludez\XFILESwin32\Init.h"

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


#include "C:\myIncludez\XFILESwin32\numbers_xyz.h"



