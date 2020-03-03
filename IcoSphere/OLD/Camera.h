#include <math.h>
class CCam{
   public:

    CCam();
    ~CCam();
   D3Dvec CamPos;
   D3Dvec CamView;
   D3Dvec jay;    //this is just (0,1,0) in OpenGL, never changed
   D3Dvec iprime;   // local coordinates
   D3Dvec jprime;   
   D3Dvec kprime;   

   D3Dvec CamUP;

   bool firstcall;

   void CamMove(double); 
   void CamZoom(double); 
   void CamStrafe(double);
   void CamStrafe2(double);
   void CamUpDown(double);

   void CamRotateView1(double);
   void CamRotatePos1(double);
   void CamRotateBoomPos1(double);
   void CamRotateView2(double);
   void CamRotatePos2(double);
   void CamRotateBoomPos2(double);
   void CamBoomSpin(double);
   void CamPlaneRoll(double);
   void CamPlanePitch(double);
   void MouseView();
   void MouseView2();
   void MouseLookAt();

   void SetPos(double, double, double);
   void SetView(double, double, double);
};

/******************** To Do List *********************************************/
//       Remember to make RealCamPos shadow CamPos in an change to CamPos    //
//       Make Collision Test a function call instead of inlining             //
//       Make Periodic PBCs a functon call too                               //
//       Add Collision tests and PBCs to all changes to CamPos               //
//       Add Aeroplane Mouse Control                                         //
//       Add Control panel for bools                                         //
//       Enable toggle for drawing if a contol panel with slidebars is up    //
/*****************************************************************************/

extern CCam Camera1;

