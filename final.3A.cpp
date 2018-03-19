#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double vCALL(double x, double r);

int main()
{
	int N;	
	N = 16814;					//number of time steps from part 2b
	double t = 0;				//overall time
	
	double delt;				//time step
	delt = 0.1875/N; 			//uniform time spacing over 1.5 periods
	
	double x[2][N];				//positions x and y 
								//--x[0][i] for x and x[1][i] for y
								
	double v[2][N];				//velocities vx and vy
								//-- v[0][i] for vx and v[1][i] for y

	double kx[2][4];			//kx[0][i] for x, kx[1][i] for y
	double kv[2][4];			//kv[0][i] for vx, kv[1][i] for vy

	//initial conditions
	x[0][0] = 0.25;				//x0 = 	0.25	
	v[0][0] = 0;				//vx0 = 0
	x[1][0] = 0;				//y0 = 0
	v[1][0] = (4.0*M_PI);		//vy0 = 4*pi
	
	
	double R;					//vector length at time t
	
	for(int i=0; i<(N+1); i++)
	{
		R = pow((x[0][i]*x[0][i] + x[1][i]*x[1][i]),0.5);
		
		//finding next x and vx
		kx[0][0] = delt*v[0][i];
		kv[0][0] = delt*vCALL(x[0][i], R);
		
		kx[0][1] = delt*(v[0][i] + (0.5 * kv[0][0]));
		kv[0][1] = delt*vCALL((x[0][i] + (0.5 * kx[0][0])), R);
		
		kx[0][2] = delt*(v[0][i] + (0.5 * kv[0][1]));
		kv[0][2] = delt*vCALL((x[0][i] + (0.5 * kx[0][1])), R);
		
		kx[0][3] = delt*(v[0][i] + kv[0][2]);
		kv[0][3] = delt*vCALL((x[0][i] + kx[0][2]), R);
		
		x[0][i+1] = x[0][i] + (1.0/6.0) * (kx[0][0] + 2.0*kx[0][1] + 2.0*kx[0][2] + kx[0][3]);
		v[0][i+1] = v[0][i] + (1.0/6.0) * (kv[0][0] + 2.0*kv[0][1] + 2.0*kv[0][2] + kv[0][3]);
		
		//cout << (i*delt) << "		" << x[i] << endl; 
												//debugging
		//finding next y and vy
		kx[1][0] = delt*v[1][i];
		kv[1][0] = delt*vCALL(x[1][i],R);
		
		kx[1][1] = delt*(v[1][i] + (0.5 * kx[1][0]));
		kv[1][1] = delt*vCALL((x[1][i] + (0.5 * kv[1][0])), R);
		
		kx[1][2] = delt*(v[1][i] + (0.5 * kx[1][1]));
		kv[1][2] = delt*vCALL((x[1][i] + (0.5 * kv[1][1])), R);
		
		kx[1][3] = delt*(v[1][i] + kx[1][2]);
		kv[1][3] = delt*vCALL((x[1][i] + kv[1][2]), R);
		
		x[1][i+1] = x[1][i] + (1.0/6.0) * (kx[1][0] + 2.0*kx[1][1] + 2.0*kx[1][2] + kx[1][3]);
		v[1][i+1] = v[1][i] + (1.0/6.0) * (kv[1][0] + 2.0*kv[1][1] + 2.0*kv[1][2] + kv[1][3]);
		

		
		cout << t << "		" << x[0][i] << endl;		//x vs t
		//cout << x[0][i] << "		" << x[1][i] << endl;	//y vs x
		//cout << t << "		" << R << endl;				//r vs t
		
		t += delt;								
							
	}
	
	
	
	
	return 0;
}


double vCALL(double x, double r)
{
	//takes in x (or y) and returns dv/dt
	double f;
	
	//k = (2*pi)^2
	f = ((-1)*(2.0*M_PI)*(2.0*M_PI)*x) / (r*r*r);
	
	return f;
}
