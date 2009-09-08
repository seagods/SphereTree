#include <math.h>
#include <iostream>
using namespace std;
/************************************************************************/
/************************************************************************/
// A simple Vector class

class D3Dvec{

public:

	D3Dvec();
	D3Dvec(double , double , double );
        D3Dvec(const D3Dvec &);      //copy constructor
	~D3Dvec();



	D3Dvec& operator=(const D3Dvec &); 
	D3Dvec& operator=(const D3Dvec *); 

	void Normalise(D3Dvec &);
	void Normalise(D3Dvec *);
	double GetMod(const D3Dvec &);

	D3Dvec operator+(const D3Dvec&);
	D3Dvec operator+(const D3Dvec*);
	void operator+=(const D3Dvec&);
	void operator+=(const D3Dvec*);

	D3Dvec operator-(const D3Dvec&);
	void operator-=(const D3Dvec&);
	D3Dvec operator-(const D3Dvec*);
	void operator-=(const D3Dvec*);

	D3Dvec operator*(const double &);
	void operator*=(const double &);

	D3Dvec operator/(const double &);
	void operator/=(const double &);

        D3Dvec operator*(const D3Dvec&);
        D3Dvec operator*(const D3Dvec*);
        double Dot(const D3Dvec&);  
        double Dot(const D3Dvec*);  

	void SetVec( double, double, double);
	void SetVec( double*, double*, double*);
	void SetX(double);
	void SetY(double);
	void SetZ(double);

	double GetX() const {return *(V);}
	double GetY() const {return *(V+1);}
	double GetZ() const {return *(V+2);}
	double* GetV() const {return V;}

	int CompareEW(D3Dvec*);
	int CompareNS(D3Dvec*);
	int CompareUD(D3Dvec*);
	int CompareEW(D3Dvec&);
	int CompareNS(D3Dvec&);
	int CompareUD(D3Dvec&);


private:
        double *V;
}; 

D3Dvec::D3Dvec(){
 V= new double[3];
 *V=0; *(V+1)=0.0; *(V+2)=0;
} 
D3Dvec::D3Dvec(double arg1, double arg2, double arg3){

 V= new double[3];
 *V = arg1;
 *(V+1) = arg2;
 *(V+2)= arg3;

}
D3Dvec::D3Dvec(const D3Dvec &rhs){
 if(!V)V= new double[3];
 double* rhsV;  
 rhsV=rhs.GetV();
  *V= *rhsV;
  *(V+1)= *(rhsV+1);
  *(V+2)= *(rhsV+2);
} 
D3Dvec::~D3Dvec(){
   delete V;
   V=NULL;
}

void D3Dvec::SetVec(double arg1, double arg2, double arg3){
 if(!V){ cout << "V is NULL in D3Dvec::SetVec " << endl; exit(0);}
 *(V) = arg1;
 *(V+1) = arg2;
 *(V+2) = arg3;
}
void D3Dvec::SetVec(double *arg1, double *arg2, double *arg3){
 if(!V){ cout << "V is NULL in D3Dvec::SetVec " << endl; exit(0);}
 *(V) = *arg1;
 *(V+1) = *arg2;
 *(V+2) = *arg3;
}
void D3Dvec::SetX(double arg1){
 if(!V){ cout << "V is NULL in D3Dvec::SetX " << endl; exit(0);}
 *(V) = arg1;
}
void D3Dvec::SetY(double arg1){
 if(!V){ cout << "V is NULL in D3Dvec::SetY " << endl; exit(0);}
 *(V+1) = arg1;
}
void D3Dvec::SetZ(double arg1){
 if(!V){ cout << "V is NULL in D3Dvec::SetZ " << endl; exit(0);}
 *(V+2) = arg1;
}