CCam::CCam(){
    std::cout << "Creating Camera CCam \n";
    D3Dvec Vec1(0.0, 0.0, 3000.0);  // to be camera position
    D3Dvec Vec2(0.0, 0.0, 0.0);   // to be stare at point
    D3Dvec Vec3(0.0, 1.0, 0.0);   // up vector
    D3Dvec Vec4(1.0, 0.0, 0.0);   // iprime initial
    D3Dvec Vec5(0.0, 1.0, 0.0);   // jprime initial
    D3Dvec Vec6(0.0, 0.0, 1.0);   // kprime initial
    D3Dvec zero(0.0, 0.0, 0.0);
    CamPos=Vec1;
    CamView=Vec2;
    // Remember to always keep Camera Up Vector normalised if changed
    jay=Vec3;  //never change jay = OpenGL j!

    if(exwhyzed){
    iprime=Vec4;  // Local coordinates
    jprime=Vec5;  // initialise 
    kprime=Vec6;  
    }
    if(boom){
    D3Dvec v=zero-CamPos;  //v=s-c  but s=0;
    kprime=v;
    Normalise(kprime);
    iprime=CamPos*jay; //generally not at rightangles
    Normalise(iprime);  //so normalise -careful with changes!
    jprime=kprime*iprime;
    }
    if(flight || wander ){
	    D3Dvec v=CamView-CamPos;  //v=s-c
	    kprime=v;
	    double check=GetMod(kprime);
               if(fabs(check)<1e-6){
		       cout <<" Camera look at point is camera position!\n";
		       exit(0);
	       }
	    Normalise(kprime);
	    iprime=CamPos*jay;  
	    check=GetMod(iprime);

	    if(fabs(check)<1e-6){
		    // camera is at (0, y, 0)
		    jprime=jay;
		    iprime=jprime*kprime;
	    }
		    else
		    {
	             Normalise(iprime);
	             jprime=kprime*iprime;
	    }

    }

    firstcall=true;
};
CCam::~CCam(){
 std::cout <<  "CCam Destructor  \n";
}
/********************************************************************/
void CCam::CamStrafe2(double speed){
CamPos=CamPos-kprime*4*speed;
CamView=CamView-kprime*4*speed;
}
/***********************************************************************/
void CCam::CamStrafe(double speed){
D3Dvec  v;
v=CamView;
v-=CamPos;

D3Dvec iprime;
iprime=v*jay;   
Normalise(iprime);
   //  PERIODIC BOUNDARY CONDITIONS  //
    double xp=CamPos.GetX();
    double yp=CamPos.GetY();
    double zp=CamPos.GetZ();
    ix=(int)(xp/xside);
    iz=(int)(zp/xside);
    ixold=ix;
    izold=iz;

CamPos=CamPos-iprime*4*speed;
CamView=CamView-iprime*4*speed;

//rest is for periodic bcs and collision tests
    xp=CamPos.GetX();
    yp=CamPos.GetY();
    zp=CamPos.GetZ();


      double rxp,ryp,rzp;
      if(periodic_xz){
      rxp=RealCamPos.GetX(); //Make sure RealPos is updated
      ryp=RealCamPos.GetY(); //In all Movement functions!
      rzp=RealCamPos.GetZ();

      rxp=rxp-speed*iprime.GetX();
      if(!twodee)ryp=ryp-speed*iprime.GetY();
      rzp=rzp-speed*iprime.GetZ();

      if(rxp<-ihalfside*xside)rxp=rxp+xlength;
      if(rxp >ihalfside*xside)rxp=rxp-xlength;
      if(rzp<-ihalfside*xside)rzp=rzp+xlength;
      if(rzp >ihalfside*xside)rzp=rzp-xlength;

      RealCamPos.SetVec(rxp,ryp,rzp);
      }
      
     // cout << collisiontest << endl;
      if(collisiontest){
      int deep=0;

      //CamPos is in OpenGL coordinates
      //OctTree is in more usual xyz coordinates
      //Use RealCamPos because we never really leave
      D3Dvec Pos;

      if(periodic_xz){
      double  ex, why, zed;
      ex=rxp; why=-rzp; zed=ryp;  //Translate from OpenGL coords
      Pos.SetVec(ex,why,zed);  //to normal xyz
      }
      else
      {
      double  ex, why, zed;
      ex=xp; why=-zp; zed=yp;  //Translate from OpenGL coords
      Pos.SetVec(ex,why,zed);  //to normal xyz
      }

      D3Dvec testedge1;
      D3Dvec testedge2;
      D3Dvec testnorm;
      D3Dvec testorigin;
      double testalpha, testbeta,testgamma;
      int mytesttri;
      int test1,test2,test3;
      bool kaboom=true;
      bool verbose=false;
      intList* Local;
      ListNode* Head;
      ListNode* Tail;
      int length=0;
      int* newtri;
      int testtri;
      int inode;
      D3Dvec Origin, edge1, edge2, normal;


      int dim=3;
      int p,q,r;

      Dmatrix Matrix(dim,dim);
      Dvector RHS(dim);
      Dvector LHS(dim);
      Dvector CheckPos(dim);
      Dvector ORIG(dim);
      Dvector EDGE1(dim);
      Dvector EDGE2(dim);
      Dvector NORMAL(dim);

      double** Matpp;
      double* lhsV;
      double* rhsV;

      double alpha, beta, gamma;

      double radius=100;

      for(int i=0; i< 8*(MD+1); i++)
	      CollideTri[i]=NULL;

      nlists=0;
      CollideTree->GetList(CollideTri,Pos,X1,X2,Y1,Y2,Z1,Z2,deep);

     // cout <<"Number of Lists=" << nlists << endl;
     // cout << Pos.GetX() << "  " << Pos.GetY() << "  "<<  Pos.GetZ() << endl;

        for(int i=0; i<nlists; i++){
		//      cout << "checking list" << i << endl;
          Local=CollideTri[i];
           if(Local){
           Head=Local->GetHead();
           Tail=Local->GetTail();
           length=Local->GetLength();

	   if(verbose)
	cout << "Local=" << Local << "  depth=" << i  << " length=" << length << endl;

           int j=0;
	   while(Head->GetNextPtr() !=Tail){
	        Head=Head->GetNextPtr();
	        newtri=Head->GetDatumPtr();

	   if(verbose)
	cout << "i=" << i << "  " << "j=" << j << " triangle=" << *newtri << endl;

	        j++;
		testtri=*newtri;
		inode=Triangles[testtri].Get1();
		Origin=NodeV[inode];
		edge1=edges1[testtri]; edge2=edges2[testtri], normal=Normals[testtri]; 

                p=0; q=1, r=2;
		RHS(p)=Pos.GetX()-Origin.GetX();
		RHS(q)=Pos.GetY()-Origin.GetY();
		RHS(r)=Pos.GetZ()-Origin.GetZ();

		ORIG(p)=Origin.GetX(); ORIG(q)=Origin.GetY(); ORIG(r)=Origin.GetZ();
		EDGE1(p)=edge1.GetX(); EDGE1(q)=edge1.GetY(); EDGE1(r)=edge1.GetZ();
		EDGE2(p)=edge2.GetX(); EDGE2(q)=edge2.GetY(); EDGE2(r)=edge2.GetZ();
		NORMAL(p)=normal.GetX();NORMAL(q)=normal.GetY();NORMAL(r)=normal.GetZ();
		
		Matrix.SetCol(EDGE1,p);
		Matrix.SetCol(EDGE2,q);
		Matrix.SetCol(NORMAL,r); 

//                Solver now replaced by MyGaussElim in libmylib
//                Solver(dim, maxerr, Matrix, RHS, LHS); 


                int ierror=0;

                double** Matpp;
                double* lhsV;
                double* rhsV;

                Matpp=Matrix.GetM();
                lhsV=LHS.GetV();
                rhsV=RHS.GetV();
                ierror=myGaussElim(dim, Matpp, rhsV, lhsV);
                if(ierror !=0){
                  cout << " myGaussElim Failed in Camera.h \n";
                }

		alpha=LHS(p); beta=LHS(q); gamma=LHS(r);
		CheckPos=ORIG+EDGE1*alpha+EDGE2*beta+NORMAL*gamma;

		p=Triangles[testtri].Get1(); q= Triangles[testtri].Get2(); 
		r=Triangles[testtri].Get3();

		if(kaboom){

		if(fabs(gamma)<radius){
		    if(alpha <1.0  && alpha >0.0){
		    if(beta<1.0  && beta>0.0){
			    if(alpha+beta<1.0){
				    cout << "KABOOM!!!\n"; exit(0);
			    }}}}
		}
	   }
        }  //endif Local
      }//end  i<nlists Loop
   }//endif for collision test
    //PERIODIC BOUNDARY CONDITIONS (remainder of CamStrafe)
    if(periodic_xz){
    ix=(int)(xp/xside);
    iz=(int)(zp/xside);
    diffx=ix-ixold; diffz=iz-izold;

    if(diffx==-1)
    {
	    if(!launch){
	    if(diffx !=diffoldx && diffoldx !=0){
               // reversed direction --- xshiftedge was increasing
	       xshiftedge=xshiftedge-1;
	       if(xshiftedge <0){
		       cout << "A " << endl;
		       xshiftedge=iside-1;
		     //  exit(0);
	       }
	    }
	    }
	    if(xshiftedge !=-10){
	    for(int i=0; i< iside; i++){
		    xshift[xshiftedge][i]=
		    xshift[xshiftedge][i]-xlength;
	    }
	    xshiftedge=xshiftedge-1;
	    if(xshiftedge <0 )xshiftedge=iside-1;
	    }
	    else
	    {
		    if(startoffx){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    xshift[iside-1][i]=-xlength;
		    }
		    xshiftedge=iside-2;
		    startoffx=false; //DO ONLY ONCE
		    }
	    }
    }
    if(diffx==1){
	    if(!launch){
	    if(diffx !=diffoldx &&  diffoldx !=0){
               // reversed direction --- xshiftedge was decreasing
	       xshiftedge=xshiftedge+1;
	       if(xshiftedge==iside){
		       cout << "B " << endl;
		       xshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }
	    if(xshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    xshift[xshiftedge][i]=
		    xshift[xshiftedge][i]+xlength;
	    }
	    xshiftedge=xshiftedge+1;
	    if(xshiftedge == iside)xshiftedge=0;
	    }
	    else
	    {
		    if(startoffx){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    xshift[0][i]=xlength;
		    }
		    xshiftedge=1;
		    startoffx=false; //DO ONLY ONCE
		    }
	    }
    }

    if(diffz==-1){
	    //heading in negative z direction (OpenGL)
	    //is heading positive y (normal xyz)
	    if(!launch){
	    if(diffz !=diffoldz  &&  diffoldz !=0){
               // reversed direction --- yshiftedge was decreasing
	       yshiftedge=yshiftedge+1;
	       if(yshiftedge==iside){
		       cout << "C " << endl;
		       yshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }

	    if(yshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    yshift[i][yshiftedge]=
		    yshift[i][yshiftedge]+xlength;
	    }
	    yshiftedge=yshiftedge+1;
	    if(yshiftedge == iside)yshiftedge=0;
	    }
	    else
	    {
		    if(startoffy){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    yshift[i][0]=xlength;
		    }
		    yshiftedge=1;
		    startoffy=false; //DO ONLY ONCE
		    }
	    }
    }
    if(diffz==1){
	    if(!launch){
	    if(diffz !=diffoldz  && diffoldz !=0){

               // reversed direction --- yshiftedge was increasing
	       yshiftedge=yshiftedge-1;
	       if(yshiftedge==iside){
		       cout << "D " << endl;
		       yshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }
	    //heading in positive OpenGL  is heading in negative y
	    if(yshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    yshift[i][yshiftedge]=
		    yshift[i][yshiftedge]-xlength;
	    }
	    yshiftedge=yshiftedge-1;
	    if(yshiftedge < 0)yshiftedge=iside-1;
	    }
	    else
	    {
		    if(startoffy){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    yshift[i][iside-1]=-xlength;
		    }
		    yshiftedge=iside-2;
		    startoffy=false;  //DO ONLY ONCE
		    }
	    }
    }
    if( abs(diffx)>0 || abs(diffz)>0){
      if(diffz !=0 && fabs(diffz) !=iside-1)diffoldz=diffz;
      if(diffx !=0 && fabs(diffz) !=iside-1)diffoldx=diffx;
      if(fabs(diffx) !=iside-1 && fabs(diffz)!=iside-1)launch=false; 
      }
     } //endif for periodic xz
    
}
/***********************************************************************/
void CCam::SetPos(double x, double y, double z){
	CamPos.SetVec(x,y,z);
}
/***********************************************************************/
void CCam::SetView(double x, double y, double z){
	CamView.SetVec(x,y,z);
}
/***********************************************************************/
void CCam::CamUpDown(double speed){
	double y=CamPos.GetY();
	double y2=y+speed;
	CamPos.SetY(y2);

	y=CamView.GetY();
	y2=y+speed;
	CamView.SetY(y2);
	RealCamPos=CamPos;
}
/***********************************************************************/
void CCam::CamBoomSpin(double speed){

double CosA=cos(speed);
double SinA=sin(speed);

D3Dvec iprime2,jprime2;

iprime2=iprime*CosA+jprime*SinA;
jprime2=jprime*CosA-iprime*SinA;

iprime=iprime2;
jprime=jprime2;
}
/***********************************************************************/
void CCam::CamPlaneRoll(double speed){

double CosA=cos(speed);
double SinA=sin(speed);

D3Dvec iprime2,jprime2;

iprime2=iprime*CosA+jprime*SinA;
jprime2=jprime*CosA-iprime*SinA;

iprime=iprime2;
jprime=jprime2;

jay=jprime;
}
/***********************************************************************/
void CCam::CamMove(double speed){
    double xp=CamPos.GetX();
    double yp=CamPos.GetY();
    double zp=CamPos.GetZ();

    
   //  PERIODIC BOUNDARY CONDITIONS  //
    ix=(int)(xp/xside);
    iz=(int)(zp/xside);
    ixold=ix;
    izold=iz;

    double xv=CamView.GetX();
    double yv=CamView.GetY();
    double zv=CamView.GetZ();
    double norm;
    if(twodee) norm=
       norm=sqrt( (xv-xp)*(xv-xp)+(zv-zp)*(zv-zp) );
    else
       norm=sqrt( (xv-xp)*(xv-xp)+(yv-yp)*(yv-yp)+(zv-zp)*(zv-zp) );

    if( norm >1.e-1){  //else view undefined at end of cammove
      double speednorm =4.*speed/norm;
      D3Dvec Vel((xv-xp)*speednorm, (yv-yp)*speednorm, (zv-zp)*speednorm);

      xp=xp+Vel.GetX();
      if(!twodee)yp=yp+Vel.GetY();
      zp=zp+Vel.GetZ();

      xv=xv+Vel.GetX();
      if(!twodee)yv=yv+Vel.GetY();
      zv=zv+Vel.GetZ();

      double rxp,ryp,rzp;

      if(periodic_xz){
      rxp=RealCamPos.GetX();
      ryp=RealCamPos.GetY();
      rzp=RealCamPos.GetZ();

      rxp=rxp+Vel.GetX();
      if(!twodee)ryp=ryp+Vel.GetY();
      rzp=rzp+Vel.GetZ();

      if(rxp<-ihalfside*xside)rxp=rxp+xlength;
      if(rxp >ihalfside*xside)rxp=rxp-xlength;
      if(rzp<-ihalfside*xside)rzp=rzp+xlength;
      if(rzp >ihalfside*xside)rzp=rzp-xlength;

      RealCamPos.SetVec(rxp,ryp,rzp);
      }

      CamPos.SetVec(xp,yp,zp);   //OpenGL coords

      if(collisiontest){
      int deep=0;

      //CamPos is in OpenGL coordinates
      //OctTree is in more usual xyz coordinates
      //Use RealCamPos because we never really leave
      D3Dvec Pos;

      if(periodic_xz){
      double  ex, why, zed;
      ex=rxp; why=-rzp; zed=ryp;  //Translate from OpenGL coords
      Pos.SetVec(ex,why,zed);  //to normal xyz
      }
      else
      {
      double  ex, why, zed;
      ex=xp; why=-zp; zed=yp;  //Translate from OpenGL coords
      Pos.SetVec(ex,why,zed);  //to normal xyz
      }

      D3Dvec testedge1;
      D3Dvec testedge2;
      D3Dvec testnorm;
      D3Dvec testorigin;
      double testalpha, testbeta,testgamma;
      int mytesttri;
      int test1,test2,test3;
      bool kaboom=true;
      bool verbose=false;
      intList* Local;
      ListNode* Head;
      ListNode* Tail;
      int length=0;
      int* newtri;
      int testtri;
      int inode;
      D3Dvec Origin, edge1, edge2, normal;


      int dim=3;
      int p,q,r;

      Dmatrix Matrix(dim,dim);
      Dvector RHS(dim);
      Dvector LHS(dim);
      Dvector CheckPos(dim);
      Dvector ORIG(dim);
      Dvector EDGE1(dim);
      Dvector EDGE2(dim);
      Dvector NORMAL(dim);
      double alpha, beta, gamma;

      double radius=100;
      double maxerr;



      for(int i=0; i< 8*(MD+1); i++)
	      CollideTri[i]=NULL;

      nlists=0;
      CollideTree->GetList(CollideTri,Pos,X1,X2,Y1,Y2,Z1,Z2,deep);
      
      if(verbose){
      cout <<"Number of Lists=" << nlists << endl;
      cout << Pos.GetX() << "  " << Pos.GetY() << "  "<<  Pos.GetZ() << endl;
      }

        for(int i=0; i<nlists; i++){
          Local=CollideTri[i];
           if(Local){
           Head=Local->GetHead();
           Tail=Local->GetTail();
           length=Local->GetLength();

	   if(verbose)
	cout << "Local=" << Local << "  depth=" << i  << " length=" << length << endl;

           int j=0;
	   while(Head->GetNextPtr() !=Tail){
	        Head=Head->GetNextPtr();
	        newtri=Head->GetDatumPtr();

	   if(verbose)
	cout << "i=" << i << "  " << "j=" << j << " triangle=" << *newtri << endl;

	        j++;
		testtri=*newtri;
		inode=Triangles[testtri].Get1();
		Origin=NodeV[inode];
		edge1=edges1[testtri]; edge2=edges2[testtri], normal=Normals[testtri]; 

                p=0; q=1, r=2;
		RHS(p)=Pos.GetX()-Origin.GetX();
		RHS(q)=Pos.GetY()-Origin.GetY();
		RHS(r)=Pos.GetZ()-Origin.GetZ();

		ORIG(p)=Origin.GetX(); ORIG(q)=Origin.GetY(); ORIG(r)=Origin.GetZ();
		EDGE1(p)=edge1.GetX(); EDGE1(q)=edge1.GetY(); EDGE1(r)=edge1.GetZ();
		EDGE2(p)=edge2.GetX(); EDGE2(q)=edge2.GetY(); EDGE2(r)=edge2.GetZ();
		NORMAL(p)=normal.GetX();NORMAL(q)=normal.GetY();NORMAL(r)=normal.GetZ();
		
		Matrix.SetCol(EDGE1,p);
		Matrix.SetCol(EDGE2,q);
		Matrix.SetCol(NORMAL,r); 


                double** Matpp;
                double* lhsV;
                double* rhsV;


                Matpp=Matrix.GetM();
                lhsV=LHS.GetV();
                rhsV=RHS.GetV();

                int ierror=0;

                ierror=myGaussElim(dim, Matpp, rhsV, lhsV);

                if(ierror !=0){
                  cout << " myGaussElim Failed in Camera.h \n";
                }
 //               Solver replaced by myGaussElim in libmylib
 //               Solver(dim, maxerr, Matrix, RHS, LHS); 

		alpha=LHS(p); beta=LHS(q); gamma=LHS(r);
		CheckPos=ORIG+EDGE1*alpha+EDGE2*beta+NORMAL*gamma;

		p=Triangles[testtri].Get1(); q= Triangles[testtri].Get2(); 
		r=Triangles[testtri].Get3();

		if(kaboom){

		if(verbose){
      cout << "normal  x y z " << Pos.GetX() 
	      << "  " << Pos.GetY() << "  "<<  Pos.GetZ() << endl;
      cout << "OpenGL x y z " << CamPos.GetX() 
	      << "  " << CamPos.GetY() << "  "<<  CamPos.GetZ() << endl;
			cout << " a b c =" << alpha << "  " << beta
				<< "  " << gamma << endl;
		}

		if(fabs(gamma)<radius){
		    if(alpha <1.0  && alpha >0.0){
		    if(beta<1.0  && beta>0.0){
			    if(alpha+beta<1.0){
				    cout << "KABOOM!!!\n"; exit(0);
			    }}}}
		}
	   }
        }  //endif Local
      }//end  i<nlists Loop

      }//endif for collisiontest


      CamView.SetVec(xv,yv,zv);


    //PERIODIC BOUNDARY CONDITIONS (remainder of CamMove)
    if(periodic_xz){
    ix=(int)(xp/xside);
    iz=(int)(zp/xside);
    diffx=ix-ixold; diffz=iz-izold;

    if(diffx==-1)
    {
	    if(!launch){
	    if(diffx !=diffoldx && diffoldx !=0){
               // reversed direction --- xshiftedge was increasing
	       xshiftedge=xshiftedge-1;
	       if(xshiftedge <0){
		       cout << "A " << endl;
		       xshiftedge=iside-1;
		     //  exit(0);
	       }
	    }
	    }
	    if(xshiftedge !=-10){
	    for(int i=0; i< iside; i++){
		    xshift[xshiftedge][i]=
		    xshift[xshiftedge][i]-xlength;
	    }
	    xshiftedge=xshiftedge-1;
	    if(xshiftedge <0 )xshiftedge=iside-1;
	    }
	    else
	    {
		    if(startoffx){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    xshift[iside-1][i]=-xlength;
		    }
		    xshiftedge=iside-2;
		    startoffx=false; //DO ONLY ONCE
		    }
	    }
    }
    if(diffx==1){
	    if(!launch){
	    if(diffx !=diffoldx &&  diffoldx !=0){
               // reversed direction --- xshiftedge was decreasing
	       xshiftedge=xshiftedge+1;
	       if(xshiftedge==iside){
		       cout << "B " << endl;
		       xshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }
	    if(xshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    xshift[xshiftedge][i]=
		    xshift[xshiftedge][i]+xlength;
	    }
	    xshiftedge=xshiftedge+1;
	    if(xshiftedge == iside)xshiftedge=0;
	    }
	    else
	    {
		    if(startoffx){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    xshift[0][i]=xlength;
		    }
		    xshiftedge=1;
		    startoffx=false; //DO ONLY ONCE
		    }
	    }
    }

    if(diffz==-1){
	    //heading in negative z direction (OpenGL)
	    //is heading positive y (normal xyz)
	    if(!launch){
	    if(diffz !=diffoldz  &&  diffoldz !=0){
               // reversed direction --- yshiftedge was decreasing
	       yshiftedge=yshiftedge+1;
	       if(yshiftedge==iside){
		       cout << "C " << endl;
		       yshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }

	    if(yshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    yshift[i][yshiftedge]=
		    yshift[i][yshiftedge]+xlength;
	    }
	    yshiftedge=yshiftedge+1;
	    if(yshiftedge == iside)yshiftedge=0;
	    }
	    else
	    {
		    if(startoffy){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    yshift[i][0]=xlength;
		    }
		    yshiftedge=1;
		    startoffy=false; //DO ONLY ONCE
		    }
	    }
    }
    if(diffz==1){
	    if(!launch){
	    if(diffz !=diffoldz  && diffoldz !=0){

               // reversed direction --- yshiftedge was increasing
	       yshiftedge=yshiftedge-1;
	       if(yshiftedge==iside){
		       cout << "D " << endl;
		       yshiftedge=0;
		     //  exit(0);
	       }
	    }
	    }
	    //heading in positive OpenGL  is heading in negative y
	    if(yshiftedge != -10){
	    for(int i=0; i< iside; i++){
		    yshift[i][yshiftedge]=
		    yshift[i][yshiftedge]-xlength;
	    }
	    yshiftedge=yshiftedge-1;
	    if(yshiftedge < 0)yshiftedge=iside-1;
	    }
	    else
	    {
		    if(startoffy){
		    //must have started at origin, nothing has been
		    //shifted yet!
		    for(int i=0; i<iside; i++){
			    yshift[i][iside-1]=-xlength;
		    }
		    yshiftedge=iside-2;
		    startoffy=false;  //DO ONLY ONCE
		    }
	    }
    }
    if( abs(diffx)>0 || abs(diffz)>0){
      if(diffz !=0 && fabs(diffz) !=iside-1)diffoldz=diffz;
      if(diffx !=0 && fabs(diffz) !=iside-1)diffoldx=diffx;
      if(fabs(diffx) !=iside-1 && fabs(diffz)!=iside-1)launch=false; 
      }
    }//endif for periodic_xz
   }
   else
   {
      std::cout <<"view undefined in CamMove, Camera.cpp\n";
      exit(1);
   }
}

