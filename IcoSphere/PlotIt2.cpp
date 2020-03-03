//-------------------------------------------------------------------------------
// Copyright 2008-2011 Christopher Godsalve.
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
using namespace std;
#include "PlotIt2.h"

#include "C:\myIncludez\XFILESwin32\TrueType.h"

#include "C:\myIncludez\XFILESwin32\SetUp.h"  //loads of declarations and initialisations
#include "C:\myIncludez\XFILESwin32\Controls.h"
#include "C:\myIncludez\XFILESwin32\DrawTextMove2.h"
#include "C:\myIncludez\XFILESwin32\DrawCurveCol.h"
#include "C:\myIncludez\XFILESwin32\DrawLegend.h"
#include "C:\myIncludez\XFILESwin32\DrawLogicBox.h"

#define LINE0 0xFFFF
#define LINE1 0x0101
#define LINE2 0x00FF
#define LINE3 0x1C47
#define LINE4 0x3F07

void EventLoop()
{
 LIGHTS=false;
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 if(hidemousecursor)SDL_ShowCursor(0);
      if(LIGHTS){
	      speed=5.0;
	      angspeed=0.01;}
      else
      {
	      speed=1.0;
	      angspeed=0.005;}

//Override Setup.h
LIGHTS=false;


//  Go to while(!quitit) to see what happens once data set up

// Go to Render Scene for graphics bit

 //   if_stream opens for input
 //   of_stream opens for output
 //   f_stream opens for both
 //
 // Camera1 position and stare at point have defaults
 // in C:\myIncludez\XFILESwin32\.
 // CamPos is in OpenGL y=0 plane, at x=0, z=-3000,
 // stare at origin. Also jprime=OpenGL j, iprime=OpenGL i
 // and kprime=OpenGL k.
 //
 // Be careful to adjust iprime jprime, jay, and kprime
 // if changed here (See Landscape and Camera.h)
 //
 // if you use SetPos here
    if(staked){
	    Camera1.SetPos(0.0,0.0,0.0);
	    Camera1.SetView(0.0,0.0,1000.0);
    }

    shift1=0.0;  //  x leftright
    shift2=0.0;   // in/out
    shift3=0.0;   // z up/down
    shift4=150.0;    //  x in/out
    shift5=150.0;    //  y left/right
    shift6=-100.0;    //  radial+-
    shift7=0.0;
    shift8=0.0;
    shift9=0.0;
    shift10=0.0;
    shift11=0.0;
    shift12=0.0;



    int pointsize=45; // for camera coordinates in perspective mode
 
    font1=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timeg.ttf",pointsize);
     if(font1==0 || !font1->isValid()){
        std::cout << "Font1 Failed" << std::endl;
        exit(1);
     }
     else{
        std::cout << "Font 1 is fine!" << std::endl;  }

     font2=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timegi.ttf",pointsize);
     if(font2==0 || !font2->isValid()){
        std::cout << "Font2 Failed" << std::endl;
        exit(1);
     }
     else{
        std::cout << "Font 2 is fine!" << std::endl;  }

     font3=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timegbd.ttf",pointsize);
     if(font3==0 || !font3->isValid()){
        std::cout << "Font3 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 3 is fine!" << std::endl;  }

     font4=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timegibd.ttf",pointsize);
     if(font4==0 || !font4->isValid()){
       std::cout << "Font4 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 4 is fine!" << std::endl;  }

     font5=new OGLFT::Filled("C:/myIncludez/Fonts/Fonts-Linux/slgrrg__.ttf",pointsize);
     if(font5==0 || !font5->isValid()){
       std::cout << "Font5 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 5 is fine!" << std::endl;  }

     font6=new OGLFT::Filled("C:/myIncludez/Fonts/texcm/cmex10.ttf",pointsize);
     if(font6==0 || !font6->isValid()){
       std::cout << "Font6 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 6 is fine!" << std::endl;  }

     font7=new OGLFT::Filled("C:/myIncludez/Fonts/texcm/cmmi10.ttf",pointsize);
     if(font7==0 || !font7->isValid()){
       std::cout << "Font7 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 7 is fine!" << std::endl;  }

     font8=new OGLFT::Filled("C:/myIncludez/Fonts/texcm/cmr10.ttf",pointsize);
     if(font8==0 || !font8->isValid()){
       std::cout << "Font8 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 8 is fine!" << std::endl;  }

     font9=new OGLFT::Filled("C:/myIncludez/Fonts/texcm/cmsy10.ttf",pointsize);
     if(font9==0 || !font9->isValid()){
       std::cout << "Font9 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 9 is fine!" << std::endl;  }
     
     //rasterised bitmap font
     pointsize=12;
     font10=new OGLFT::Monochrome("C:/myIncludez/Fonts/times/Timeg.ttf",pointsize);

     if(font10==0 || !font10->isValid()){
       std::cout << "Font10 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 10 is fine!" << std::endl;  }
    
     pointsize=6;  // for orthomode with scalefac 100.
     font11=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timeg.ttf",pointsize);
     if(font11==0 || !font11->isValid()){
       std::cout << "Font11 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 11 is fine!" << std::endl;  }

     pointsize=60;   //  other sizes for perspective mode and cam coord system
     font12=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timeg.ttf",pointsize);
     if(font12==0 || !font12->isValid()){
       std::cout << "Font12 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 12 is fine!" << std::endl;  }

     pointsize=75;
     font13=new OGLFT::Filled("C:/myIncludez/Fonts/times/Timeg.ttf",pointsize);
     if(font13==0 || !font13->isValid()){
       std::cout << "Font13 Failed" << std::endl;
        exit(1);
     }
     else{
       std::cout << "Font 13 is fine!" << std::endl;  }


     font1->setForegroundColor(0.0, 0.0, 0.0);
     font2->setForegroundColor(0.0, 0.0, 0.0);
     font3->setForegroundColor(0.0, 0.0, 0.0);
     font4->setForegroundColor(0.0, 0.0, 0.0);
     font5->setForegroundColor(0.0, 0.0, 0.0);
     font6->setForegroundColor(0.0, 0.0, 0.0);
     font7->setForegroundColor(0.0, 0.0, 0.0);
     font8->setForegroundColor(0.0, 0.0, 0.0);
     font9->setForegroundColor(0.0, 0.0, 0.0);
     font10->setForegroundColor(0.0, 0.0, 0.0);
     font11->setForegroundColor(0.0, 0.0, 0.0);
     font12->setForegroundColor(0.0, 0.0, 0.0);
     font13->setForegroundColor(0.0, 0.0, 0.0);


     glPixelStorei( GL_UNPACK_ALIGNMENT, 1);


    //read in data here
    //
    string filename;   //wierd C++ string and standard c string mash up
    ostringstream oss;   //don't really need the C++ string class here but...
    if(arg_count>=2){
    oss << *(arg_list+1);  //gets standard C string into C++ string object
    filename=oss.str();
    cout << filename << endl;
    }
    else
    {
	    filename="data.dat"; //default name
    }

    ifstream file_in;

    file_in.open(filename.c_str());  //c_str() is a member functio of the C++
                                     //string class, returns pointer to regular C string
    std::cout <<"My Arse!\n";
    cout << "file_in=" << filename << std::endl;
    if(!file_in){
	   std::cout << "Data file does not exist!\n";
            exit(0);	
    }
    file_in >> nplots;   //number of curves to be plotted

    std::cout << "we are plotting " << nplots << " data sets \n";   
    std::cout << "argc=" << arg_count << std::endl;

    ndata=(int*)calloc(nplots,sizeof(int));
    ntype=(int*)calloc(nplots,sizeof(int));
    ncol=(int*)calloc(nplots,sizeof(int));
    nstyle=(int*)calloc(nplots,sizeof(int));
    npoint=(int*)calloc(nplots,sizeof(int));

    //ndata -- number of points
    //ntype, 0 for lines, 1 for points
    //ncol  initial coloure number, 0=black
    //nstyle  select line style if lines
    //could adapt to symbols for ntype=0 later

    x=(double**)calloc(nplots,sizeof(double*));
    y=(double**)calloc(nplots,sizeof(double*));
    z=(double**)calloc(nplots,sizeof(double*));


    xmin=1e300; xmax=-1e300; ymin=1e300; ymax=-1e300; zmin=1e300; zmax=-1e300;
//adapt to read z later
    for(int i=0; i<nplots;i++){
            file_in  >> *(ndata+i) >> *(ntype+i) >> *(ncol+i) >> *(nstyle+i) >>*(npoint+i);
            if(*(ncol+i)>imats){
              std::cout << "colour code for curve " << i << " exceeds number of material colours " << imats <<endl;
               exit(1);
           }
           std::cout << "ndata=" << *(ndata+i) << "  ";
           std::cout << "ntype=" << *(ntype+i) << "  ";
           std::cout << "ncol=" << *(ncol+i) <<  "  ";
           std::cout << "nstyle=" << *(nstyle+i) << std::endl;
           std::cout << "point size=" << *(npoint+i) << std::endl;
	    *(x+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    *(y+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    *(z+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    for(int j=0; j < *(ndata+i); j++){
		    file_in >> *(*(x+i)+j) >> *(*(y+i)+j) >> *(*(z+i)+j);

		    if( *(*(x+i)+j)<xmin)xmin=*(*(x+i)+j);
		    if( *(*(y+i)+j)<ymin)ymin=*(*(y+i)+j);
		    if( *(*(z+i)+j)<zmin)zmin=*(*(z+i)+j);

		    if( *(*(x+i)+j)>xmax)xmax=*(*(x+i)+j);
		    if( *(*(y+i)+j)>ymax)ymax=*(*(y+i)+j);
		    if( *(*(z+i)+j)>zmax)zmax=*(*(z+i)+j);

	    }
    } 


    //now deal with xy axis labels for what x and y are and what are the units
    char xchar,ychar,zchar;
 //   int ixtext, ixunits, iytext, iyunits;
    int strlength;


    file_in >> ixtext >> ixunits;  //=1 if any text or any units
    if(ixtext==1 && ixunits==1)file_in >>   xtext >> xunits;
    if(ixtext==1 && ixunits==0)file_in >> xtext;
    file_in >> iytext >> iyunits;  //=1 if any text or any units
    if(iytext==1 && iyunits==1)file_in >>   ytext >> yunits;
    if(iytext==1 && iyunits==0)file_in >> ytext;
    file_in >> iztext >> izunits;  //=1 if any text or any units
    if(iztext==1 && izunits==1)file_in >>   ztext >> zunits;
    if(iztext==1 && izunits==0)file_in >> ztext;

    file_in >> LegendExists;


    if(LegendExists){

        LegendStrings=new string[nplots];
        for(int i=0; i<nplots;i++){
            file_in >> LegendStrings[i];
            for(int j=0; j<LegendStrings[i].length(); j++){
                xchar=LegendStrings[i][j];
                if(xchar=='@')LegendStrings[i].replace(j,1," ",1);
            }

        }
        cout << "Legends have been read\n";
      }


    //any intended spaces in the line of text in data.dat must be an ampersand
    //all ampersands are stripped out of the string.
    if(ixtext==1){
    strlength=xtext.length();
    for(int i=0; i<strlength; i++){
        xchar=xtext[i];
        if(xchar=='@')xtext.replace(i,1," ",1);
     }}
    if(ixunits==1){
    strlength=xunits.length();
    for(int i=0; i<strlength; i++){
        xchar=xunits[i];
        if(xchar=='@')xunits.replace(i,1," ",1);
     }}

    if(iytext==1){
    strlength=ytext.length();
    for(int i=0; i<strlength; i++){
        ychar=ytext[i];
        if(ychar=='@')ytext.replace(i,1," ",1);
     }}
    if(iyunits==1){
    strlength=yunits.length();
    for(int i=0; i<strlength; i++){
        ychar=yunits[i];
        if(ychar=='@')yunits.replace(i,1," ",1);
     }}

    if(iztext==1){
    strlength=ztext.length();
    for(int i=0; i<strlength; i++){
        zchar=ztext[i];
        if(zchar=='@')ztext.replace(i,1," ",1);
     }}
    if(izunits==1){
    strlength=zunits.length();
    for(int i=0; i<strlength; i++){
        zchar=zunits[i];
        if(zchar=='@')zunits.replace(i,1," ",1);
     }}


   std::cout << " x axis label in data.dat is " << xtext << std::endl;
   std::cout << " y axis label in data.dat is " << ytext << std::endl;
   std::cout << " z axis label in data.dat is " << ztext << std::endl;
   std::cout << " x axis unit in data.dat is " << xunits << std::endl;
   std::cout << " y axis unit in data.dat is " << yunits << std::endl;
   std::cout << " z axis unit in data.dat is " << zunits << std::endl;

   std::cout << "xmin and xmax are " <<  xmin << "  " <<   xmax << std::endl;
   std::cout << "ymin and ymax are " <<ymin << "  " << ymax << std::endl;
   std::cout << "zmin and zmax are " <<zmin << "  " << zmax << std::endl;
    xrange=xmax-xmin; yrange=ymax-ymin; zrange=zmax-zmin;
    if(fabs(xrange)<1e-42){
	   std::cout << "xrange too small, exiting " << std::endl;
	    exit(0);}
    if(fabs(yrange)<1e-42){
	   std::cout << "yrange too small, exiting " << std::endl;
	    exit(0);}
    if(fabs(zrange)<1e-42){
	   std::cout << "zrange too small, exiting " << std::endl;
	    exit(0);}

    xexp=floor(log10(xrange)); yexp=floor(log10(yrange));
    zexp=floor(log10(zrange));
    xfact=pow(10.0,xexp); yfact=pow(10.0,yexp); zfact=pow(10.0,zexp);
    xrange_scale=xrange/xfact; yrange_scale=yrange/yfact;
    zrange_scale=zrange/zfact;

    //all the following  have been initialised false
    if(xmin >0.0)xmin_zero=true; if(ymin>0)ymin_zero=true;
    if(zmin>0)zmin_zero=true;
    if(xmax >0.0)xmax_zero=true; if(ymax>0)ymax_zero=true;
    if(zmax>0)zmax_zero=true;
    
    if(xmax >0.0 && xmin > 0.0)xboth=true; if(xmax <0.0 && xmin < 0.0)xboth=true; 
    if(ymax >0.0 && ymin > 0.0)yboth=true; if(ymax <0.0 && ymin < 0.0)yboth=true;
    if(zmax >0.0 && zmin > 0.0)zboth=true; if(zmax <0.0 && zmin < 0.0)zboth=true;

   std::cout << "xrange and xfact are " << xrange << "  " << xfact << std::endl;
   std::cout << "yrange and yfact are " << yrange << "  " << yfact << std::endl;
   std::cout << "zrange and zfact are " << zrange << "  " << zfact << std::endl;

    if(xmin>0)xmin_zero=true;  if(ymin>0)ymin_zero=true; if(zmin>0)zmin_zero=true;  
    if(xmax>0)xmax_zero=true;  if(ymax>0)ymax_zero=true; if(zmax>0)zmax_zero=true;

    if(xmin_zero==true && xmax_zero==true)xboth=true;
    if(xmin_zero==false && xmax_zero==false)xboth=true;

    if(ymin_zero==true && ymax_zero==true)yboth=true;
    if(ymin_zero==false && ymax_zero==false)yboth=true;

    if(zmin_zero==true && zmax_zero==true)zboth=true;
    if(zmin_zero==false && zmax_zero==false)zboth=true;
    
    
    if(xmin>0)xminexp=floor(log10(xmin)); 
    if(xmin<0)xminexp=floor(log10(-xmin)); 

    if(ymin>0)yminexp=floor(log10(ymin));
    if(ymin<0)yminexp=floor(log10(-ymin));

    if(zmin>0)zminexp=floor(log10(zmin));
    if(zmin<0)zminexp=floor(log10(-zmin));

    xminfact=pow(10.0,xminexp); yminfact=pow(10.0,yminexp); zminfact=pow(10.0,zminexp);
    xmin_scale=xmin/xminfact;   ymin_scale=ymin/yminfact; zmin_scale=zmin/zminfact;

    numbers_xyz();

      ostringstream xmod;
      if(xtimesdiv){
       if(xexp<0){
        xmod << '*';  xmod << '1'; xmod << 'e'; xmod << '+';
        xmod << fabs(xexp);}
        else{
        xmod << '/';  xmod << '1'; xmod << 'e'; xmod << '+';
        xmod << fabs(xexp);}
        }
        else{xmod << ' ';}

        xtextmod=xmod.str();

      ostringstream ymod;
      if(ytimesdiv){
       if(yexp<0){
        ymod << '*';  ymod << '1'; ymod << 'e'; ymod << '+';
        ymod << fabs(yexp);}
        else{
        ymod << '/';  ymod << '1'; ymod << 'e'; ymod << '+';
        ymod << fabs(yexp);}
        }
        else{ymod << ' ';}

        ytextmod=ymod.str();

      ostringstream zmod;
      if(ztimesdiv){
       if(zexp<0){
        zmod << '*';  zmod << '1'; zmod << 'e'; zmod << '+';
        zmod << fabs(zexp);}
        else{
        zmod << '/';  zmod << '1'; zmod << 'e'; zmod << '+';
        zmod << fabs(zexp);}
        }
        else{zmod << ' ';}

        ztextmod=zmod.str();

      if(ixtext==1){
      ostringstream xst;
      if(xaddsubtract){
         xst << '(';
         xst << xtext << xtextmod;
         if(xsubtract<0){
             xst << '+';
             xst << -xsubtract;
             }
         if(xsubtract>0){
           xst << '-';
           xst << xsubtract;
           }
          xst << ')';
      }
      if(!xaddsubtract)xst << xtext << xtextmod;

      if(ixunits==1){
        xst << ' ';
        xst << xunits;
      }

      xaxistext=xst.str();
      }  //endif ixtext==1


     if(iytext==1){
      ostringstream yst;
      if(yaddsubtract){
         yst << '(';
         yst << ytext << ytextmod;
         if(ysubtract<0){
             yst << '+';
             yst << -ysubtract;
             }
         if(ysubtract>0){
           yst << '-';
           yst << ysubtract;
           }
          yst << ')';
      }
      if(!yaddsubtract)yst << ytext << ytextmod;

      if(iyunits==1){
        yst << ' ';
        yst << yunits;
      }

      yaxistext=yst.str();
      } // endif y axis text

     if(iztext==1){
      ostringstream zst;
      if(zaddsubtract){
         zst << '(';
         zst << ztext << ztextmod;
         if(zsubtract<0){
             zst << '+';
             zst << -zsubtract;
             }
         if(zsubtract>0){
           zst << '-';
           zst << zsubtract;
           }
          zst << ')';
      }
      if(!zaddsubtract)zst << ztext << ztextmod;

      zaxistext=zst.str();

      if(izunits==1){
        zst << ' ';
        zst << zunits;
      }

      } // endif z axis text

    

 while(!quitit){
        
       while(SDL_PollEvent(&event)){

          switch(event.type){
               case SDL_QUIT:
                 quitit=true;
                 break;
                 case SDL_MOUSEBUTTONDOWN:
		    if(!mousedown)
			    firstmousedown=true;
		    else
		            firstmousedown=false;
                    mousedown=true;
                 break;
                 case SDL_MOUSEBUTTONUP:
                    mousedown=false;   //mousedown remains true untill mouse up
                 break;

                 case SDL_MOUSEMOTION:
                  if(mousedown){
                         if(MouseOn)
				 if(tethered || staked)
					Camera1.MouseView();
					else
					Camera1.MouseLookAt();

		  }  //MouseView: change view direction
                  else{
                         if(MouseOn)
				 if(tethered || staked)
					Camera1.MouseLookAt();
					else
					Camera1.MouseView();
		  }  //MouseLookat: change point from where camera "looks at" scene
                 break;  


               case SDL_KEYDOWN:
                   whatkey=&event.key.keysym;
                   HandleKeyPress(whatkey);
                   break;
               case SDL_KEYUP:
                   whatkey=&event.key.keysym;
                   HandleKeyRelease(whatkey);
               default:
                 break;
                     } // end of case
                } //end of inner loop
       /************************************************************/
              CheckMove(Camera1);
		    if(a_Pressed){
			    speed=speed+0.1;
			    angspeed=angspeed+0.001;
			    if(speed > 60)speed=60;
			    if(angspeed  > 0.15)angspeed=0.15;
		    }
		    if(z_Pressed){
			    speed=speed-0.1;
			    angspeed=angspeed-0.001;
			    if(speed  < 0)speed=0;
			    if(angspeed  < 0)angspeed=0;
		    }

              RenderScene(Camera1); 
	      //(does picking in DrawLightPos etc)
            } //end of outer loop

}
void RenderScene(CCam & Camera1)
{
   glClearColor(RedM[0][0],GreenM[0][0],BlueM[0][0] ,AlphaM[0][0]);
   //background colour initialised

       glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
       glLoadIdentity();

       int ix,iz;

       //
       //camera  pos      view     up vector
       if(exwhyzed){
       gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.jay.GetX(),   Camera1.jay.GetY(),   Camera1.jay.GetZ());   
        }
       if(boom || aeroplane){
        gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.jprime.GetX(),   Camera1.jprime.GetY(),   Camera1.jprime.GetZ());   
        }


      glLineWidth(1.0);

      //LIGHTS ARE OFF  - KEEP CODE ANYWAY FOR NOW
      if(LIGHTS)
	      glEnable(GL_LIGHTING);
      else
	      glDisable(GL_LIGHTING);
     if(LIGHTS){

     glEnable(GL_BLEND);

     for(int il=0; il<ilights; il++){

     CosZen=cos(Zen[il]/convert);
     SinZen=sin(Zen[il]/convert);
     SinAz=sin(Az[il]/convert);
     CosAz=cos(Az[il]/convert);

     //check initial for Pesky openGL coordinates too
     gLightPosition[0]=Rho[il]*SinZen*CosAz;
     gLightPosition[2]=-Rho[il]*SinZen*SinAz;
     gLightPosition[1]=Rho[il]*CosZen;
     if(Rho[il] >  L_Inf)
	     gLightPosition[3]=0.0; // at infinity if =0 
     else   
             gLightPosition[3]=1.0;   // xyzw, pos= x/w,y/w,z/w

     float ambient[4]={RedL[il][0], GreenL[il][0], BlueL[il][0], AlphaL[il][0]}; 
     float diffuse[4]={RedL[il][1], GreenL[il][1], BlueL[il][1], AlphaL[il][1]}; 
     float specular[4]={RedL[il][2], GreenL[il][2], BlueL[il][2], AlphaL[il][2]}; 
     glLightfv(MYLIGHTS[il],GL_AMBIENT,ambient);
     glLightfv(MYLIGHTS[il],GL_DIFFUSE,diffuse);
     glLightfv(MYLIGHTS[il],GL_SPECULAR,specular);
     glLightfv(MYLIGHTS[il],GL_POSITION,gLightPosition);
      }
      }

      if(!helpscreen && drawback){
	      glDisable(GL_TEXTURE_2D); //Otherwise Colors get messed
	      glPointSize(2.0);
	      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	      glEnable(GL_POINT_SMOOTH);
	      if(Gouraud){
	      glShadeModel(GL_SMOOTH);
	      }
	      else
	      {
	      glShadeModel(GL_FLAT);
	      }
	      bool drawscene=true;     //by last call to glBindTexture

	      DrawScene(Camera1, drawscene);

      }// endif for !helpscreen
      /***********************************************************************/
      /*            End Plots    Begin helpscreen and  Boxes Here            */
      /***********************************************************************/

      glEnable(GL_TEXTURE_2D);
      if(helpscreen){

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
	      //low top high bottom
	      //Matrix is diagonal
	      //  2/(high-low), 2/(top-bottom), -2/(far-near)
	      //  call in OrthMode is to glOrtho with near=0, far=1
	      //  Args are  low, top, high, bottom

      OrthoMode(-1, 1, 1, -1);
      glColor3ub(255,255,255);
      glBindTexture(GL_TEXTURE_2D,gl_Texture[0]);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glBegin(GL_QUADS);
             // 0,0 is screen centre
             // -1,-1 is screen bottom low
	      glTexCoord2f(0.0,1.0);
	      glVertex2f(-1.0, 1.0); 
	      glTexCoord2f(0.0,0.0);
	      glVertex2f(-1.0, -1.0); // Bottom Left
	      glTexCoord2f(1.0,0.0);
	      glVertex2f(1.0, -1.0); // Bottom high
	      glTexCoord2f(1.0,1.0);
	      glVertex2f(1.0, 1.0); // Top high
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      PerspectiveMode();

       }  //endif for helpscreen

      //call draw functions twice
      // once to actually draw, and once in selection mode


              if(movetext){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawTextMove2(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawTextMove2(drawbox);
              }

             if(stylechange){
              glDisable(GL_DEPTH_TEST);
              glEnable(GL_BLEND);
                  bool drawbox;
	          drawbox=true;
	          DrawCurveCol(drawbox);  //draw
              glDisable(GL_BLEND);
              glEnable(GL_DEPTH_TEST);

	      drawbox=false;   //pickmatrix
	      DrawCurveCol(drawbox);
              }

             if(logicbox){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawLogicBox(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawLogicBox(drawbox);
              }

         //    legendplot=false;
             if(legendplot && LegendExists){

               bool drawbox;
               glDisable(GL_DEPTH_TEST);
               glDisable(GL_LIGHTING);
	          drawbox=true;
	          DrawLegend(drawbox);  //draw
               glEnable(GL_DEPTH_TEST);
               glEnable(GL_LIGHTING);

             //std::cout << post_Pressed << std::endl;
	       drawbox=false;   //pickmatrix
	       if(!post_Pressed)DrawLegend(drawbox);
               
               //if you make a call to gl2ps where
                //selection mode is being switched
                // you get no output!

                }
 
	      SDL_GL_SwapBuffers();
}

#include "C:\myIncludez\XFILESwin32\Init.cpp"

void DrawScene(CCam & Camera1, bool drawscene)
{
      int viewport[4];
      SDL_GetMouseState(&mousex, &mousey);

      double xvals[5],yvals[5],zvals[5];
      double ex, why, zed;

      if(drawscene){
      int matl=1;  //black

      if(LIGHTS){
        std::cout << "No LIGHTS allowed in PlotIt2\n";  exit(0);
        }
        else
	{
	glColor3ub((int)(255*RedM[matl][0]),(int)(255*GreenM[matl][0])
			,(int)(255*BlueM[matl][0]));
	}

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      }  //endif drawscene 


      double xlow,ylow,xhigh,yhigh; 
      //Camera is at  (0,0,3000) OpenGL coords
      xlow=-800.0; ylow=-800.0;  //keep 2d bounding box the same
      xhigh=800.0; yhigh=800.0; //note not  OpenGL xyz but normal xyz
      zlow=-800.0; zhigh=800.0;





          if(drawscene){
                   // X axis BOUNDING BOX
                   //numbers for x axis lower bounding box edge
                   glColor3ub(0,0,0);
                   double xt,yt,zt;
                   double longtick=70.0; double shorttick=longtick/2.0;

                   //xyz refer to normal xyz coordinates


                   D2Dvec Cam;
                   Cam.SetVec(Camera1.CamPos.GetX(),-Camera1.CamPos.GetZ()); //not OpenGL coords
                   D2Dvec Centre;

                   Centre.SetVec((xhigh+xlow)/2.0,(yhigh+ylow)/2.0);
                   D2Dvec Corner1, Corner2, Corner3, Corner4;
                   Corner1.SetVec(xlow,ylow); Corner2.SetVec(xhigh,ylow); // two near, left and right
                   Corner3.SetVec(xlow,yhigh); Corner4.SetVec(xhigh, yhigh);

                   D2Dvec vec0,vec1,vec2,vec3,vec4;

                   vec0=Cam-Centre; vec1=Corner1-Centre; vec2=Corner2-Centre;
                   vec3=Corner3-Centre; vec4=Corner4-Centre;

                   double Mod0,Mod1,Mod2,Mod3,Mod4;
                   Mod0=GetMod(vec0);
                   double ang0,ang1,ang2,ang3,ang4;
                   double dot1,dot2,dot3,dot4;

                   //probably dont need Mods or normalisation
                   if(Mod0>1.e-3){
                      dot1=vec0.Dot(vec1);dot2=vec0.Dot(vec2);dot3=vec0.Dot(vec3); dot4=vec0.Dot(vec4);
                   }

                    bool quad1=false,quad2=false,quad3=false,quad4=false;

                    if(dot1>0 && dot2>0)quad1=true; if(dot1>0 && dot3>0)quad2=true;
                    if(dot3>0 && dot4>0)quad3=true; if(dot4>0 && dot2>0)quad4=true; 

                    int iquad=0;
                    if(quad1)iquad++;if(quad2)iquad++;if(quad3)iquad++;if(quad4)iquad++;
                 //  std::cout << "quads are " << quad1 << quad2 << quad3 << quad4 << std::endl;

                    if(iquad!=1){
                      std::cout << " need to alter quadrant testing in DrawScene, iquad=" << iquad << std::endl;
                       exit(0);
                    }
                    D2Dvec Cam2Corn1,Cam2Corn2,Cam2Corn3,Cam2Corn4;

                    Cam2Corn1=vec1-vec0;Cam2Corn2=vec2-vec0;
                    Cam2Corn3=vec3-vec0;Cam2Corn4=vec4-vec0;

                    Mod1=GetMod(Cam2Corn1); Mod2=GetMod(Cam2Corn2);
                    Mod3=GetMod(Cam2Corn3); Mod2=GetMod(Cam2Corn4);

                    Normalise(Cam2Corn1); Normalise(Cam2Corn2);
                    Normalise(Cam2Corn3); Normalise(Cam2Corn4);
                    Normalise(vec0);   //dots will now be cosines

                    dot1=-vec0.Dot(Cam2Corn1); dot2=-vec0.Dot(Cam2Corn2);
                    dot3=-vec0.Dot(Cam2Corn3); dot4=-vec0.Dot(Cam2Corn4);

                    bool all, silly, tom, cats;


                    double cosine, sine, angle;
                    cosine=-vec0.GetY();
                    sine=vec0.GetX();
                    angle=asin(sine)*180.0/pi;
              //     std::cout << dot5 << "  " << sine5 << std::endl;
                    all=false; silly=false; tom=false; cats=false;
                    if(sine>=0.0){ if(cosine >=0.0){all=true;} else {silly=true;} };
                    if(sine<0.0){ if(cosine < 0.0){tom=true;} else {cats=true;} };

                    //all in quadrant 1, do nothing
                    if(silly)angle=180.0-angle;  //quadrant 2 angle decreasing from 90 to 0
                    if(tom)angle=180.0-angle;  //quadrant3   angle increasing 0 to -90 
                    if(cats)angle=360.0+angle;   //quadrant 4 angle1 negative 0 to -90
 
                    bool printz1=false,printz2=false,printz3=false,printz4=false;

             //      std::cout <<pi << std::endl;
                    
                    if(quad1){
                       if(dot1<dot3){printz1=true; } 
                             else {  printz3=true; }
                       if(dot2<dot4){printz2=true; }
                               else{ printz4=true; }}
                   if(quad2){


                       if(dot3<dot4){printz3=true; }
                              else{  printz4=true; }
                       if(dot1<dot2){printz1=true; }
                               else{ printz2=true; }}
                   if(quad3){
                       if(dot2<dot4){printz2=true; }
                              else{  printz4=true; }
                       if(dot1<dot3){printz1=true; }
                               else{ printz3=true; }}
                  if(quad4){
                       if(dot1<dot2){printz1=true; }
                              else{  printz2=true; }
                       if(dot3<dot4){printz3=true; }
                               else{ printz4=true; }}

//                  Near x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   glRotatef(-90.0,1.0,0.0,0.0);
                   // in/out now openGL -+y,  up/down now openGL -+z
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow);
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1,-yt-shift4,-zt);  //initial translation with shift

                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
		      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();
//                 Far x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(180.0,0.0,0.0,1.0);
                   //left/right now openGL -+xm in/out now openGL +iy,up/down now openGL -+z

                   xt=xhigh-(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow);
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1,-yt-shift4,-zt);  //initial translation with shift

                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
		      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(-xt,yt,zt);
                    }
                   glPopMatrix();

                   //major tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb; i++){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,zlow,ylow-longtick); glVertex3f(0.0,zlow,ylow);
                          glVertex3f(0.0,zlow,yhigh); glVertex3f(0.0,zlow,yhigh+longtick);
                      glEnd();
                      glTranslated(xt,yt,zt);
                    }
                    glPopMatrix();

                   //minor tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start2-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep2/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb2; i++){
                      if(xnumbers2[i]+xsubtract>=xmin && xnumbers2[i]+xsubtract<=xmax){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,zlow,ylow-shorttick); glVertex3f(0.0,zlow,ylow);
                          glVertex3f(0.0,zlow,yhigh+shorttick); glVertex3f(0.0,zlow,yhigh);
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();


                   //Y BOUNDING BOX NUMBERS AND TICKMARKS

                   //numbers for y axis left and right bounding box edge

                   yt=ylow-(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(-90.0,0.0,0.0,1.0);
                   // openGL in/out=-+x, left/right=+-y, up/down =+-z
                   glTranslated(-yt-shift5,xlow-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(-yt,xt,zt);
                    }
                   glPopMatrix();

                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(90.0,0.0,0.0,1.0);
                   // openGL in/out=+-x, left/right=-+y, up/down =+-z
                   glTranslated(yt-shift5,-xhigh-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(yt,xt,zt);
                    }
                   glPopMatrix();

 

                   //major tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb; i++){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,zlow,0.0); glVertex3f(xlow-longtick,zlow,0.0);
                        glVertex3f(xhigh,zlow,0.0); glVertex3f(xhigh+longtick,zlow,0.0);
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();

                   //minor tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start2-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep2/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb2; i++){
                      if(ynumbers2[i]+ysubtract>=ymin && ynumbers2[i]+ysubtract<=ymax){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,zlow,0.0); glVertex3f(xlow-shorttick,zlow,0.0);
                        glVertex3f(xhigh,zlow,0.0); glVertex3f(xhigh+shorttick,zlow,0.0);
                      glEnd();
                      }
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();

                   //Z BOUNDING BOX NUMBERS AND TICKMARKS
                   //numbers for 4 vertical z axes

                   double xtrans,ytrans;

                   if(printz3){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xlow; ytrans=ylow;
                   if(quad1 || quad2){
                     xtrans=xtrans-(180-shift6)*cosine;  ytrans=ytrans+(180.0+shift6)*sine;}
                   else{
                     xtrans=xtrans+(120+shift6)*cosine;  ytrans=ytrans-(120.0+shift6)*sine;}

                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);

                   glTranslated(xtrans*cosine-ytrans*sine
                                ,zt-shift3,ytrans*cosine+xtrans*sine);
                   //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   }  //corner3

                   if(printz4){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xhigh;   ytrans=ylow;
                   if(quad1 || quad4 ){
                     xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100.0+shift6)*sine;}
                   else{
                     xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180.0+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine
                                ,zt-shift3,ytrans*cosine+xtrans*sine);  
                   //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   } //corner4

                   if(printz1){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xlow;  ytrans=yhigh;
                  if(quad1 || quad4){
                     xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180.0+shift6)*sine;}
                   else{
                     xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100.0+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine
                                 ,zt-shift3,ytrans*cosine+xtrans*sine);
                    //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   }  //corner1

 
                  if(printz2){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xhigh; ytrans=yhigh;
                   if(quad1 || quad2){
                        xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100.+shift6)*sine;}
                      else{
                        xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180.+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine,
                                zt-shift3,ytrans*cosine+xtrans*sine); 
                    //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                  }  //corner2

                   //major tick marks for  4 z axis axes
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,ylow); //initial translation step
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb; i++){
                      glBegin(GL_LINES);
                        if(quad1 || quad2){
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-longtick*cosine,0.0,longtick*sine);
                        } else {
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+longtick*cosine,0.0,-longtick*sine);}
                       if(quad1 || quad4){
                         glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+longtick*cosine,0.0,-longtick*sine);}
                       else{
                         glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-longtick*cosine,0.0,+longtick*sine);}
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }

                   glPopMatrix();
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yhigh); //initial translation step
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb; i++){
                      glBegin(GL_LINES);
                         if(quad1 || quad4){
                         glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-longtick*cosine,0.0,longtick*sine);}
                         else{
                         glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+longtick*cosine,0.0,-longtick*sine);}
                       if(quad1 || quad2){
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+longtick*cosine,0.0,-longtick*sine);}
                          else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-longtick*cosine,0.0,longtick*sine);}
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   //minor z tickmarks
                   zt=zlow+(z_start2-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,ylow); //initial translation step
                   zt=zstep2/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb2; i++){
                      if(znumbers2[i]+zsubtract>=zmin && znumbers2[i]+zsubtract<=zmax){
                      glBegin(GL_LINES);
                        if(quad1 || quad2){
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-shorttick*cosine,0.0,shorttick*sine);}
                        else{
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+shorttick*cosine,0.0,-shorttick*sine);}
                        if(quad1 || quad4){
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+shorttick*cosine,0.0,-shorttick*sine);}
                        else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-shorttick*cosine,0.0,+shorttick*sine);}
                      glEnd();
                      }
                      glTranslated(xt,zt,yt);
                    }
                    glPopMatrix();
                   zt=zlow+(z_start2-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yhigh); //initial translation step
                   zt=zstep2/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb2; i++){
                      if(znumbers2[i]+zsubtract>=zmin && znumbers2[i]+zsubtract<=zmax){
                      glBegin(GL_LINES);
                         if(quad1 || quad4){
                           glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-shorttick*cosine,0.0,shorttick*sine);}
                         else{
                           glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+shorttick*cosine,0.0,-shorttick*sine);}

                        if(quad1 || quad2){
                           glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+shorttick*cosine,0.0,-shorttick*sine);}
                        else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-shorttick*cosine,0.0,+shorttick*sine);}
                      glEnd();

                      }
                      glTranslated(xt,zt,yt);
                    }
                    glPopMatrix();


      //3-D bounding box
      glBegin(GL_LINES);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xhigh,zlow,ylow);
        glVertex3f(xlow,zlow,yhigh); glVertex3f(xhigh,zlow,yhigh);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xlow,zlow,yhigh);
        glVertex3f(xhigh,zlow,ylow); glVertex3f(xhigh,zlow,yhigh);

        glVertex3f(xlow,zhigh,ylow); glVertex3f(xhigh,zhigh,ylow);
        glVertex3f(xlow,zhigh,yhigh); glVertex3f(xhigh,zhigh,yhigh);
        glVertex3f(xlow,zhigh,ylow); glVertex3f(xlow,zhigh,yhigh);
        glVertex3f(xhigh,zhigh,ylow); glVertex3f(xhigh,zhigh,yhigh);

        glVertex3f(xlow,zlow,ylow); glVertex3f(xlow,zhigh,ylow);
        glVertex3f(xlow,zlow,yhigh); glVertex3f(xlow,zhigh,yhigh);
        glVertex3f(xhigh,zlow,ylow); glVertex3f(xhigh,zhigh,ylow);
        glVertex3f(xhigh,zlow,yhigh); glVertex3f(xhigh,zhigh,yhigh);
      glEnd();





      if(ixtext==1){

      float xt=(float)xaxistext.length();
      xt=xt*40/2.0;  //pointsize 45

      glPushMatrix();
      glRotatef(-90.0,1.0,0.0,0.0);
         //Opengl in out now +-y, up/down=+-z
         glTranslated(-xt-shift7, ylow-250.-shift8 , zlow);
         font12->draw(xaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
      glRotatef(-90.0,1.0,0.0,0.0);
      glRotatef(180.0,0.0,0.0,1.0);
         //Opengl in out now -+y, up/down=+-z, leftright=-+x
         glTranslated(-xt-shift7, ylow-250.-shift8 , zlow);
         font12->draw(xaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any x axis text

     if(iytext==1){

      float yt=(float)yaxistext.length();
      yt=yt*40./2.0;


      glPushMatrix();
         glRotatef(-90.0,1.0,0.0,0.0);  //rotate anticlock
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in out now -+x, openGL left/right now -+y  i[down +0z
         glTranslated(-yt-shift10,-xhigh-220.0+shift9,zlow);
         font12->draw(yaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
         glRotatef(-90.0,1.0,0.0,0.0);  //rotate clock
         glRotatef(-90.0,0.0,0.0,1.0);
         //openGL in out now +-x, openGL left/right now +-y up/down +=z
         glTranslated(-yt-shift10, xlow-240.0+shift9,zlow);//remember xlow is negative, and that after rotation y is towards old -x
         font12->draw(yaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any y axis text


     if(iztext==1){

      float zt=zaxistext.length();
      zt=zt*40./2.0;

      if(printz3){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xlow; ytrans=zlow;
         if(quad3 || quad4){
            xtrans=xtrans-(300.0-shift12)*cosine;  ytrans=ytrans-(300.0-shift12)*sine;}
            else{
            xtrans=xtrans+(250.0-shift12)*cosine;  ytrans=ytrans+(250.0-shift12)*sine;}
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
       }    //corner3

      if(printz4){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xhigh; ytrans=zlow;
         if( quad1 || quad4){
             xtrans=xtrans-(250.0-shift12)*cosine, ytrans=ytrans-(250.-shift12)*sine; }
            else{
             xtrans=xtrans+(250.0-shift12)*cosine, ytrans=ytrans+(250.-shift12)*sine; }
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
        font12->draw(zaxistext.c_str());
       glPopMatrix();
       }  //corner 4


      if(printz1){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xlow; ytrans=zhigh;
         if(quad1 || quad4){
            xtrans=xtrans+(250.0-shift12)*cosine; ytrans=ytrans+(250.-shift12)*sine;}
          else{
            xtrans=xtrans-(250.0-shift12)*cosine; ytrans=ytrans-(250.0-shift12)*sine;}
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
     } //corner1


      if(printz2){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xhigh;  ytrans=zhigh;
         if(quad1 || quad2){
                 xtrans=xtrans-(250.0-shift12)*cosine; ytrans=ytrans-(250.-shift12)*sine;}
                 else{
                 xtrans=xtrans+(250.0-shift12)*cosine; ytrans=ytrans+(250.-shift12)*sine;}

         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
      } // corner2



      }   //endif for is there any z axis text



	  } //end draw scene


  //Now plot the bloody graph!

      if(drawlines && drawscene){

      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

      for(int i=0; i<nplots; i++){

 	     if(LIGHTS){
              //aint gonna happen
              std::cout << "LIGHTS MUST BE SET TO FALSE FOR PLOTIT" << std::endl;
               exit(0);
	     }
	     else
	     {
	glColor3ub((int)(255*RedPC1[*(ncol+i)][1]),
                   (int)(255*GreenPC1[*(ncol+i)][1]),(int)(255*BluePC1[*(ncol+i)][1]));
	}  //endif for LIGHTS

         glLineWidth((float)*(npoint+i));

        if(*(ntype+i)==0){ //plot lines
//  the 1 is a stretch factor (dont strectch)
          if(*(nstyle+i)==0)glLineStipple(1,LINE0);
          if(*(nstyle+i)==1)glLineStipple(1,LINE1);
          if(*(nstyle+i)==2)glLineStipple(1,LINE2);
          if(*(nstyle+i)==3)glLineStipple(1,LINE3);
          if(*(nstyle+i)==4)glLineStipple(1,LINE4);

          glEnable(GL_LINE_STIPPLE);

          glBegin(GL_LINES);
          for(int j=0; j< *(ndata+i)-1; j++){
              double x1,y1,x2,y2,z1,z2;
              
              x1=*(*(x+i)+j); y1=*(*(y+i)+j); z1=*(*(z+i)+j);
              x2=*(*(x+i)+j+1); y2=*(*(y+i)+j+1); z2=*(*(z+i)+j+1);

              
 //cout << i << " " << j <<  "  " << x1  << "  " << y1 
  //        << "  " << x2 << "  " << y2 << "  "  << z1 << "  " << z2 << std::endl;

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=ylow+(z1-zmin)/zrange*(zhigh-zlow);

              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              z2=zlow+(z2-zmin)/zrange*(zhigh-zlow);

             
              glVertex3d(x1,z1,-y1);
              glVertex3d(x2,z2,-y2);
          }
          glEnd();
          glDisable(GL_LINE_STIPPLE);
      }
       if(*(ntype+i)==1){ //plot points

         glPointSize((float)*(npoint+i));


          glBegin(GL_POINTS);
          for(int j=0; j< *(ndata+i); j++){
              double x1,y1,z1;
              
              x1=*(*(x+i)+j); y1=*(*(y+i)+j); z1=*(*(z+i)+j);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=ylow+(z1-zmin)/zrange*(zhigh-zlow);
              glVertex3d(x1,z1,-y1);
          }
          glEnd();
      }

       } // end nplots loop

  //    std::cout << " drawn plots\n";


    } // endif lines and drawscene

}