void Normalise(D3Dvec &Vec){

 double x, y, z;
 double x1, y1, z1;
 double *V;
 V=Vec.GetV();

 x=*(V);
 y=*(V+1);
 z=*(V+2);

 //avoid x*x +y*y+z*z-> 0 or Inf if all small or large
 double max;
 max=0.0;
 if( fabs(x) > max)max=fabs(x);
 if( fabs(y) > max)max=fabs(y);
 if( fabs(z) > max)max=fabs(z);

if(max == 0.0)
   { 
   cout << fabs(x) <<  "  " <<  fabs(y)  << "  " << fabs(z) << "  " << max << endl;
   cout << " Divide by zero in Norm!" << endl;
    exit(1);}

 x1=x/max;
 y1=y/max;
 z1=z/max;

 double modval=max*sqrt(  x1*x1+y1*y1+z1*z1 );

 *(V) = *(V)/modval;
 *(V+1) = *(V+1)/modval;
 *(V+2) = *(V+2)/modval;

}

void Normalise(D3Dvec *Vec){

 double x, y, z;
 double x1, y1, z1;
 double *V;
 V=Vec->GetV();

 x=*(V);
 y=*(V+1);
 z=*(V+2);

 //avoid x*x +y*y+z*z-> 0 or Inf if all small or large
 double max;
 max=0.0;
 if( fabs(x) > max)max=fabs(x);
 if( fabs(y) > max)max=fabs(y);
 if( fabs(z) > max)max=fabs(z);

if(max == 0.0)
   { 
   cout << fabs(x) <<  "  " <<  fabs(y)  << "  " << fabs(z) << "  " << max << endl;
   cout << " Divide by zero in Norm!" << endl;
    exit(1);}

 x1=x/max;
 y1=y/max;
 z1=z/max;

 double modval=max*sqrt(  x1*x1+y1*y1+z1*z1 );

 *(V) = *(V)/modval;
 *(V+1) = *(V+1)/modval;
 *(V+2) = *(V+2)/modval;
}

double GetMod(D3Dvec &Vec){

 double x, y, z;
 double x1, y1, z1;
 double *V;
 V=Vec.GetV();

 x=*(V);
 y=*(V+1);
 z=*(V+2);

 //avoid x*x +y*y+z*z-> 0 or Inf if all small or large
 double max;
 max=0.0;
 if( fabs(x) > max)max=fabs(x);
 if( fabs(y) > max)max=fabs(y);
 if( fabs(z) > max)max=fabs(z);

 if(max==0.0){
	 cout <<" Warning, modulus zero! " << endl;
	 return max;
 }

 x1=x/max;
 y1=y/max;
 z1=z/max;


double modval=max*sqrt( x1*x1+y1*y1+z1*z1 );
return modval;

}


D3Dvec& D3Dvec::operator=(const D3Dvec& rhs)
{
  if(!V)V=new double[3]; 
  double* rhsV;
  rhsV=rhs.GetV();
  *V= *rhsV;
  *(V+1)=*(rhsV+1);
  *(V+2)=*(rhsV+2); 
}

D3Dvec& D3Dvec::operator=(const D3Dvec* rhs)
{
  if(!V)V=new double[3]; 
  double* rhsV;
  rhsV=rhs->GetV();
  *V= *rhsV;
  *(V+1)=*(rhsV+1);
  *(V+2)=*(rhsV+2); 
}

D3Dvec D3Dvec::operator*(const D3Dvec & rhs){

   double ex,why,zed, x, y, z;
   x=this->GetX(); y=this->GetY(); z=this->GetZ();
   ex=rhs.GetX(); why=rhs.GetY(); zed=rhs.GetZ();


   D3Dvec Temp; 
   double* TempV;

   TempV=Temp.GetV();
   
   *TempV=y*zed-z*why;
   *(TempV+1)=-(x*zed-z*ex);
   *(TempV+2)=x*why-y*ex;
   
   return Temp;
}

D3Dvec D3Dvec::operator*(const D3Dvec * rhs){

   double ex,why,zed, x, y, z;

   x=this->GetX(); y=this->GetY(); z=this->GetZ();
   ex=rhs->GetX(); why=rhs->GetY(); zed=rhs->GetZ();

   D3Dvec Temp; 
   double* TempV;

   TempV=Temp.GetV();
   
   *TempV=y*zed-z*why;
   *(TempV+1)=-(x*zed-z*ex);
   *(TempV+2)=x*why-y*ex;
   
   return Temp; 
}
   