/***********************************************************************/
void CCam::CamZoom(double speed){
//same as CamMove except that the stare at point doesn't change.
//No periodic boundary applied
double xp=CamPos.GetX();
double yp=CamPos.GetY();
double zp=CamPos.GetZ();

double xv=CamView.GetX();
double yv=CamView.GetY();
double zv=CamView.GetZ();
double norm;
if(twodee) norm=
     norm=sqrt( (xv-xp)*(xv-xp)+(zv-zp)*(zv-zp) );
else
     norm=sqrt( (xv-xp)*(xv-xp)+(yv-yp)*(yv-yp)+(zv-zp)*(zv-zp) );

if( norm >1.e-1){
   double speednorm =4.*speed/norm;
   D3Dvec Vel((xv-xp)*speednorm, (yv-yp)*speednorm, (zv-zp)*speednorm);
      xp=xp+Vel.GetX();
      if(!twodee)yp=yp+Vel.GetY();
      zp=zp+Vel.GetZ();
      CamPos.SetVec(xp,yp,zp);
      RealCamPos=CamPos;
   }
   else
   {
   //   Reverse move
   double speednorm =4.*speed/norm;
   D3Dvec Vel((xv-xp)*speednorm, (yv-yp)*speednorm, (zv-zp)*speednorm);
      xp=xp-Vel.GetX();
      if(!twodee)yp=yp-Vel.GetY();
      zp=zp-Vel.GetZ();
      CamPos.SetVec(xp,yp,zp);
      RealCamPos=CamPos;
   }
}
/***********************************************************************/
void CCam::CamRotateView1(double speed){

double xp=CamPos.GetX();
double zp=CamPos.GetZ();

double xv=CamView.GetX();
double zv=CamView.GetZ();

double vx=(xv-xp);    //(s-c)
double vz=(zv-zp);

double CosA=cos(speed);
double SinA=sin(speed);

double vx2=(CosA*vx-SinA*vz);
double vz2=(SinA*vx+CosA*vz);

CamView.SetX(xp+vx2);  //c+Rotate(s-c)
CamView.SetZ(zp+vz2);

}
/***********************************************************************/
void CCam::CamRotateView2(double speed){

double xp=CamPos.GetX();
double yp=CamPos.GetY();
double zp=CamPos.GetZ();

double xv=CamView.GetX();
double yv=CamView.GetY();
double zv=CamView.GetZ();

double vx=(xv-xp);
double vy=(yv-yp);
double vz=(zv-zp);   //s-c

double rho=sqrt(vx*vx+vz*vz);  //project to xz plane
double cosang, sinang, ang;
cosang=vx/rho;
sinang=vz/rho;

double CosA=cos(speed);
double SinA=sin(speed);

double vr2y=(CosA*vy-SinA*rho);
double vr2xz=(SinA*vy+CosA*rho);

double vx2=vr2xz*cosang;
double vz2=vr2xz*sinang;
double vy2=vr2y;

CamView.SetX(xp+vx2);  // c+Rotated (s-c)
CamView.SetY(yp+vy2);  // c+Rotated (s-c)
CamView.SetZ(zp+vz2);

}

