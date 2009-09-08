#include <math.h>
#include <iostream>
using namespace std;
/************************************************************************/
/************************************************************************/
// A simple Triangle class

class Triangle{

public:

	Triangle();
	Triangle(int, int, int);  // sets three node numbers
        Triangle(const Triangle&);      //copy constructor
	~Triangle();

	Triangle& operator=(const Triangle&); 
	Triangle& operator=(const Triangle*); 

	void SetTri( int, int, int);
	void SetTri( int*, int*, int*);

	void Set1(int);  //Set nodes one at a time
	void Set2(int);
	void Set3(int);

	void SetNeighb( int, int, int);
	void SetNeighb(int*, int*, int*);

	void SetN1(int);  //Set nodes one at a time
	void SetN2(int);
	void SetN3(int);

	void SetSplit( int, int, int, int);
	void SetSplit(int*, int*, int*, int*);

	int* GetT() const {return T;}    //get pointer to nodes
	int* GetN() const {return N;}    //get pointer to neighbours
	int* GetS() const {return S;}    //get pointer to four subtriangles

	int Get1();     //Get Nodes
	int Get2();
	int Get3();

	int GetN1();    //get Neighbours
	int GetN2();
	int GetN3();


	int GetS1();    //get triangle numbers of four subtriangles
	int GetS2();
	int GetS3();
	int GetS4();

	// The system of finding neighbours needs to know
	// whether two triangles are in the same quadrant
	// of the upper or lower halves of the octahedron
	char GetQuad() const {return myquad;}
	void SetQuad(char arg) {myquad=arg;}

private:
        int *T;   //points to three node numbers
	int *N;   //points to three triangle numbers
	int *S;   //points to the triangles it has been 
	          //split up into. S=NULL if unsplit;
		  //
	char myquad;

}; 

Triangle::Triangle(){
 T= new int[3];
 *T=0; *(T+1)=0; *(T+2)=0;
 N=NULL; S=NULL;
 myquad='x';
} 
Triangle::Triangle(int arg1, int arg2, int arg3){

 T= new int[3];
 *T = arg1;
 *(T+1) = arg2;
 *(T+2)= arg3;
 N=NULL;  S=NULL;
 myquad='x';

}
Triangle::Triangle(const Triangle &rhs){
 if(!T)T= new int[3];
 if(!N)N= new int[3];
 int* rhsT;  
 int* rhsN;  
 int* rhsS;  
 int rhsquad;

 rhsT=rhs.GetT();
  *T= *rhsT;
  *(T+1)= *(rhsT+1);
  *(T+2)= *(rhsT+2);

 rhsN=rhs.GetN();
  *N= *rhsN;
  *(N+1)= *(rhsN+1);
  *(N+2)= *(rhsN+2);

 if(rhsS){
 rhsS=rhs.GetS();
  *N= *rhsN;
  *(N+1)= *(rhsN+1);
  *(N+2)= *(rhsN+2);
 }
 myquad=rhs.GetQuad();
} 
Triangle::~Triangle(){
   delete T;
   if(N) delete N;
   if(S) delete S;
   T=NULL;
   N=NULL;   S=NULL;

}

void Triangle::SetTri(int arg1, int arg2, int arg3){
 if(!T){ cout << "T is NULL in Triangle::SetTri " << endl; exit(0);}
 *(T) = arg1;
 *(T+1) = arg2;
 *(T+2) = arg3;
 myquad='x';
}
void Triangle::SetTri(int *arg1, int *arg2, int *arg3){
 if(!T){ cout << "T is NULL in Triangle::SetTri " << endl; exit(0);}
 *(T) = *arg1;
 *(T+1) = *arg2;
 *(T+2) = *arg3;
 myquad='x';
}

void Triangle::SetNeighb(int arg1, int arg2, int arg3){
 if(!T){ cout << "T is NULL in Triangle::SetNeighb " << endl; exit(0);}
 if(!N)N=new int[3];
 *(N) = arg1;
 *(N+1) = arg2;
 *(N+2) = arg3;
}
void Triangle::SetNeighb(int *arg1, int *arg2, int *arg3){
 if(!T){ cout << "T is NULL in Triangle::SetNeighb " << endl; exit(0);}
 if(!N)N=new int[3];
 *(N) = *arg1;
 *(N+1) = *arg2;
 *(N+2) = *arg3;
}

