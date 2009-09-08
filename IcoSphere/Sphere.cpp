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

#include "Sphere.h"
#include <fstream>

//  We shall be using OpenGL's Quadric function
//  GLU_FILL means that it won't be wire frame
//  GLU_LINE means it will be wire frame
//  int g_RenderMode=GLU_FILL; // this is for quadrics only
//

int g_RenderMode=GLU_LINE;

int nv,npoly;

const double pi=acos(-1.0);
//
D3Dvec *NodeV;
Triangle *Triangles;
int ntri, ntrinew;
int istart,istop, isplit, iquad;

double xmin,xmax,ymin,ymax,zmin,zmax;
bool   xallpos,xallneg;
bool   yallpos,yallneg;
bool   zallpos,zallneg;

int iplot=-1;

double xrange,yrange,zrange;
double xrangenorm, yrangenorm,zrangenorm;
int   normx,normy,normz;


char *cstrval=(char*)malloc(50);;
//cstrval=(char*)malloc(50);

const int MAX_TEXTURES=300;
unsigned int gl_Texture[MAX_TEXTURES];

/*  FONTS IN
HAVE TRUETYPE FONTS IN
1.  /usr/share/tuxpaint/fonts
2,  /usr/lib/SunJava2-1.4.2/jre/lib/fonts
3.  /usr/X11R6/lib/X11/fonts/truetype
4   plus a few others from games and povray
*/

int width=1024;
int height=768;
const double speed=50;
const double acceleration=1;
const double convert=180.0/pi;
const double twopi=2.0*pi;
// instantaneous rotation angles
double angx=0.0, angy=0.0;
// cumulative versions
double angxcum=0.0, angycum=0.0;

bool upPressed=false;
bool downPressed=false;
bool leftPressed=false;
bool ctrl_leftPressed=false;
bool shift_leftPressed=false;
bool rightPressed=false;
bool ctrl_rightPressed=false;
bool shift_rightPressed=false;
bool p_Pressed=false;
bool MouseOn=true;
bool togglez=false;



