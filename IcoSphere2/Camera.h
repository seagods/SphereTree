#include <math.h>
class CCam{
   public:

    CCam();
    ~CCam();
   D3Dvec CamPos;
   D3Dvec CamView;
   D3Dvec CamUp;

   bool firstcall;

   void CamPlace(D3Dvec &, D3Dvec &,  D3Dvec &);
   void CamMove(double); 
   void CamRotateView(double);
   void CamRotatePos(double);
   void CamStrafe(double);
   void MouseView();
   void MouseLookAt();
};

extern CCam Camera1;
CCam::CCam(){

    std::cout << "Creating Camera CCam \n";
//    Declaring CCam has called constructo
//    for D3Dvec (no arguments) three times
//    So CamPos, CamView, and CamUp are all
//    Set to (1.,1.,1.)
//    but now scale to

    D3Dvec Vec1(0.0,0.0,11000);  // to be camera position
    D3Dvec Vec2(0.0,0.0,0.0);   // to be stare at point
    D3Dvec Vec3(0.0,1.0,0.0);   // up vector
    CamPos=Vec1;
    CamView=Vec2;
    // Always make Camera Up Vector normalised
    Normalise(Vec3);
    CamUp=Vec3;

    firstcall=true;
};
CCam::~CCam(){
 std::cout <<  "CCam Destructor  \n";
}
/*void  CCam::CamPlace(D3Dvec & NewPos, D3Dvec & NewView, D3Dvec &NewUp){
  CamPos=NewPos;
  CamView=NewView;
  CamUp=NewUp;
}*/

void CCam::CamMove(double speed){

double xp=CamPos.GetX();
double yp=CamPos.GetY();
double zp=CamPos.GetZ();


//cout << " Cam Pos="<<xp<<", "<<yp<<", "<<zp<<" Speed="<<speed<<"\n";

double xv=CamView.GetX();
double yv=CamView.GetY();
double zv=CamView.GetZ();


// for 3d motion
double norm=sqrt( (xv-xp)*(xv-xp)+(yv-yp)*(yv-yp)+(zv-zp)*(zv-zp) );

//for 2d motion
//double norm=sqrt( (xv-xp)*(xv-xp)+(zv-zp)*(zv-zp) );

if( norm >1.e-6){

double speednorm =4.*speed/norm;

D3Dvec Vel((xv-xp)*speednorm, (yv-yp)*speednorm, (zv-zp)*speednorm);

xp=xp+Vel.GetX();
//comment out yp for 2D motion
yp=yp+Vel.GetY();
zp=zp+Vel.GetZ();


xv=xv+Vel.GetX();
//comment out yp for 2D motion
yv=yv+Vel.GetY();
zv=zv+Vel.GetZ();

CamPos.SetVec(xp,yp,zp);
CamView.SetVec(xv,yv,zv);

}
else
{
std::cout <<"view undefined in CamMove, Camera.cpp\n";
exit(0);

}


}
void CCam::CamRotateView(double speed){

//rotate about y azis
//
double xp=CamPos.GetX();
double zp=CamPos.GetZ();

double xv=CamView.GetX();
double zv=CamView.GetZ();

double vx=(xv-xp);
double vz=(zv-zp);

angycum-=speed;
if(angycum > twopi)angycum-=twopi;
if(angxcum < -twopi)angxcum+=twopi;
double CosA=cos(speed);
double SinA=sin(speed);

double vx2=(CosA*vx-SinA*vz);
double vz2=(SinA*vx+CosA*vz);

CamView.SetX(CamPos.GetX()+vx2);
CamView.SetZ(CamPos.GetZ()+vz2);


}
void CCam::CamRotatePos(double speed){

//rotate camera position about stare at point
//
double xp=CamPos.GetX();
double zp=CamPos.GetZ();

double xv=CamView.GetX();
double zv=CamView.GetZ();

double vx=(xp-xv);
double vz=(zp-zv);

//initialise as zero
//compensate total cumulative rotations!

/*angycum-=speed;
if(angycum > twopi)angycum-=twopi;
if(angxcum < -twopi)angxcum+=twopi;*/

double CosA=cos(speed);
double SinA=sin(speed);

double vx2=(CosA*vx-SinA*vz);
double vz2=(SinA*vx+CosA*vz);

CamPos.SetX(CamView.GetX()+vx2);
CamPos.SetZ(CamView.GetZ()+vz2);

}
void CCam::CamStrafe(double speed){

//
D3Dvec  v;
v=CamView;
v-=CamPos;


D3Dvec Perp;
Perp=v*CamUp;   
Normalise(Perp);

CamPos=CamPos-Perp*speed;
CamView=CamView-Perp*speed;
}