double D3Dvec::Dot(const D3Dvec& rhs){
    double *V1,*V2;
    V1=this->GetV();
    V2=rhs.GetV();
    double dot=0.0;

    dot=(*V1)*(*V2)+(*(V1+1))*(*(V2+1))+(*(V1+2))*(*(V2+2));

    return dot;
}

double D3Dvec::Dot(const D3Dvec* rhs){
    double *V1,*V2;
    V1=this->GetV();
    V2=rhs->GetV();
    double dot=0.0;

    dot=(*V1)*(*V2)+(*(V1+1))*(*(V2+1))+(*(V1+2))*(*(V2+2));

    return dot;
}

D3Dvec D3Dvec::operator+(const D3Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 3; i++)
           *(TempV+i)=*(V+i) + *(rhsV+i);

      return Temp;
}
D3Dvec D3Dvec::operator+(const D3Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 3; i++)
           *(TempV+i)=*(V+i) + *(rhsV+i);

      return Temp;
}
D3Dvec D3Dvec::operator-(const D3Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 3; i++)
           *(TempV+i)=*(V+i) - *(rhsV+i);

      return Temp;
}

D3Dvec D3Dvec::operator-(const D3Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 3; i++)
           *(TempV+i)=*(V+i) - *(rhsV+i);

      return Temp;
}

void D3Dvec::operator+=(const D3Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i) + *(rhsV+i);
}

void D3Dvec::operator+=(const D3Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i) + *(rhsV+i);
}

void D3Dvec::operator-=(const D3Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i) - *(rhsV+i);
}

void D3Dvec::operator-=(const D3Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i) - *(rhsV+i);
}

D3Dvec D3Dvec::operator*(const double& rhs){

      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 3; i++)
           *(TempV+i)=*(V+i)*rhs;

    return Temp;
}

void D3Dvec::operator*=(const double& rhs){


      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i)*rhs;
}
D3Dvec D3Dvec::operator/(const double& rhs){


      D3Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();


      for( int i=0; i< 3; i++)
           *(TempV+i)=*(V+i)/rhs;
    return Temp;
}

void D3Dvec::operator/=(const double& rhs){

      for(int i=0; i< 3; i++)
           *(V+i)=*(V+i)/rhs;
}


int D3Dvec::CompareEW(D3Dvec *rhs){
	double val=rhs->GetX();
	if(*V <= val )return 0;  //P1 is west of P2
	else
		if(*V==val)return 1; //neither east nor west;
			else
			return 2;  // P1 is east of P2;
}
int D3Dvec::CompareNS(D3Dvec *rhs){
	double val=rhs->GetY();
	if(*(V+1) <= val )return 0;  //P1 is south of P2
	else
		if(*(V+1)== val)return 1;  //neither north nor south
		else
		return 2;  //P1 is north of P2
}
int D3Dvec::CompareUD(D3Dvec *rhs){
	double val=rhs->GetZ();
	if(*(V+2) <= val )return 0;  //P1 is lower than P2
	else
		if(*(V+2)== val)return 1;  //neither 
		else
		return 2;  //P1 is higher of P2
}
int D3Dvec::CompareEW(D3Dvec &rhs){
	double val=rhs.GetX();
	if( *V <= val )return 0;  //P1 is west of P2
	else
		if(*V==val)return 1;
		else
		return 2;  // P1 is east of P2;
}
int D3Dvec::CompareNS(D3Dvec& rhs){
	double val=rhs.GetY();
	if(*(V+1) <= val )return 0;  //P1 is south of P2
	else
		if(*(V+1)==val)return 1;
		else
		return 2;  //P1 is north of P2
} 
int D3Dvec::CompareUD(D3Dvec & rhs){
	double val=rhs.GetZ();
	if(*(V+2) <= val )return 0;  //P1 is lower than P2
	else
		if(*(V+2)==val)return 1;
		else
		return 2;  //P1 is higher than P2
}