void Triangle::SetSplit(int arg1, int arg2, int arg3, int arg4){
 if(!T){ cout << "T is NULL in Triangle::SetSplit" << endl; exit(0);}
 if(!S)S=new int[4];
 *(S) = arg1;
 *(S+1) = arg2;
 *(S+2) = arg3;
 *(S+3) = arg4;
}
void Triangle::SetSplit(int *arg1, int *arg2, int *arg3, int *arg4){
 if(!T){ cout << "T is NULL in Triangle::SetSplit" << endl; exit(0);}
 if(!S)S=new int[3];
 *(S) = *arg1;
 *(S+1) = *arg2;
 *(S+2) = *arg3;
 *(S+3) = *arg4;
}
int Triangle::Get1(){
	if(T){
	      return *(T);
	}
	      else{
		cout << " T Null in Get1 " << endl; exit(0);
      } 
}
int Triangle::Get2(){
	if(T){
	      return *(T+1);}
	      else{
		cout << " T Null in Get2 " << endl; exit(0);
	      } 
}
int Triangle::Get3(){
	if(T){
	      return *(T+2);}
	      else{
		cout << " T Null in Get2 " << endl; exit(0);
	      } 
}

int Triangle::GetN1(){
       	if(N){return *(N);}
		else
	{cout << " N Null in GetN1 " << endl;} exit(0);
}
int Triangle::GetN2(){
       	if(N){return *(N+1);}
		else
	{cout << " N Null in GetN2 " << endl;} exit(0);
}
int Triangle::GetN3(){
       	if(N){return *(N+2);}
		else
	{cout << " N Null in GetN3 " << endl;} exit(0);
}
int Triangle::GetS1(){
       	if(S){return *(S);}
		else
	{cout << " S Null in GetS1 " << endl;} exit(0);
}
int Triangle::GetS2(){
       	if(S){return *(S+1);}
		else
	{cout << " S Null in GetS2 " << endl;} exit(0);
}
int Triangle::GetS3(){
       	if(S){return *(S+2);}
		else
	{cout << " S Null in GetS3 " << endl;} exit(0);
}
int Triangle::GetS4(){
       	if(S){return *(S+3);}
		else
	{cout << " S Null in GetS4 " << endl;} exit(0);
}
void Triangle::Set1(int arg1){
 if(!T){ cout << "T is NULL in Triangle::Set1 " << endl; exit(0);}
 *(T) = arg1;
}
void Triangle::Set2(int arg1){
 if(!T){ cout << "T is NULL in Triangle::Set2 " << endl; exit(0);}
 *(T+1) = arg1;
}
void Triangle::Set3(int arg1){
 if(!T){ cout << "T is NULL in Triangle::Set3 " << endl; exit(0);}
 *(T+2) = arg1;
}

void Triangle::SetN1(int arg1){
 if(!T){ cout << "T is NULL in Triangle::SetN1 " << endl; exit(0);}
 if(!N)N=new int[3];  
 *(N) = arg1;
}
void Triangle::SetN2(int arg1){
 if(!T){ cout << "T is NULL in Triangle::SetN2 " << endl; exit(0);}
 if(!N)N=new int[3];  
 *(N+1) = arg1;
}
void Triangle::SetN3(int arg1){
 if(!T){ cout << "T is NULL in Triangle::SetN3 " << endl; exit(0);}
 if(!N)N=new int[3];  
 *(N+2) = arg1;
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
  int* rhsT;
  int* rhsN;
  int* rhsS;

  rhsT=rhs.GetT();
  rhsN=rhs.GetN();
  rhsS=rhs.GetS();

  if(rhsT){
  if(!T)T=new int[3]; 
  }

  if(rhsN){
  if(!N)N=new int[3];
  }

   if(rhsS){
	   if(!S)S=new int[4]; 
   }
  if(rhsT){

  *T= *rhsT;
  *(T+1)=*(rhsT+1);
  *(T+2)=*(rhsT+2); 
  }

  if(rhsN){
  *N= *rhsN;
  *(N+1)=*(rhsN+1);
  *(N+2)=*(rhsN+2); 
  }
  if(rhsS){
  *S= *rhsS;
  *(S+1)=*(rhsS+1);
  *(S+2)=*(rhsS+2); 
  *(S+3)=*(rhsS+3); 
  }
  myquad=rhs.GetQuad();
}

Triangle& Triangle::operator=(const Triangle* rhs)
{
  if(!T)T=new int[3]; 

  int* rhsT;
  int* rhsN;
  int* rhsS;

  rhsT=rhs->GetT();
  rhsN=rhs->GetN();
  rhsS=rhs->GetS();

  if(rhsN){
  if(!N)N=new int[3];
  }
  if(T){
  *T= *rhsT;
  *(T+1)=*(rhsT+1);
  *(T+2)=*(rhsT+2); 
  }

   if(rhsN){
  *N= *rhsN;
  *(N+1)=*(rhsN+1);
  *(N+2)=*(rhsN+2); 
   }

   if(rhsS){
  *S= *rhsS;
  *(S+1)=*(rhsS+1);
  *(S+2)=*(rhsS+2); 
  *(S+3)=*(rhsS+3); 
   }
  myquad=rhs->GetQuad();
   
   
}