void  CCam::MouseView(){
// use mouse to alter the view direction of the camera
int mousex,mousey;
int middlex,middley;
middlex=SCREEN_WIDTH >> 1;
middley=SCREEN_HEIGHT >> 1;
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


angy =-(double)(mousex-middlex)/1000.0;   //rotate about cameras y axis if x changes
angx =(double)(mousey-middley)/1000.0;   //rotate about camera x axis

D3Dvec  v;
v=CamView-CamPos;

// v is a vector from the camera to the stare at point


D3Dvec Perp;
Perp=v*CamUp;  
                          // It's the camera's x axis


Normalise(Perp);
//now Perp and CamUp (x and y at the camera) are normalised

double dotty=CamUp.Dot(v);

              //use vector tripple product instead of cross product
             //  (U dot U) V -(V dot U) U but U is normed

D3Dvec vbar;
vbar=v;
vbar-=CamUp*dotty;                

Normalise(vbar);

//vbar is now unit z vector at camera
double vx=Perp.Dot(v);
double vy=CamUp.Dot(v);
double vz=vbar.Dot(v);

double SinTheta1=sin(angy);
double CosTheta1=cos(angy);
double SinTheta2=sin(angx);
double CosTheta2=cos(angx);

double vnewx=CosTheta1*vx-SinTheta1*vz;
double vnewy=-SinTheta2*SinTheta1*vx+CosTheta2*vy-SinTheta2*CosTheta1*vz;
double vnewz=-CosTheta2*SinTheta1*vx+SinTheta2*vy+CosTheta2*CosTheta1*vz;

CamView=CamPos+Perp*vnewx+CamUp*vnewy+vbar*vnewz;

}

void  CCam::MouseLookAt(){

//use mouse to change the camera position while looking at stare at point

int mousex,mousey;
int middlex,middley;
middlex=SCREEN_WIDTH >> 1;
middley=SCREEN_HEIGHT >> 1;
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

D3Dvec  v;
v=CamPos;
v-=CamView;


D3Dvec Perp;
Perp=v*CamUp;   
                          // It's the camera's x axis

Normalise(Perp);
//now Perp and CamUp (x and y at the camera) are normalised

double dotty=CamUp.Dot(v);

              //use vector tripple product instead of cross product
              //  (U dot U) V -(V dot U) U but U is normed
D3Dvec vbar;
vbar=v;
                 
vbar-=CamUp*dotty;

Normalise(vbar);


double vx=Perp.Dot(v);
double vy=CamUp.Dot(v);
double vz=vbar.Dot(v);
 
double SinTheta1=sin(angy);
double CosTheta1=cos(angy);
double SinTheta2=sin(angx);
double CosTheta2=cos(angx);

//Rotate about y followd by rotate about x
double vnewx=CosTheta1*vx-SinTheta1*vz;
double vnewy=CosTheta2*vy-SinTheta2*(SinTheta1*vx+CosTheta1*vz);
double vnewz=SinTheta2*vy+CosTheta2*(SinTheta1*vx+CosTheta1*vz);

CamPos=CamView+Perp*vnewx+CamUp*vnewy+vbar*vnewz;


}
