#include <iostream>
#include <math.h>
using namespace std;
int main(){

	double theta,pi,psi;


	pi=acos(-1.0);

	theta=45.0/64.;  //degrees
	theta=theta/180.0*pi;
       
	psi=26.57;
        psi=psi*pi/180.0;

	/*
	  cout << " alpha=" << tan(psi)/tan(theta) <<endl;
	cout << " alpha prime=" 
	       << sin(psi)/( 2.0*sin(theta/2.0)*cos(psi-theta/2.0) ) << endl;
	       */

	double ratio;
        for(int i=0; i<21; i++){

		psi=theta/20.0*( (double)i);
		if(i==0.0)psi=1./100000000.0;
		ratio=
		sin(psi)/( 2.0*sin(theta/2.0)*cos(psi-theta/2.0) );
		


                cout << "angle degrees=" << psi*180./pi 
			<< " error in degrees=" << (ratio*theta-psi)*180./pi
		       	<< " error in km=" << (ratio*theta-psi)*6380.0 << endl;
	}



	return 0;
}