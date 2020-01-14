/*
	Assignment- 1- Part 1
	   Swagatam Haldar
		  16EE10063
	       14/1/20
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double hirec(int n);
double lorec(int n);
double* hilorec(int n);
double* hiloformula(int n);

double hirec(int n)
{
	if(n == 0)
		return 1;
	return 2*hirec(n-1) + lorec(n-1);
}

double lorec(int n)
{
	if(n == 0)
		return 0;
	return hirec(n-1) + lorec(n-1);
}

double* hilorec(int n)
{
	double* hilo = new double[2];
	if(n == 0)
	{
		hilo[0] = 1;
		hilo[1] = 0;
		return hilo;
	}
	
	double* hilo_prev = hilorec(n-1);
	double hi, lo;
	
	hi = hilo_prev[0];
	lo = hilo_prev[1];
	
	hilo[0] = 2*hi + lo;
	hilo[1] = hi + lo;
	
	return hilo;
}

double* hiloformula(int n)
{
	double alpha, beta, gamma, delta;
	alpha = (5 + sqrt(5))/10;
	beta = (3 - sqrt(5))/2;
	gamma = (5 - sqrt(5))/10;
	delta = (3 + sqrt(5))/2;
	
	double* hilo = new double[2];
	hilo[0] = alpha * pow(beta,n+1) + gamma * pow(delta,n+1);
	
	alpha = (-5 - 3 * sqrt(5))/10;
	beta = (3 - sqrt(5))/2;
	gamma = (-5 + 3 * sqrt(5))/10;
	delta = (3 + sqrt(5))/2;
	
	hilo[1] = alpha * pow(beta,n+1) + gamma * pow(delta,n+1);
	
	return hilo;
}

int main()
{
	int n = 25;
	cout<<" n = "; cin>>n;
	cout<<"+++ Method 0"<<endl;
	double hi, lo;
	hi = hirec(n); lo = lorec(n);
	//cout.precision(100);
	cout<<"    "<<"hi("<<n<<") = "<<hi<<"\tlo("<<n<<") = "<<lo<<endl;
	cout<<"+++ Method 1"<<endl;
	double *hilo = hilorec(n);
	cout<<"    "<<"hi("<<n<<") = "<<hi<<"\tlo("<<n<<") = "<<lo<<endl;
	cout<<"+++ Method 2"<<endl;
	hilo = hiloformula(n);
	cout<<"    "<<"hi("<<n<<") = "<<hi<<"\tlo("<<n<<") = "<<lo<<endl;
	return 0;
}