void Init(){
   InitialiseGL(SCREEN_WIDTH, SCREEN_HEIGHT);
  // CreateTexture(gl_Texture,"Earth2.bmp",0);

   //lighting  r,b,g,alpha (alpha is for blending)
   glClearColor(1.,1.,1.,1.); //background colour white
   glClearColor(0.,0.,0.,1.); //background colour black

     std::cout << " Max Number of Lights=" << GL_MAX_LIGHTS << endl;

     //To specifiy a light we need to name them as follows
     // from GL_LIGHT0, GL_LIGHT1,GL_LIGHT2,... GL_LIGHTN.

     /* Second Argument can be
       GL_AMBIENT, GL_DIFFUSE,GL_SPECULAR,GL_POSITION,
    GL_SPOT_CUTTOFF, GL_SPOT_DIRECTION, GL_SPOT_EXPONENT,
    GL_CONSTANT_ATTENIATION, GL_LINEAR_ATTENUATION,
    GL_QUADRATIC_ATTENUATION   */
    //
    //colour of the ambient and diffuse light
     float ambient[4]={0.7, 0.7, 0.7, 0.2}; // light from all over
     float diffuse[4]={1.0, 1.0, 1.0, 1.0}; // light component reflecting diffusely
     float specular[4]={1.0, 1.0, 1.0, 1.0}; //light reflecting specularly

     glLightfv(GL_LIGHT0,GL_AMBIENT, ambient);
     glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
     glLightfv(GL_LIGHT0,GL_SPECULAR, specular);

     float gLightPosition[4]={-1000.,-1000.,-1000.,0.0};
  //   float gLightPosition[4]={10000.,0.,0., 1.0};
     //The last number  tells OpenGL that it's
     // a light position if it is non zero. 
     // The first three numbers are the coordinates. If this last entry is zero
     // OpenGL will treat it as a direction, and will work out
     // direction cosines from the first three numbers. 

     glLightfv(GL_LIGHT0,GL_POSITION,gLightPosition);

     glEnable( GL_LIGHT0 );

     glEnable( GL_LIGHTING);

}
void EventLoop(CCam & Camera1)
{
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

    extern double X,Y,Z;
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

    for(int i=0; i< 20; i++){
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

    ntri=20; n_nodes=12; ntrinew=0;   //we have 8 triangles and 6 nodes


    ofstream file_out;
    file_out.open("Sphere0.dat", ios::out);  //can habe ios::app for appending
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

	    if(idiv==0)*filename="Sphere1.dat";
	    if(idiv==1)*filename="Sphere2.dat";
	    if(idiv==2)*filename="Sphere3.dat";
	    if(idiv==3)*filename="Sphere4.dat";
	    if(idiv==4)*filename="Sphere5.dat";

    file_out.open(*filename, ios::out);  //can habe ios::app for appending
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
                         if(MouseOn)Camera1.MouseView();}
                  else{
                         if(MouseOn)Camera1.MouseLookAt(); }
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
void RenderScene(CCam & Camera1)
{

       glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
       glLoadIdentity();

       //
       //camera  pos      view     up vector
       gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.CamUp.GetX(),   Camera1.CamUp.GetY(),   Camera1.CamUp.GetZ());   


      //create fonts here
      //Check in Camera.h
      //Camera at (0,0,-5000)
      // stare at (0,0,0)

      //camera angle is 45 degees
      //camera 5000 away
      //-2000. is where xmin will be
      //+2000. is where xmax will be
      //
      //bounding box
 
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

      for(int i=istart; i<istop; i++){

		 int mi,mj,mk;
		 mi=Triangles[i].Get1();
		 mj=Triangles[i].Get2();
		 mk=Triangles[i].Get3();

                 int j=0;
                 xvals[j]=NodeV[ Triangles[i].Get1()].GetX();
                 yvals[j]=NodeV[ Triangles[i].Get1()].GetY();
                 zvals[j]=NodeV[ Triangles[i].Get1()].GetZ();

	/*	 cout << Triangles[i].Get1() << "  "
                 << xvals[j]*xvals[j]
                 + yvals[j]*yvals[j]
                 + zvals[j]*zvals[j] << endl; */

		 j=1;
                 xvals[j]=NodeV[ Triangles[i].Get2()].GetX();
                 yvals[j]=NodeV[ Triangles[i].Get2()].GetY();
                 zvals[j]=NodeV[ Triangles[i].Get2()].GetZ();

	/*	 cout << Triangles[i].Get2() << "  "
                 << xvals[j]*xvals[j]
                 + yvals[j]*yvals[j]
                 + zvals[j]*zvals[j] << endl; */

		 j=2;
                 xvals[j]=NodeV[ Triangles[i].Get3()].GetX();
                 yvals[j]=NodeV[ Triangles[i].Get3()].GetY();
                 zvals[j]=NodeV[ Triangles[i].Get3()].GetZ();

         /*	 cout << Triangles[i].Get3() << "  "
                 << xvals[j]*xvals[j]
                 + yvals[j]*yvals[j]
                 + zvals[j]*zvals[j] << endl; */

	      D3Dvec edge1, edge2,cross,normal;
	      edge1.SetX(xvals[1]-xvals[0]);
	      edge1.SetY(yvals[1]-yvals[0]);
	      edge1.SetZ(zvals[1]-zvals[0]);
	      edge2.SetX(xvals[2]-xvals[0]);
	      edge2.SetY(yvals[2]-yvals[0]);
	      edge2.SetZ(zvals[2]-zvals[0]);

	      cross=edge1*edge2;
	      Normalise(cross);
	      glNormal3f( (float)cross.GetX(), cross.GetY(),cross.GetZ());


              float scaleit=3000.0;

      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      if(i==iplot)glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb2);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
              glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	      glBegin(GL_TRIANGLES);
          	glVertex3f( scaleit*xvals[0], scaleit*zvals[0], -scaleit*yvals[0] );
          	glVertex3f( scaleit*xvals[1], scaleit*zvals[1], -scaleit*yvals[1] );
          	glVertex3f( scaleit*xvals[2], scaleit*zvals[2], -scaleit*yvals[2] );
             glEnd(); 
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, line_shine);

              glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	      glBegin(GL_TRIANGLES);
          	glVertex3f( scaleit*xvals[0], scaleit*zvals[0], -scaleit*yvals[0] );
          	glVertex3f( scaleit*xvals[1], scaleit*zvals[1], -scaleit*yvals[1] );
          	glVertex3f( scaleit*xvals[2], scaleit*zvals[2], -scaleit*yvals[2] );
             glEnd(); 
      }

      SDL_GL_SwapBuffers();

}

