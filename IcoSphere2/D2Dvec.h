#include <math.h>
#include <iostream>
using namespace std;
/************************************************************************/
/************************************************************************/
// A simple Vector class

class D2Dvec{

public:

	D2Dvec();
	D2Dvec(double , double );
        D2Dvec(const D2Dvec &);      //copy constructor
	~D2Dvec();



	D2Dvec& operator=(const D2Dvec &); 
	D2Dvec& operator=(const D2Dvec *); 

	void Normalise(D2Dvec &);
	double GetMod(const D2Dvec &);

	D2Dvec operator+(const D2Dvec&);
	D2Dvec operator+(const D2Dvec*);
	void operator+=(const D2Dvec&);
	void operator+=(const D2Dvec*);

	D2Dvec operator-(const D2Dvec&);
	void operator-=(const D2Dvec&);
	D2Dvec operator-(const D2Dvec*);
	void operator-=(const D2Dvec*);

	D2Dvec operator*(const double &);
	void operator*=(const double &);

	D2Dvec operator/(const double &);
	void operator/=(const double &);

 //       D2Dvec operator*(const D2Dvec&);
 //       D2Dvec operator*(const D2Dvec*);
        double Dot(const D2Dvec&);  
        double Dot(const D2Dvec*);  

	void SetVec( double, double);
	void SetVec( double*, double*);
	void SetX(double);
	void SetY(double);

	double GetX() const {return *(V);}
	double GetY() const {return *(V+1);}
	double* GetV() const {return V;}

	int CompareEW(D2Dvec*);
	int CompareNS(D2Dvec*);
	int CompareEW(D2Dvec&);
	int CompareNS(D2Dvec&);


private:
        double *V;
}; 

D2Dvec::D2Dvec(){
 V= new double[2];
 *V=0; *(V+1)=0.0;
} 
D2Dvec::D2Dvec(double arg1, double arg2){

 V= new double[2];
 *V = arg1;
 *(V+1) = arg2;

}
D2Dvec::D2Dvec(const D2Dvec &rhs){
 if(!V)V= new double[2];
 double* rhsV;  
 rhsV=rhs.GetV();
  *V= *rhsV;
  *(V+1)= *(rhsV+1);
} 
D2Dvec::~D2Dvec(){
   delete V;
   V=NULL;
}

void D2Dvec::SetVec(double arg1, double arg2){
 if(!V){ cout << "V is NULL in D2Dvec::SetVec " << endl; exit(0);}
 *(V) = arg1;
 *(V+1) = arg2;
}
void D2Dvec::SetVec(double *arg1, double *arg2){
 if(!V){ cout << "V is NULL in D2Dvec::SetVec " << endl; exit(0);}
 *(V) = *arg1;
 *(V+1) = *arg2;
}
void D2Dvec::SetX(double arg1){
 if(!V){ cout << "V is NULL in D2Dvec::SetX " << endl; exit(0);}
 *(V) = arg1;
}
void D2Dvec::SetY(double arg1){
 if(!V){ cout << "V is NULL in D2Dvec::SetY " << endl; exit(0);}
 *(V+1) = arg1;
}
void Normalise(D2Dvec &Vec){

 double x, y;
 double x1, y1;
 double *V;
 V=Vec.GetV();

 x=*(V);
 y=*(V+1);

 //avoid x*x +y*y+z*z-> 0 or Inf if all small or large
 double max;
 max=0.0;
 if( fabs(x) > max)max=fabs(x);
 if( fabs(y) > max)max=fabs(y);

if(max == 0.0)
   { 
   cout << fabs(x) <<  "  " <<  fabs(y)   << "  " << max << endl;
   cout << " Divide by zero in Norm!" << endl;
    exit(1);}

 x1=x/max;
 y1=y/max;

 double modval=max*sqrt(  x1*x1+y1*y1 );

 *V = *V/modval;
 *(V+1) = *(V+1)/modval;

}
double GetMod(D2Dvec &Vec){

 double x, y;
 double x1, y1;
 double *V;
 V=Vec.GetV();

 x=*(V);
 y=*(V+1);

 //avoid x*x +y*y+z*z-> 0 or Inf if all small or large
 double max;
 max=0.0;
 if( fabs(x) > max)max=fabs(x);
 if( fabs(y) > max)max=fabs(y);
 if(max == 0.0)
   { 
	   cout << "Warning, modulus zero " << endl;
	   return max;
    }

 if(max==0.0)return max;

 x1=x/max;
 y1=y/max;


double modval=max*sqrt( x1*x1+y1*y1 );
return modval;

}


