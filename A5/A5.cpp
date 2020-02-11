//16EE10063, Swagatam Haldar
#include <iostream>
#include <cmath>
#include <limits>

const double minus_inf = -std::numeric_limits<double>::max();

using namespace std;

double e(double *p, double* s, double *t, int i, int mi)
{
	double ei = 0;
	double pi = pow(p[i], mi);
	ei = (1 - pi) * s[i] + pi * t[i];
	return ei;
}

double optimalbuy1(int n, int C, int *c, double *s, double *t, double *p)
{
	double **T, **mc;
	T = new double*[n];
	mc = new double*[n];
	double *count = new double[n];
	for(int i=0; i<n; i++)
	{
		T[i] = new double[C+1];
		mc[i] = new double[C+1];
		count[i] = 0;
	}
	
	
	int m, mi;
	double curmax = minus_inf, curp;
	for(int j=0; j<=C; j++)
	{
		
		if(j < c[0] ||j == 0)
			T[0][j] = minus_inf;
		else
		{
			m = j / c[0];
			double cost = e(p,s,t,0,m);
			T[0][j] = cost;
			mc[0][j] = m;
			count[0] = m;
			/*if(cost > curmax)
			{
				T[0][j] = cost;
				count[0] = m;
				curmax = cost;
				cout<<"Curmax cost of 0 = "<<curmax<<endl;
			}
			else
				T[0][j] = curmax;*/
		}
	}
	
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=C; j++)
		{
			//cout<<"Dealing with i = "<<i<<"j = "<<j<<endl;
			if(j == 0 || j < c[i])
				T[i][j] = minus_inf;
			else
			{
				m = j / c[i];
				//cout<<"mmax = "<<m;
				curmax = minus_inf;
				//cout<<"mmax = "<<m;
				for(mi = 1; mi <= m; mi++)
				{
					//cout<<"Processing mi = "<<mi<<endl;
					if(j - mi*c[i] < 0)
						continue;
					curp = e(p,s,t,i,mi) + T[i-1][j-mi*c[i]];
					if(curp > curmax)
					{
						T[i][j] = curp;
						mc[i][j] = mi;
						if(i == 1)
						{
							mc[i-1][j] = 
						}
						count[i] = mi;
						curmax = curp;
					}
				}
			}
		}
	}
	curmax = minus_inf;
	count[n-1] = mc[n-1][C];
	double prof = T[n-1][C], pe;
	int mmax;
	for(int i=n-1; i>0; i--)
	{
		
	}
	
	int total_b = 0;
	for(int i=0; i<n; i++)
	{
		cout<<"   Machine "<<i<<":\t"<<count[i]<<" copies, cost =\t"<<count[i] * c[i]<<endl;
		total_b += count[i] * c[i];
	}
	cout<<"--- Total Buying Cost = "<<total_b<<endl;
	cout<<"--- Expected Total Profit = "<<T[n-1][C]<<endl;
	
}

double optimalbuy2(int n, int C, int *c, double *s, double *t, double *r, double *p, double *q)
{
	double **T, **mc;
	T = new double*[n];
	mc = new double*[n];
	double *count = new double[n];
	for(int i=0; i<n; i++)
	{
		T[i] = new double[C+1];
		mc[i] = new double[C+1];
		count[i] = 0;
	}
	
	
	int m, mi;
	double curmax = minus_inf, curp;
	for(int j=0; j<=C; j++)
	{
		
		if(j < c[0] ||j == 0)
			T[0][j] = minus_inf;
		else
		{
			m = j / c[0];
			double cost = e(p,s,t,0,m);
			T[0][j] = cost;
			mc[0][j] = m;
			count[0] = m;
			/*if(cost > curmax)
			{
				T[0][j] = cost;
				count[0] = m;
				curmax = cost;
				cout<<"Curmax cost of 0 = "<<curmax<<endl;
			}
			else
				T[0][j] = curmax;*/
		}
	}
	
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=C; j++)
		{
			//cout<<"Dealing with i = "<<i<<"j = "<<j<<endl;
			if(j == 0 || j < c[i])
				T[i][j] = minus_inf;
			else
			{
				m = j / c[i];
				//cout<<"mmax = "<<m;
				curmax = minus_inf;
				//cout<<"mmax = "<<m;
				for(mi = 1; mi <= m; mi++)
				{
					//cout<<"Processing mi = "<<mi<<endl;
					if(j - mi*c[i] < 0)
						continue;
					curp = e(p,s,t,i,mi) + T[i-1][j-mi*c[i]];
					if(curp > curmax)
					{
						T[i][j] = curp;
						mc[i][j] = mi;
						count[i] = mi;
						curmax = curp;
					}
				}
			}
		}
	}
	curmax = minus_inf;
	double prof = T[n-1][C], pe;
	
	int total_b = 0;
	for(int i=0; i<n; i++)
	{
		cout<<"   Machine "<<i<<":\t"<<count[i]<<" copies, cost =\t"<<count[i] * c[i]<<endl;
		total_b += count[i] * c[i];
	}
	cout<<"--- Total Buying Cost = "<<total_b<<endl;
	cout<<"--- Expected Total Profit = "<<T[n-1][C]<<endl;
	
}

int main()
{
	int n, C;
	//cout<<"n = "; 
	cin>>n;
	//cout<<"Capital (C) = ";
	cin>>C;
	int *m, *c;
	double *s, *t, *r, *p, *q;
	m = new int[n];
	c = new int[n];
	s = new double[n];
	t = new double[n];
	r = new double[n];
	p = new double[n];
	q = new double[n];
	
	//cout<<"Give costs (c) = ";
	for(int i=0; i<n; i++)
		cin>>c[i];
	//cout<<"Give Selling Prices (s) = ";
	for(int i=0; i<n; i++)
		cin>>s[i];
	//cout<<"Give reduced Selling Prices (t) = ";
	for(int i=0; i<n; i++)
		cin>>t[i];
	//cout<<"Give maintenance costs (r) = ";
	for(int i=0; i<n; i++)
		cin>>r[i];
	//cout<<"Probabilities (p) = ";
	for(int i=0; i<n; i++)
		cin>>p[i];
	//cout<<"Probabilities (q) = ";
	for(int i=0; i<n; i++)
		cin>>q[i];
	
	cout<<"+++ Part1: Best Buying Option"<<endl;
	optimalbuy1(n,C,c,s,t,p);
	
	return 0;
}
