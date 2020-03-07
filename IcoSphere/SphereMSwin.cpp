//-------------------------------------------------------------------------------
// Copyright 2009 Christopher Godsalve.
// All Rights Reserved.
//
// Permission to use, copy, modify and distribute this software (if not modified) and its
// documentation for educational, research and non-profit purposes, without fee,
// and without a written agreement is hereby granted, provided that the above
// copyright notice and the following three paragraphs appear in all copies.
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

#include "SphereMSwin.h"

#include "C:\myIncludez\XFILESwin32\TrueType.h"
#include "C:\myIncludez\XFILESwin32\SetUp.h"
#include "C:\myIncludez\XFILESwin32\Controls.h"
#include "C:\myIncludez\XFILESwin32\DrawTextMove.h"
#include "C:\myIncludez\XFILESwin32\DrawCurveCol.h"
#include "C:\myIncludez\XFILESwin32\DrawLegend.h"
#include "C:\myIncludez\XFILESwin32\DrawLogicBox.h"

//  We shall be using OpenGL's Quadric function
//  GLU_FILL means that it won't be wire frame
//  GLU_LINE means it will be wire frame
//  int g_RenderMode=GLU_FILL; // this is for quadrics only
//

int g_RenderMode=GLU_LINE;


int myplotz;
int nv,npoly;

int ntri, ntrinew;
int istart,istop, isplit, iquad;

bool   xallpos,xallneg;
bool   yallpos,yallneg;
bool   zallpos,zallneg;



/*  FONTS IN
HAVE TRUETYPE FONTS IN
1.  /usr/share/tuxpaint/fonts
2,  /usr/lib/SunJava2-1.4.2/jre/lib/fonts
3.  /usr/X11R6/lib/X11/fonts/truetype
4   plus a few others from games and povray
*/

int width=1024;
int height=768;


#include "C:\myIncludez\XFILESwin32\Init.cpp"