/***********************************************************************/
void CCam::CamRotatePos1(double speed){

D3Dvec v=CamView-CamPos;  //v=s-c

double CosA=cos(speed);
double SinA=sin(speed);

double vx=v.Dot(iprime), vy=v.Dot(jprime),  vz=v.Dot(kprime);

double vx2=(CosA*vx-SinA*vz);
double vz2=(SinA*vx+CosA*vz);

CamPos=CamView-iprime*vx2-jprime*vy-kprime*vz2;
RealCamPos=CamPos;

D3Dvec iprime2,kprime2;
iprime2=iprime*CosA+kprime*SinA;
kprime2=kprime*CosA-iprime*SinA; 
iprime=iprime2;
kprime=kprime2;
}
/***********************************************************************/
void CCam::CamRotatePos2(double speed){

D3Dvec v=CamView-CamPos;
double vx=v.Dot(iprime), vy=v.Dot(jprime), vz=v.Dot(kprime);

double CosA=cos(speed);
double SinA=sin(speed);

double vy2=(CosA*vy-SinA*vz);
double vz2=(SinA*vy+CosA*vz);
double vx2=vx;

CamPos=CamView-iprime*vx2-jprime*vy2-kprime*vz2;
RealCamPos=CamPos;
}

/***********************************************************************/
void CCam::CamRotateBoomPos1(double speed){

double CosA=cos(speed);
double SinA=sin(speed);

double vx=-CamPos.Dot(iprime), vy=-CamPos.Dot(jprime), vz=-CamPos.Dot(kprime);

double vx2=(CosA*vx-SinA*vz);
double vz2=(SinA*vx+CosA*vz);

CamPos=CamView-iprime*vx2-jprime*vy-kprime*vz2;  //s -Rotate(s-c)
RealCamPos=CamPos;

D3Dvec iprime2, kprime2;
iprime2=iprime*CosA+kprime*SinA;
kprime2=kprime*CosA-iprime*SinA;
iprime=iprime2;
kprime=kprime2;

}