void HandleKeyPress(SDL_keysym *whatkey)
{ 
             int igetscreen;
             float myspeed=speed;

             switch(whatkey->sym)
             {
                 case SDLK_F1:
                   ToggleFullScreen();
                   break;
                 case SDLK_F2:
                   if(MouseOn==true)
                     {
                      MouseOn=false;
                     }
                     else
                    {
                      MouseOn=true;
                    }
                    break;
                 case SDLK_F9:
                   if(togglez==true)
                        togglez=false;
                   else
                        togglez=true;

                 case SDLK_F10:
                   igetscreen=Screenshot(MainWindow,"screenshot.bmp");
                   break;
                 case SDLK_ESCAPE:
                   SDL_Quit();
                   exit(0);
                   break;
                 case  SDLK_UP:
                   upPressed=true;
                   break;
		 case  SDLK_DOWN:
                   downPressed=true;
                   break;
                 case SDLK_LEFT:
                   leftPressed=true;
                   if( whatkey->mod & KMOD_CTRL)
                   {
                   leftPressed =false;
                   ctrl_leftPressed=true;
                   }
                   if( whatkey->mod & KMOD_SHIFT){
                   leftPressed =false;
                   shift_leftPressed=true;
                   }
                   break;
                 case SDLK_RIGHT:
                   rightPressed=true;
                   if( whatkey->mod & KMOD_CTRL)
                   {
                   rightPressed =false;
                   ctrl_rightPressed=true;
                   }
                   if( whatkey->mod & KMOD_SHIFT){
                   rightPressed =false;
                   shift_rightPressed=true;
                   }
                 default:
                   break;
                 case SDLK_p:
                   p_Pressed=true;
                   break; 
                 case SDLK_F12:
                   iplot++;
                   break;
             }
}

void HandleKeyRelease(SDL_keysym *whatkey)
{ 
             switch(whatkey->sym)
             {
                 case  SDLK_UP:
                   upPressed=false;
                   break;
		 case  SDLK_DOWN:
                   downPressed=false;
                   break;
                 case SDLK_LEFT:
                   leftPressed=false;
                   shift_leftPressed=false;
                   ctrl_leftPressed=false;
                   break;
                 case SDLK_RIGHT:
                   rightPressed=false;
                   shift_rightPressed=false;
                   ctrl_rightPressed=false;
                   break;
                 default:
                   break;
                 case SDLK_p:
                   p_Pressed=false;
                   break; 
             }
}

void CheckMove(CCam & Camera1)
{
    if(downPressed)Camera1.CamMove(-speed);
    if(upPressed)Camera1.CamMove(speed);
             
    if(leftPressed)Camera1.CamRotatePos(-speed/1000);
    if(rightPressed)Camera1.CamRotatePos(speed/1000);

    //assumes noone does ctrl and shift together!
    if(shift_leftPressed)Camera1.CamRotateView(-speed/1000);
    if(shift_rightPressed)Camera1.CamRotateView(speed/1000);
    if(ctrl_leftPressed)Camera1.CamStrafe(speed);
    if(ctrl_rightPressed)Camera1.CamStrafe(-speed);

    if(p_Pressed){

    FILE *fp=fopen("MyFileName.ps","wb");
    GLint buffsize=0;
    GLint state=GL2PS_OVERFLOW;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    while(state==GL2PS_OVERFLOW){
       buffsize+=1024*1024;
//     could use GL2PS_USE_CURRENT_VIEWPORT,
       int ips=gl2psBeginPage("MyTitle","MyProducer",viewport,
               GL2PS_PS,GL2PS_BSP_SORT,GL2PS_SILENT | 
	       GL2PS_SIMPLE_LINE_OFFSET | GL2PS_BEST_ROOT,GL_RGBA,0,NULL,
               0,0,0,buffsize,fp,"MyFileName.ps");
       RenderScene(Camera1);
       state=gl2psEndPage();

       }  //end while loop
      fclose(fp);
    } // end p_Pressed

}
