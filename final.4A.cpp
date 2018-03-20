#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

double vCALL(double x, double r);

int main()
{
	ofstream file_out;
	file_out.open("final.4A.data1.txt");
	
	if(file_out.fail())
	{
		cout << "Error opening file. Exiting..." << endl;
	}
	
	int N;	
	double delt;				//time step
	
	delt = 0.000011151; 	//uniform time spacing from number 3
	N = 60000;				//number of time steps =627,722
							//program breaks for N > 60,000
	
	double t = 0;				//overall time goes from t=0 to t=7
	
	double x[2][N];				//positions x and y 
								//	x[0][i] for x and x[1][i] for y
								
	double v[2][N];				//velocities vx and vy
								//	v[0][i] for vx and v[1][i] for y
								
	double vel;					//overall velocity calculated from
								//	vx and vy

	double kx[2][4];			//kx[0][i] for x, kx[1][i] for y
	double kv[2][4];			//kv[0][i] for vx, kv[1][i] for vy

	//initial conditions
	x[0][0] = 0.25;				//x0 = 	0.25	
	v[0][0] = 0;				//vx0 = 0
	x[1][0] = 0;				//y0 = 0
	v[1][0] = (6.0*M_PI);		//vy0 = 6*pi
	
	
	double R;					//vector length at time t
	
	int count=0;				//needed because of array size limitation
	int count2=0;				//debugging
	do
	{
		for(int i=0; i<60000; i++)
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
			
			//file_out << "count: " << count << endl;	//debugging
			
			//calculating total velocity from vx and vy
			vel = pow(((v[0][i]*v[0][i]) + (v[1][i]*v[1][i])),(0.5));
			
			//file_out << t << "		" << x[0][i] << endl;		//x vs t
			//file_out << x[0][i] << "		" << x[1][i] << endl;	//y vs x
			//file_out << t << "		" << R << endl;				//r vs t
			file_out << t << "		" << vel << endl;				//v vs t
			
			t += delt;
			count2++;														
		}
		
		//because of limitation on array size (program breaks when 
		//	N>60,000 for some reason), initial conditions will be 
		//	changed to the last calculated value in the above arrays,
		//	and arrays will be recalculated to continue up to N=627,722
		
		x[0][0] = x[0][59999];					
		v[0][0] = v[0][59999];				
		x[1][0] = x[1][59999];				
		v[1][0] = v[1][59999];		
		
		count++;
	}
	while(count < 10);
	
	//the do-while loop has now looped over 600,000 of the N=627,722 
	//	points. now all that is needed is to loop over the remaining 
	//	27,722 points
	
	x[0][0] = x[0][59999];					
	v[0][0] = v[0][59999];				
	x[1][0] = x[1][59999];				
	v[1][0] = v[1][59999];
	
	for(int i=0; i<27722; i++)
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
		
		//file_out << "count: " << count << endl;	//debugging
		
		//calculating total velocity from vx and vy
		vel = pow(((v[0][i]*v[0][i]) + (v[1][i]*v[1][i])),(0.5));
		
		//file_out << t << "		" << x[0][i] << endl;		//x vs t
		//file_out << x[0][i] << "		" << x[1][i] << endl;	//y vs x
		//file_out << t << "		" << R << endl;				//r vs t
		file_out << t << "		" << vel << endl;				//v vs t
		
		t += delt;
		count2++;
	}
	
	
	//file_out << count2 << endl;		//dubugging
	
	file_out.close();
	
	//_____________________________________________________________
	//ACCORDING TO CALCULATION FROM THIS CODE, OUMUAMUA WILL CROSS
	//	THE ORBIT OF PLUTO (40 AU) AT APPROXIMATELY t = 5.748 YEARS.
	//_____________________________________________________________
	
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