/***********************************************************************/
void CCam::CamRotateBoomPos2(double speed){

D3Dvec  v;
v=CamView-CamPos;  //v=s-c

double vx=v.Dot(iprime);
double vy=v.Dot(jprime);
double vz=v.Dot(kprime);

double CosA=cos(speed);
double SinA=sin(speed);

double vy2=(CosA*vy-SinA*vz);
double vz2=(SinA*vy+CosA*vz);

CamPos=CamView-iprime*vx-jprime*vy2-kprime*vz2;
RealCamPos=CamPos;

D3Dvec jprime2,kprime2;

jprime2=jprime*CosA+kprime*SinA;
kprime2=kprime*CosA-jprime*SinA;
jprime=jprime2;
kprime=kprime2;
}
/***********************************************************************/
void CCam::CamPlanePitch(double speed){

D3Dvec  v;
v=CamView-CamPos;  //v=s-c

double vx=v.Dot(iprime);
double vy=v.Dot(jprime);
double vz=v.Dot(kprime);

double CosA=cos(speed);
double SinA=sin(speed);

double vy2=(CosA*vy-SinA*vz);
double vz2=(SinA*vy+CosA*vz);

CamView=CamPos+iprime*vx+jprime*vy2+kprime*vz2;

D3Dvec jprime2,kprime2;

jprime2=jprime*CosA+kprime*SinA;
kprime2=kprime*CosA-jprime*SinA;
jprime=jprime2;
kprime=kprime2;

jay=jprime;
}
/***********************************************************************/
void  CCam::MouseView(){
// use mouse to alter the view direction of the camera
int mousex,mousey;
int middlex,middley;

middlex=WIDTH >> 1;  // ">>" is a binary shift operator
middley=HEIGHT >> 1; // so this is divide by 2!
double angy, angx;
angy=0.0;
angx=0.0;
   if(firstcall){
      SDL_WarpMouse(middlex,middley);
      firstcall=false;
      return;
   } 
SDL_GetMouseState(&mousex,&mousey);
if(middlex==mousex && middley==mousey)return;
SDL_WarpMouse(middlex,middley);

angy =(double)(mousex-middlex)/1000.0;   //rotate about cameras y axis if x changes
angx =(double)(mousey-middley)/1000.0;   //rotate about camera x axis

D3Dvec  v;
v=CamView-CamPos;  //v=s-c
iprime=jay*v;  
Normalise(iprime);
kprime=iprime*jay;
//kprime is now unit z vector at camera
//
double vx=iprime.Dot(v);
double vy=jay.Dot(v);
double vz=kprime.Dot(v);

double SinTheta1=sin(angy);
double CosTheta1=cos(angy);
double SinTheta2=sin(angx);
double CosTheta2=cos(angx);

//Rotate about y followed by rotate about x
double vnewx=CosTheta1*vx-SinTheta1*vz;
double vnewy=CosTheta2*vy-SinTheta2*(SinTheta1*vx+CosTheta1*vz);
double vnewz=SinTheta2*vy+CosTheta2*(SinTheta1*vx+CosTheta1*vz);

//of course iprime etc have OpenGL coordinates!
//CamView=CamPos-iprime*vnewx-jay*vnewy-kprime*vnewz;
//
//    view dir -> c + Rotated (s-c)
CamView=CamPos+iprime*vnewx+jay*vnewy+kprime*vnewz;

}
/***********************************************************************/
void  CCam::MouseView2(){
// use mouse to alter the view direction of the camera
// NOT USED, keep for a while anyway
// Only difference between this and MouseView is the sign of
// the angle on change in mouse x
int mousex,mousey;
int middlex,middley;

middlex=WIDTH >> 1;  // ">>" here is a binary shift operator
middley=HEIGHT >> 1; // so this is divide by 2!
double angy, angx;
angy=0.0;
angx=0.0;
   if(firstcall){
      SDL_WarpMouse(middlex,middley);
      firstcall=false;
      return;
   } 
SDL_GetMouseState(&mousex,&mousey);
if(middlex==mousex && middley==mousey)return;
SDL_WarpMouse(middlex,middley);

angy =(double)(mousex-middlex)/1000.0;   //rotate about cameras y axis if x changes
angx =-(double)(mousey-middley)/1000.0;   //rotate about camera x axis

D3Dvec  v;
v=CamView-CamPos;  //v=s-c
iprime=jay*v;  
Normalise(iprime);
kprime=iprime*jay;
//kprime is now unit z vector at camera
//
double vx=iprime.Dot(v);
double vy=jay.Dot(v);
double vz=kprime.Dot(v);

double SinTheta1=sin(angy);
double CosTheta1=cos(angy);
double SinTheta2=sin(angx);
double CosTheta2=cos(angx);

//Rotate about y followed by rotate about x
double vnewx=CosTheta1*vx-SinTheta1*vz;
double vnewy=CosTheta2*vy-SinTheta2*(SinTheta1*vx+CosTheta1*vz);
double vnewz=SinTheta2*vy+CosTheta2*(SinTheta1*vx+CosTheta1*vz);

//of course iprime etc have OpenGL coordinates!
//CamView=CamPos-iprime*vnewx-jay*vnewy-kprime*vnewz;
//
//    view dir -> c + Rotated (s-c)
CamView=CamPos+iprime*vnewx+jay*vnewy+kprime*vnewz;
}