D2Dvec& D2Dvec::operator=(const D2Dvec& rhs)
{
  if(!V)V=new double[2]; 
  double* rhsV;
  rhsV=rhs.GetV();
  *V= *rhsV;
  *(V+1)=*(rhsV+1);
}

D2Dvec& D2Dvec::operator=(const D2Dvec* rhs)
{
  if(!V)V=new double[2]; 
  double* rhsV;
  rhsV=rhs->GetV();
  *V= *rhsV;
  *(V+1)=*(rhsV+1);
}
   
double D2Dvec::Dot(const D2Dvec& rhs){
    double *V1,*V2;
    V1=this->GetV();
    V2=rhs.GetV();
    double dot=0.0;

    dot=(*V1)*(*V2)+(*(V1+1))*(*(V2+1));

    return dot;
}

double D2Dvec::Dot(const D2Dvec* rhs){
    double *V1,*V2;
    V1=this->GetV();
    V2=rhs->GetV();
    double dot=0.0;

    dot=(*V1)*(*V2)+(*(V1+1))*(*(V2+1));

    return dot;
}

D2Dvec D2Dvec::operator+(const D2Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 2; i++)
           *(TempV+i)=*(V+i) + *(rhsV+i);

      return Temp;
}
D2Dvec D2Dvec::operator+(const D2Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 2; i++)
           *(TempV+i)=*(V+i) + *(rhsV+i);

      return Temp;
}
D2Dvec D2Dvec::operator-(const D2Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 2; i++)
           *(TempV+i)=*(V+i) - *(rhsV+i);

      return Temp;
}

D2Dvec D2Dvec::operator-(const D2Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 2; i++)
           *(TempV+i)=*(V+i) - *(rhsV+i);

      return Temp;
}

void D2Dvec::operator+=(const D2Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i) + *(rhsV+i);
}

void D2Dvec::operator+=(const D2Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i) + *(rhsV+i);
}

void D2Dvec::operator-=(const D2Dvec& rhs){

      double* rhsV;
      rhsV=rhs.GetV();

      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i) - *(rhsV+i);
}

void D2Dvec::operator-=(const D2Dvec* rhs){

      double* rhsV;
      rhsV=rhs->GetV();

      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i) - *(rhsV+i);
}

D2Dvec D2Dvec::operator*(const double& rhs){

      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();

      for(int i=0; i< 2; i++)
           *(TempV+i)=*(V+i)*rhs;

    return Temp;
}

void D2Dvec::operator*=(const double& rhs){


      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i)*rhs;
}
D2Dvec D2Dvec::operator/(const double& rhs){


      D2Dvec Temp;
      double* TempV;
      TempV=Temp.GetV();


      for( int i=0; i< 2; i++)
           *(TempV+i)=*(V+i)/rhs;
    return Temp;
}

void D2Dvec::operator/=(const double& rhs){

      for(int i=0; i< 2; i++)
           *(V+i)=*(V+i)/rhs;
}


int D2Dvec::CompareEW(D2Dvec *rhs){
	double val=rhs->GetX();
	if(*V <= val )return 0;  //P1 is west of P2
	else
		if(*V==val)return 1; //neither east nor west;
			else
			return 2;  // P1 is east of P2;
}
int D2Dvec::CompareNS(D2Dvec *rhs){
	double val=rhs->GetY();
	if(*(V+1) <= val )return 0;  //P1 is south of P2
	else
		if(*(V+1)== val)return 1;  //neither north nor south
		else
		return 2;  //P1 is north of P2
}

int D2Dvec::CompareEW(D2Dvec &rhs){
	double val=rhs.GetX();
	if( *V <= val )return 0;  //P1 is west of P2
	else
		if(*V==val)return 1;
		else
		return 2;  // P1 is east of P2;
}
int D2Dvec::CompareNS(D2Dvec& rhs){
	double val=rhs.GetY();
	if(*(V+1) <= val )return 0;  //P1 is south of P2
	else
		if(*(V+1)==val)return 1;
		else
		return 2;  //P1 is north of P2
} 