void EventLoop()
{
 
 LIGHTS=false;
 CCam Camera1;

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


 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2;
 SDL_keysym  *whatkey;
 bool mousedown=false;

int n_nodes;
bool old1,old2,old3;
bool case0, case1, case2, case3, case4, case5, case6, case7;

//  Go to while(!quitit) to see what happens once data set up

// Go to Render Scene for graphics bit

    bool exitnow=false;

    double X,Y,Z;
    X=-1e32;Y=-1e-32;Z=-1e32;
    xmax=X; ymax=Y, zmax=Z;
    xmin=-X; ymin=-Y, zmin=-Z;

    double xunit,yunit,zunit;
    xunit=1.0;yunit=1.0;zunit=1.0;

    fstream infile1,infile2;

    infile1.open("Node.dat", ios::in);
    infile2.open("Tri.dat", ios::in);

    double lati, longi;
    double x,y,z;
    int Ttotal, Ntotal, ndiv;
    ndiv=4;
    Ttotal=20*(int)(pow(4,ndiv+1)-1);
    Ntotal=(int)(pow(2,2*ndiv));
    Ntotal=10*Ntotal+2;


    Triangles=(Triangle*)calloc(Ttotal, sizeof(Triangle));
    NodeV=(D3Dvec*)calloc(Ntotal, sizeof(D3Dvec));

    //INITIALISE USING CONSTRUCTOR
    for(int i=0; i< Ttotal; i++){
            Triangles[i]=Triangle();  }
    for(int i=0; i< Ntotal; i++){
            NodeV[i]=D3Dvec();  }  

 // position vectors for basic icosahedron
    for(int i=0; i< 12; i++){
	    infile1 >> lati >> longi;
	    x=cos(lati)*cos(longi);
	    y=cos(lati)*sin(longi);
	    z=sin(lati);
	    NodeV[i].SetVec(x,y,z);
    }


    int in,jn,kn;
    char quad, otherquad;

    for(int i=0; i< 20; i++){  //20 facts of Icosahedron
      infile2 >> in >> jn >> kn;
      in=in-1; jn=jn-1; kn=kn-1;
      Triangles[i].SetTri(in, jn, kn);
      quad=i;
      Triangles[i].SetQuad(quad);
    }

    //Neighbours for each edge of each triangle
    //Triangle edges in triangle are the edge number
    //of the edge in the NEIGHBOUR
    //
    //For instance Edge 1 of first triangle
    //is edge 1 of triangle 5, but in opposite direction
    
    // *********************************************
    in=6-1;jn=2-1;kn=5-1;
    Triangles[0].SetNeighb(in, jn, kn);
    
    in=7-1;jn=3-1;kn=1-1;
    Triangles[1].SetNeighb(in, jn, kn);
    
    in=8-1;jn=4-1;kn=2-1;
    Triangles[2].SetNeighb(in, jn, kn);
    
    in=9-1;jn=5-1;kn=3-1;
    Triangles[3].SetNeighb(in, jn, kn);
    
    in=10-1;jn=1-1;kn=4-1;
    Triangles[4].SetNeighb(in, jn, kn);
    
    // *********************************************
    in=1-1;jn=11-1;kn=12-1;
    Triangles[5].SetNeighb(in, jn, kn);
    
    in=2-1;jn=12-1;kn=13-1;
    Triangles[6].SetNeighb(in, jn, kn);
    
    in=3-1;jn=13-1;kn=14-1;
    Triangles[7].SetNeighb(in, jn, kn);
    
    in=4-1;jn=14-1;kn=15-1;
    Triangles[8].SetNeighb(in, jn, kn);
    
    in=5-1;jn=15-1;kn=11-1;
    Triangles[9].SetNeighb(in, jn, kn);
    
    // *********************************************
    in=18-1;jn=6-1;kn=10-1;
    Triangles[10].SetNeighb(in, jn, kn);
    
    in=19-1;jn=7-1;kn=6-1;
    Triangles[11].SetNeighb(in, jn, kn);
    
    in=20-1;jn=8-1;kn=7-1;
    Triangles[12].SetNeighb(in, jn, kn);
    
    in=16-1;jn=9-1;kn=8-1;
    Triangles[13].SetNeighb(in, jn, kn);
    
    in=17-1;jn=10-1;kn=9-1;
    Triangles[14].SetNeighb(in, jn, kn);
    // *********************************************
    
    in=14-1;jn=20-1;kn=17-1;
    Triangles[15].SetNeighb(in, jn, kn);
    
    in=15-1;jn=16-1;kn=18-1;
    Triangles[16].SetNeighb(in, jn, kn);
    
    in=11-1;jn=17-1;kn=19-1;
    Triangles[17].SetNeighb(in, jn, kn);
    
    in=12-1;jn=18-1;kn=20-1;
    Triangles[18].SetNeighb(in, jn, kn);
    
    in=13-1;jn=19-1;kn=16-1;
    Triangles[19].SetNeighb(in, jn, kn);
    // *********************************************

    ntri=20; n_nodes=12; ntrinew=0;   //we have 20 triangles and 6 nodes for Icosahedron


    ofstream file_out;
    file_out.open("Sphere0.dat", ios::out);  //can have ios::app for appending
    file_out << n_nodes <<" "<< ntri <<   "  number of nodes, number of triangles"  <<  endl;

    //output triangle number, 3 node numbers, and quadrant id
    for(int i=0; i<ntri; i++){
       file_out  << i <<" "<<   Triangles[i].Get1() <<" "<< Triangles[i].Get2() 
                <<" "<<  Triangles[i].Get3() 
	       	<<" "<<  Triangles[i].GetQuad() <<" "<<  endl;
    }
    //output triangle neighbours on edges 1 2 and 3.
    for(int i=0; i<ntri; i++){
       file_out << Triangles[i].GetN1()-istop <<" "<<  Triangles[i].GetN2()-istop 
                <<" "<<  Triangles[i].GetN3()-istop  << endl;
    }
    //output x,y,z coordinates of nodes.

    for(int  i=0; i< n_nodes;  i++){
      file_out <<  i <<" "<<   NodeV[i].GetX()  <<" "<< 
	      NodeV[i].GetY() <<" "<<  NodeV[i].GetZ() << endl;
    }

    file_out.close();

    n_nodes=n_nodes-1;  // 12 nodes 0-11



    int *pSplit0,*pSplit1,*pSplit2,*pSplit3;
    bool split_this;

    int in1,in2,in3;
    int is1,is2;
    int nn1,nn2,nn3;

    int inode1,inode2,inode3;
    int new0,new1,new2,new3;  //serves for new node or triangle numbers
    int new1N,new2N,new3N;  

    istart=0;
    istop=20;

      // split all triangles at this level if the neighbours 
      // are on the same level. Then every split triangle
      // has an unsplit neighbour and vice versa
      //
	    //recursive subdivision
	    //
	    char* filename[5];
	    for(int idiv=0; idiv < ndiv; idiv++){
		 ntrinew=0;
	    for(int itri=istart;itri<istop;itri++){
		    if( Triangles[itri].GetN() ){
		    in1=Triangles[itri].GetN1();
		    in2=Triangles[itri].GetN2();
		    in3=Triangles[itri].GetN3();
		    }
		    else { cout <<" No Neighbours " << endl;  exit(0);  }

		    pSplit0=Triangles[itri].GetS();
		    pSplit1=Triangles[in1].GetS();
		    pSplit2=Triangles[in2].GetS();
		    pSplit3=Triangles[in3].GetS();

                    if(!pSplit0){split_this=true;} else {split_this=false;}

		    if(split_this){

		    // Split This Triangle into 4 with three new nodes

		    bool NodeExists1=false;
		    bool NodeExists2=false;
		    bool NodeExists3=false;

		    if(pSplit3)NodeExists1=true;
		    if(pSplit2)NodeExists2=true;
		    if(pSplit1)NodeExists3=true;

		    int oldnode1=-1,oldnode2=-1,oldnode3=-1;

                    old1=false; old2=false; old3=false;
		    // nodes of internal triangle to current replacement
		    // in current leve;
		    if(NodeExists1){
			    // split exists on edge 3 of current T
			   quad=Triangles[itri].GetQuad();
			   otherquad=Triangles[in3].GetQuad();

			   iquad=(int)quad;
			   if(iquad > 4 &&  iquad <15)otherquad=quad;

			    
                           if(quad != otherquad){
			    oldnode1=
			    Triangles[Triangles[in3].GetS2()].Get3();}
			   else {
			    oldnode1=
			    Triangles[Triangles[in3].GetS3()].Get3();}
			    old1=true;
		    }
		    if(NodeExists2){
			    // split exists on edge 2 of current T
			    //
			    quad=Triangles[itri].GetQuad();
			    otherquad=Triangles[in2].GetQuad();

			   iquad=(int)quad;
			   if(iquad > 4 &&  iquad <15)otherquad=quad;

			    if(quad != otherquad){
			    oldnode2=
			    Triangles[Triangles[in2].GetS3()].Get3(); }
			    else  {
			    oldnode2=
			    Triangles[Triangles[in2].GetS2()].Get3(); }

			    old2=true;
		    }
		    if(NodeExists3){
			    //  edge 1 always matches edge1
			    oldnode3=
			    Triangles[Triangles[in1].GetS2()].Get2();
			    old3=true;
		    }

		    if(oldnode1 < 0){
		       n_nodes++;
		       NodeV[n_nodes].SetX( 
				NodeV[ Triangles[itri].Get2() ].GetX()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetX()
				-NodeV[ Triangles[itri].Get2() ].GetX()
				)/2.0
				);

		       NodeV[n_nodes].SetY( 
				NodeV[ Triangles[itri].Get2() ].GetY()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetY()
				-NodeV[ Triangles[itri].Get2() ].GetY()
				)/2.0
				);
		       NodeV[n_nodes].SetZ( 
				NodeV[ Triangles[itri].Get2() ].GetZ()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetZ()
				-NodeV[ Triangles[itri].Get2() ].GetZ()
				)/2.0
				);
		    }


		    if(oldnode2 < 0){
		       n_nodes++;
		       NodeV[n_nodes].SetX( 
				NodeV[ Triangles[itri].Get1() ].GetX()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetX()
				-NodeV[ Triangles[itri].Get1() ].GetX()
				)/2.0
				);
		       NodeV[n_nodes].SetY( 
				NodeV[ Triangles[itri].Get1() ].GetY()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetY()
				-NodeV[ Triangles[itri].Get1() ].GetY()
				)/2.0
				);
		       NodeV[n_nodes].SetZ( 
				NodeV[ Triangles[itri].Get1() ].GetZ()
			       +(
				NodeV[ Triangles[itri].Get3() ].GetZ()
				-NodeV[ Triangles[itri].Get1() ].GetZ()
				)/2.0
				);
		    }
                    if(oldnode3 < 0){
		       n_nodes++;
		       NodeV[n_nodes].SetX( 
				NodeV[ Triangles[itri].Get1() ].GetX()
			       +(
				NodeV[ Triangles[itri].Get2() ].GetX()
				-NodeV[ Triangles[itri].Get1() ].GetX()
				)/2.0
				);
		       NodeV[n_nodes].SetY( 
				NodeV[ Triangles[itri].Get1() ].GetY()
			       +(
				NodeV[ Triangles[itri].Get2() ].GetY()
				-NodeV[ Triangles[itri].Get1() ].GetY()
				)/2.0
				);
		       NodeV[n_nodes].SetZ( 
				NodeV[ Triangles[itri].Get1() ].GetZ()
			       +(
				NodeV[ Triangles[itri].Get2() ].GetZ()
				-NodeV[ Triangles[itri].Get1() ].GetZ()
				)/2.0
				);
	    }

		     isplit=istop+ntrinew;

		     new0=isplit;
		     new1=isplit+1;
		     new2=isplit+2;
		     new3=isplit+3;
	    
		     Triangles[itri].SetSplit( new0, new1, new2, new3);


		       if(old1)inode1=oldnode1;
		       if(old2)inode2=oldnode2;
		       if(old3)inode3=oldnode3;
                       case0=false;
                       case1=false;
                       case2=false;
                       case3=false;
                       case4=false;
                       case5=false;
                       case6=false;
                       case7=false;

		       if( !old1 && !old2 && !old3)case0=true; 
		       if( old1 && old2 && old3)case7=true;

		       if(case0 ){
			       inode1=n_nodes-2;
			       inode2=n_nodes-1;
			       inode3=n_nodes-0;
		       }
		       if(case7){
			       inode1=oldnode1;
			       inode2=oldnode2;
			       inode3=oldnode3;
		       }


		       if(!case0 &&  !case7)
		       {
		       if(old1){
			       if(old2 || old3){
			       if(old2){   
				  case4=true;   // nodes 1 and 2 exist 
				  inode1=oldnode1;
				  inode2=oldnode2;
				  inode3=n_nodes-0;
			          }
				  else
				  {
			           case6=true;    // nodes 1 and 3 exist
			           inode1=oldnode1;
			           inode2=n_nodes-0;
			           inode3=oldnode3;
				  }
			       }
				      else 
				      {
					      case1=true;  //only node 1 exists
				              inode1=oldnode1;
				              inode2=n_nodes-1;
				              inode3=n_nodes-0;  
				      }
			         }//endif old1
		       if(old2){
			       if(!old1){   // case 4 done above
			       if(old3){   
				  case5=true;   //nodes 2 and 3 exist
				  inode1=n_nodes-0;
				  inode2=oldnode2;
				  inode3=oldnode3;
			          }
				  else
				  {
				  case2=true;  //only node 2 exists
				  inode1=n_nodes-1;
				  inode2=oldnode2;
				  inode3=n_nodes-0;
				  }
			       }
		       } //endif old2
		       if(old3){
			       if( !old1 && !old2){
			       //  1 and 3 and 2 and 3 done already
			          case3=true; 
				  inode1=n_nodes-1;
				  inode2=n_nodes-0;
				  inode3=oldnode3;
			       }
		       }
		       }  //endif (NOT case 0) AND (NOT case 7)

		       quad=Triangles[itri].GetQuad();
		       Triangles[new0].SetTri(inode1, inode2, inode3);  //Centre T
		       Triangles[new0].SetQuad(quad);

		      Triangles[new1].SetTri(Triangles[itri].Get1(), inode3, inode2); 
		      Triangles[new1].SetQuad(quad);
		      Triangles[new2].SetTri(inode3, Triangles[itri].Get2(), inode1);
		      Triangles[new2].SetQuad(quad);
		      Triangles[new3].SetTri(inode2, inode1, Triangles[itri].Get3());
		      Triangles[new3].SetQuad(quad);

		 
                      //Set Neighbours for centre Triangle;
		       new1N=new3;
		       new2N=new2;
		       new3N=new1;
		       Triangles[new0].SetNeighb(new1N,new2N,new3N);
		       Triangles[new1].SetN3(new0);
		       Triangles[new2].SetN2(new0);
		       Triangles[new3].SetN1(new0);

                       if(pSplit1){
			      // have split neighbours on edge 1
			      // These are
			      is1=Triangles[in1].GetS3();
			      is2=Triangles[in1].GetS2();

			      Triangles[new1].SetN1(is1);
			      Triangles[new2].SetN1(is2);
                               
			      Triangles[is1].SetN1(new1); 
			      Triangles[is2].SetN1(new2); 
			      //independent of quadrant
		       }
                       if(pSplit2){
			      // have split neighbours on edge 2
			      // These are
			      quad=Triangles[itri].GetQuad();
			      otherquad=Triangles[in2].GetQuad();

	   		   iquad=(int)quad;
			   if(iquad > 4 &&  iquad <15)otherquad=quad;


			      if(quad != otherquad){
			      is1=Triangles[in2].GetS3();
			      is2=Triangles[in2].GetS4();
			      }
			      else {
			      is1=Triangles[in2].GetS4();
			      is2=Triangles[in2].GetS2();
			      }
			      if(quad != otherquad){
			      Triangles[is1].SetN3(new1); 
			      Triangles[is2].SetN3(new3);
			      }
			      else {
			      Triangles[is1].SetN2(new1);
			      Triangles[is2].SetN2(new3);
			      }
			      Triangles[new1].SetN2(is1);
			      Triangles[new3].SetN2(is2);

		       }
                       if(pSplit3){
			      // have split neighbours on edge 3
			      // These are
			      quad=Triangles[itri].GetQuad();
			      otherquad=Triangles[in3].GetQuad();

                              iquad=(int)quad;
	    	              if(iquad > 4 &&  iquad <15)otherquad=quad;

                              if(quad != otherquad){
			      is1=Triangles[in3].GetS2();
			      is2=Triangles[in3].GetS4(); 
			      }
				      else {
			      is1=Triangles[in3].GetS4();
			      is2=Triangles[in3].GetS3(); 
				      }
                              if(quad != otherquad){
			      Triangles[is1].SetN2(new2);
			      Triangles[is2].SetN2(new3);
			      }
			      else
			      {
			      Triangles[is1].SetN3(new2);
			      Triangles[is2].SetN3(new3);  
			      }

			      Triangles[new2].SetN3(is1);
			      Triangles[new3].SetN3(is2);
		       }
		       
		       
		     ntrinew=ntrinew+4;

		    }  //endif neighbours unsplit
	    }  //end loop over tranche of triangles

	    if(idiv==0)filename[0]=(char*)"Sphere1.dat";
	    if(idiv==1)filename[0]=(char*)"Sphere2.dat";
	    if(idiv==2)filename[0]=(char*)"Sphere3.dat";
	    if(idiv==3)filename[0]=(char*)"Sphere4.dat";
	    if(idiv==4)filename[0]=(char*)"Sphere5.dat";

    file_out.open(*filename, ios::out);  //can have ios::app for appending
    file_out << n_nodes+1 <<" "<< ntrinew << endl;

    //output triangle number, 3 node numbers, and quadrant id
    for(int i=istop; i< istop+ntrinew; i++){
       file_out  <<   Triangles[i].Get1() <<" "<< Triangles[i].Get2() 
                <<" "<<  Triangles[i].Get3() 
	        <<" "<<  Triangles[i].GetQuad()  << endl;
    }
    //output triangle neighbours on edges 1 2 and 3.
    for(int i=istop; i < istop+ntrinew; i++){
       file_out  <<"  " << Triangles[i].GetN1()-istop <<" "<<  Triangles[i].GetN2()-istop
                <<" "<<  Triangles[i].GetN3()-istop << endl;
    }

    //  n_nodes runs from 0  to n_nodes, so there are actually n_nodes+1 nodes!
	      for(int i=0; i<n_nodes+1;i++){
	//	      cout << "Normalising i=" << i << endl;
		      Normalise(NodeV[i]);
	      }
    //output x,y,z coordinates of nodes.

    for(int  i=0; i< n_nodes+1;  i++){
      file_out <<  NodeV[i].GetX()  <<" "<< 
	      NodeV[i].GetY() <<" "<<  NodeV[i].GetZ() << endl;
    }

    file_out.close();

	      istart=istop;
	      istop=istop+ntrinew;
	      cout << " new istart=" << istart  << endl;
	      cout << "new istop=" << istop << endl;

	      int ie1, ie2, ie3,  ie4;
	      //check connections!
	      cout << "ISTART  ISTOP " << istart  << "  " << istop << endl;
	      for(int itri=istart; itri < istop; itri++){

	//	  cout << "Checking T" << itri << endl;

                  in1=Triangles[itri].GetN1();
		  in2=Triangles[itri].GetN2();
		  in3=Triangles[itri].GetN3();

		  ie1=Triangles[itri].Get1();  //across edge 1
		  ie2=Triangles[itri].Get2();

		  ie3=Triangles[in1].Get1();  // Allways Opposite
		  ie4=Triangles[in1].Get2();

		  if( ie1 != ie4)cout << " edge mismatch  1   "
		  << "Ts " <<  itri  << " " << in1  << " " << ie1 << " " << ie2
		  << " in " << itri <<  "  and " << ie3 << " " << ie4 << endl;

		  ie1=Triangles[itri].Get1(); //  across edge 2
		  ie2=Triangles[itri].Get3();

		  quad=Triangles[itri].GetQuad();
		  otherquad=Triangles[in2].GetQuad();

                  iquad=(int)quad;
		  if(iquad > 4 &&  iquad <15)otherquad=quad;


		  if(quad != otherquad){
		  ie3=Triangles[in2].Get3();
		  ie4=Triangles[in2].Get2();}  // Same directions
		  else {
		  ie3=Triangles[in2].Get1();
		  ie4=Triangles[in2].Get3();    //Opposite directions
		  }

		  if( ie1 != ie4)cout << " edge mismatch  2   "
		  << "Ts " <<  itri  << " " << in1  << " " << ie1 << " " << ie2
		  << " in " << itri <<  "  and " << ie3 << " " << ie4 
	         << "  " << in2 << 
		 "  quads are " << (int)quad << " " << (int)otherquad <<endl;



		  ie1=Triangles[itri].Get2();  //across edge 3
		  ie2=Triangles[itri].Get3();

		  quad=Triangles[itri].GetQuad();
		  otherquad=Triangles[in3].GetQuad();

                  iquad=(int)quad;
		  if(iquad > 4 &&  iquad <15)otherquad=quad;


		  if(quad != otherquad){
		  ie3=Triangles[in3].Get3();     // Same directions
		  ie4=Triangles[in3].Get1(); }
		  else {
		  ie3=Triangles[in3].Get2();
		  ie4=Triangles[in3].Get3();    //  Opposite directions
		  }

		  if( ie1 != ie4)cout << " edge mismatch  3   "
		  << "Ts " <<  itri  << " " << in1  << " " << ie1 << " " << ie2
		  << " in " << itri <<  "  and " << ie3 << " " << ie4 
	         << "  " << in2 << 
		 "  quads are " << (int)quad << " " << (int)otherquad <<endl;
	      }



    }
	    cout <<"Number of nodes is " << n_nodes+1 << endl;

    //exit(0);

 
 while(!quitit){
        
       while(SDL_PollEvent(&event)){

          switch(event.type){
               case SDL_QUIT:
                 quitit=true;
                 break;
                 case SDL_MOUSEBUTTONDOWN:
                    mousedown=true;
                 break;
                 case SDL_MOUSEBUTTONUP:
                    mousedown=false;
                 break;
                 case SDL_MOUSEMOTION:
                  if(mousedown){
                         if(MouseOn)
                         if(tethered || staked)
                           Camera1.MouseView();
                           else
                           Camera1.MouseLookAt();
                 }
                  else{
                         if(MouseOn)
                            if(tethered || staked)
                                Camera1.MouseLookAt(); 
                                else
                                Camera1.MouseLookAt(); 
                 } //from PlotGlobe
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
              CheckMove(Camera1);
              RenderScene(Camera1);
            } //end of outer loop

}



void RenderScene(CCam& Camera1)
{

      glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();

      LIGHTS=true;

      if(LIGHTS)
	      glEnable(GL_LIGHTING);
      else
	      glDisable(GL_LIGHTING);

     int il=0; //light number

     float ambient[4]={RedL[il][0], GreenL[il][0], BlueL[il][0], AlphaL[il][0]}; 
     float diffuse[4]={RedL[il][1], GreenL[il][1], BlueL[il][1], AlphaL[il][1]}; 
     float specular[4]={RedL[il][2], GreenL[il][2], BlueL[il][2], AlphaL[il][2]}; 

//   sets light colours
         glLightfv(MYLIGHTS[il],GL_AMBIENT,ambient);
         glLightfv(MYLIGHTS[il],GL_DIFFUSE,diffuse);
         glLightfv(MYLIGHTS[il],GL_SPECULAR,specular);



/*
         gLightPosition[0]=1.0;  //light from pos  openGL x 
         gLightPosition[1]=0.0;
         gLightPosition[2]=0.0; 
         //looks like light from gl (1,0,0) (at beginning of <---->)


         gLightPosition[0]=0.0;  //light from pos  openGL y
         gLightPosition[1]=0.0;
         gLightPosition[2]=1.0; 
         //looks like light from gl (0,0,1) (at beginning of <---->)


         gLightPosition[0]=0.0;  //light from pos  openGL y
         gLightPosition[1]=1.0;
         gLightPosition[2]=0.0; 
         //looks like light from gl (0,0,1) (at beginning of <---->)
*/
         double lightsx,lightsy,lightsz,lightsnorm;

         lightsx=Camera1.CamPos.GetX(); 
         lightsy=Camera1.CamPos.GetY();
         lightsz=Camera1.CamPos.GetZ();

         if( lightsnorm>1.e-6){  //makes no difference but do it anyway
           lightsnorm=sqrt(lightsx*lightsx+lightsy*lightsy+lightsz*lightsz);
           lightsx=lightsx/lightsnorm;
           lightsy=lightsy/lightsnorm;
           lightsz=lightsz/lightsnorm;
         }



//       This light is always behind you, so nothing in shadow!
         gLightPosition[0]=(float)lightsx;
         gLightPosition[1]=(float)lightsy;
         gLightPosition[2]=(float)lightsz;


        //Now lets set some stuff for gluLookat
        
        float eye[3],stare[3],up[3];

        eye[0]=(float)Camera1.CamPos.GetX();
        eye[1]=(float)Camera1.CamPos.GetY();
        eye[2]=(float)Camera1.CamPos.GetZ();

        stare[0]=(float)Camera1.CamView.GetX();
        stare[1]=(float)Camera1.CamView.GetY();
        stare[2]=(float)Camera1.CamView.GetZ();

        if(boom){
          if(exwhyzed){
             up[0]=Camera1.jay.GetX();
             up[1]=Camera1.jay.GetY();
             up[2]=Camera1.jay.GetZ();
           }
           else{
             up[0]=Camera1.jprime.GetX();
             up[1]=Camera1.jprime.GetY();
             up[2]=Camera1.jprime.GetZ();
           }
        }

        gluLookAt(eye[0],eye[1],eye[2],
                  stare[0],stare[1],stare[2],
                  up[0],up[1],up[2]);


        gLightPosition[3]=0.0; //zero sets it as directional

         glLightfv(MYLIGHTS[il],GL_POSITION,gLightPosition);
                   //  need glLightfv AFTER gluLookat.


        //  Examples light at (0,0,1) on openGL k axis



       double exmin, whymin, zedmin;
       double exmax, whymax, zedmax;
       double exrange, whyrange,zedrange;
       exrange=xrange; whyrange=yrange; zedrange=zrange; 
       exmin=xmin, whymin=ymin; zedmin=zmin;


         double Halfscreen=3000.0;
         double Screen=2.*Halfscreen;
         double maxrange;
         maxrange=exrange;
         if(maxrange < whyrange)maxrange=whyrange;
         if(maxrange < zedrange)maxrange=zedrange;

         double Halfscreenx,Halfscreeny,Halfscreenz;
         Halfscreenx=Halfscreen*exrange/maxrange;
         Halfscreeny=Halfscreen*whyrange/maxrange;
         Halfscreenz=Halfscreen*zedrange/maxrange;
     

	 double x1,y1,z1;
	 double x2,y2,z2;
	 double x3,y3,z3;
	 double x4,y4,z4;
	 

      // materials
      float mat_spec[]={1.0, 0.0, 0.0, 0.0};  //polygon's ref of specular light
      float mat_diff[]={1.0, 0.0, 0.0, 0.0};  //polygon's ref of diffuse light
      float mat_amb[]={1.0, 0.0, 0.0, 0.0};  //polygon's ref of ambient light
      float mat_amb2[]={0.0, 1.0, 0.0, 0.0};  //polygon's ref of ambient light
      float mat_shine[]= {2.0};  //polygon's specular reflection
    // 0.0 to 128, small values give sharper specular reflection
      //lines
      float line_spec[]={0.0,0.0,0.0,1.0};  //line's ref of specular light
      float line_amb[]={0.0,0.0,0.0,1.0};  //line's ref of specular light
      float line_diff[]={0.0,0.0,0.0,0.0};  //line's ref of diffuse light
      float line_shine[]= {0.0};  //lines's sharpness of specular ref 

      glLineWidth(3.0);
      //  glColor3ub(255,0,0);  //(without lighting enabled)
      //


      double xvals[3],yvals[3],zvals[3];

      float fxvals[3],fyvals[3],fzvals[3];


      cout <<"Loop Triangles from istart to istop " << istart << "  " << istop << endl;

      for(int i=istart; i< istop; i++){

		 int mi,mj,mk;
		 mi=Triangles[i].Get1();
		 mj=Triangles[i].Get2();
		 mk=Triangles[i].Get3();


                 int j=0;
                 xvals[j]=NodeV[mi].GetX();
                 yvals[j]=NodeV[mi].GetY();
                 zvals[j]=NodeV[mi].GetZ();
                 fxvals[j]=(float)xvals[j];fyvals[j]=(float)yvals[j];fzvals[j]=(float)zvals[j];

		 j=1;
                 xvals[j]=NodeV[mj].GetX();
                 yvals[j]=NodeV[mj].GetY();
                 zvals[j]=NodeV[mj].GetZ();
                 fxvals[j]=(float)xvals[j];fyvals[j]=(float)yvals[j];fzvals[j]=(float)zvals[j];

		 j=2;
                 xvals[j]=NodeV[mk].GetX();
                 yvals[j]=NodeV[mk].GetY();
                 zvals[j]=NodeV[mk].GetZ();
                 fxvals[j]=(float)xvals[j];fyvals[j]=(float)yvals[j];fzvals[j]=(float)zvals[j];

	      D3Dvec edge1, edge2,cross,normal;
	      edge1.SetX(xvals[1]-xvals[0]);
	      edge1.SetY(yvals[1]-yvals[0]);
	      edge1.SetZ(zvals[1]-zvals[0]);
	      edge2.SetX(xvals[2]-xvals[0]);
	      edge2.SetY(yvals[2]-yvals[0]);
	      edge2.SetZ(zvals[2]-zvals[0]);

//   our original coordinates are in "standard cartesians|"
//   openGL uses another right handed system 
//   x'=x, y'=z, z'=-y

	      cross=edge1*edge2;
	      Normalise(cross);
	      glNormal3f( (float)cross.GetX(), (float)cross.GetZ(), -(float)cross.GetY());

          //    Camera1 at (0,0,3000), icosahedron on unit shere
              float scaleit=1000.0;

//    first draw triangles
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	      glBegin(GL_TRIANGLES);
          	glVertex3f( scaleit*fxvals[0], scaleit*fzvals[0], -scaleit*fyvals[0] );
          	glVertex3f( scaleit*fxvals[1], scaleit*fzvals[1], -scaleit*fyvals[1] );
          	glVertex3f( scaleit*fxvals[2], scaleit*fzvals[2], -scaleit*fyvals[2] );
             glEnd(); 


//    Now draw grid
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, line_shine);

              glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	      glBegin(GL_TRIANGLES);
          	glVertex3f( scaleit*fxvals[0], scaleit*fzvals[0], -scaleit*fyvals[0] );
          	glVertex3f( scaleit*fxvals[1], scaleit*fzvals[1], -scaleit*fyvals[1] );
          	glVertex3f( scaleit*fxvals[2], scaleit*fzvals[2], -scaleit*fyvals[2] );
             glEnd(); 
      }


      glPopMatrix();

      SDL_GL_SwapBuffers();

}