/***********************************************************************/
void  CCam::MouseLookAt(){

int mousex,mousey;
int middlex,middley;

middlex=WIDTH >> 1;
middley=HEIGHT >> 1;
double angy, angx;
angy=0.0;
angx=0.0;
SDL_GetMouseState(&mousex,&mousey);
   if(firstcall){
      SDL_WarpMouse(middlex,middley);
      firstcall=false;
      return;
     }

if(middlex==mousex && middley==mousey)return;
SDL_WarpMouse(middlex,middley);

angy =(double)(mousex-middlex)/1000.0;   //rotate about cameras y axis if x changes
angx =(double)(mousey-middley)/1000.0;   //rotate about camera x axis
angy =-(double)(mousex-middlex)/1000.0;   //rotate about cameras y axis if x changes
angx =-(double)(mousey-middley)/1000.0;   //rotate about camera x axis

D3Dvec  v;
v=CamView-CamPos;  //  v=s-c
iprime=jay*v;   //jprime is jay   
Normalise(iprime);
kprime=iprime*jay;

double vx=iprime.Dot(v);
double vy=jay.Dot(v);
double vz=kprime.Dot(v);
 
double SinTheta1=sin(angy);
double CosTheta1=cos(angy);
double SinTheta2=sin(angx);
double CosTheta2=cos(angx);

//Rotate about y followed by rotate about x
double vnewx=CosTheta1*vx-SinTheta1*vz;
double vnewy=CosTheta2*vy-SinTheta2*(SinTheta1*vx+CosTheta1*vz);
double vnewz=SinTheta2*vy+CosTheta2*(SinTheta1*vx+CosTheta1*vz);

// c ->  s - Rotated(s-c)
CamPos=CamView-iprime*vnewx-jay*vnewy-kprime*vnewz;
RealCamPos=CamPos;
}
