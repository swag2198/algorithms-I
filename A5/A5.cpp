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
	double **T;
	int **mc;
	T = new double*[n];
	mc = new int*[n];
	double *count = new double[n];
	for(int i=0; i<n; i++)
	{
		T[i] = new double[C+1];
		mc[i] = new int[C+1];
		count[i] = 0;
	}
	
	
	int m, mi;
	double curmax = minus_inf, curp;
	for(int j=0; j<=C; j++)
	{
		
		if(j < c[0] || j == 0)
			T[0][j] = minus_inf;
		else
		{
			m = j / c[0];
			double cost = e(p,s,t,0,m);
			T[0][j] = cost;
			mc[0][j] = m;
		}
	}
	
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=C; j++)
		{
			if(j == 0 || j < c[i])
				T[i][j] = minus_inf;
			else
			{
				m = j / c[i];
				curmax = minus_inf;
				for(mi = 1; mi <= m; mi++)
				{
					if(j - mi*c[i] < 0)
						continue;
					curp = e(p,s,t,i,mi) + T[i-1][j-mi*c[i]];
					if(curp > curmax)
					{
						T[i][j] = curp;
						mc[i][j] = mi;
						curmax = curp;
					}
				}
			}
		}
	}
	int maxind, curC;
	curC = C;
	for(int i=n-1; i>=0; i--)
	{
		if(i == 0)
		{
			count[i] = curC / c[i];
		}
		else
		{
			curmax = minus_inf;
			m = curC / c[i];
			for(int mi = 1; mi <= m; mi++)
			{
				curp = T[i-1][curC - mi*c[i]] + e(p,s,t,i,mi);
				if(curp > curmax)
				{
					curmax = curp;
					maxind = mi;
				}
			}
			count[i] = maxind;
			curC -= maxind * c[i];
		}
	}

	/*curmax = minus_inf;
	count[n-1] = mc[n-1][C];
	int ic = count[n-1], iC = C;
	for(int i=n-2; i>=0; i--)
	{
		count[i] = mc[i][iC - ic*c[i+1]];
		// cout<<"count "<<i<<" = "<<count[i]<<endl;
		iC = iC - ic*c[i+1];
		ic = count[i];
		// cout<<"iC = "<<iC<<endl;
	}*/
	
	int total_buy = 0;
	for(int i=0; i<n; i++)
	{
		cout<<"    Machine "<<i<<":\t"<<count[i]<<" copies, cost =\t"<<count[i] * c[i]<<endl;
		total_buy += count[i] * c[i];
	}
	cout<<"--- Total Buying Cost = "<<total_buy<<endl;
	cout<<"--- Expected Total Profit = "<<T[n-1][C]<<endl;
	
}

void optimalbuy2(int n, int C, int *c, double *s, double *t, double *r, double *p, double *q)
{
	double **T;
	T = new double*[n];
	int *count = new int[n];
	int *isrep = new int[n];
	for(int i=0; i<n; i++)
	{
		T[i] = new double[C+1];
		count[i] = 0;
	}
	
	
	int m, mi;
	double curmax = minus_inf, curp, curp2, pf, pfr;
	for(int j=0; j<=C; j++)
	{
		
		if(j < c[0] || j == 0)
			T[0][j] = minus_inf;
		else
		{
			m = j / c[0];
			pf = e(p,s,t,0,m);
			pfr = e(q,s,t,0,m) - m*r[0];
			T[0][j] = max(pf, pfr);
		}
	}
	
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=C; j++)
		{
			if(j == 0 || j < c[i])
				T[i][j] = minus_inf;
			else
			{
				m = j / c[i];
				curmax = minus_inf;
				for(mi = 1; mi <= m; mi++)
				{
					if(j - mi*c[i] < 0)
						continue;
					curp = e(p,s,t,i,mi) + T[i-1][j-mi*c[i]];
					curp2 = e(q,s,t,i,mi) + T[i-1][j-mi*c[i]] - mi*r[i];
					if(curp > curmax && curp > curp2)
					{
						T[i][j] = curp;
						curmax = curp;
					}
					else if(curp2 > curmax && curp2 > curp)
					{
						T[i][j] = curp2;
						curmax = curp2;
					}
				}
			}
		}
	}
	int maxind, curC;
	curC = C;
	for(int i=n-1; i>=0; i--)
	{
		if(i == 0)
		{
			count[i] = curC / c[i];
		}
		else
		{
			curmax = minus_inf;
			m = curC / c[i];
			for(int mi = 1; mi <= m; mi++)
			{
				curp = T[i-1][curC - mi*c[i]] + e(p,s,t,i,mi);
				curp2 = e(q,s,t,i,mi) + T[i-1][curC - mi*c[i]] - mi*r[i];
				if(curp > curmax && curp > curp2)
				{
					curmax = curp;
					maxind = mi;
					isrep[i] = 0;
				}
				else if(curp2 > curmax && curp2 > curp)
				{
					curmax = curp2;
					maxind = mi;
					isrep[i] = 1;
				}
			}
			count[i] = maxind;
			curC -= maxind * c[i];
		}
	}

	/*curmax = minus_inf;
	count[n-1] = mc[n-1][C];
	int ic = count[n-1], iC = C;
	for(int i=n-2; i>=0; i--)
	{
		count[i] = mc[i][iC - ic*c[i+1]];
		// cout<<"count "<<i<<" = "<<count[i]<<endl;
		iC = iC - ic*c[i+1];
		ic = count[i];
		// cout<<"iC = "<<iC<<endl;
	}*/
	
	int total_buy = 0;
	for(int i=0; i<n; i++)
	{
		if(isrep[i] == 0)
		{
			cout<<"    Machine "<<i<<":\t"<<count[i]<<" copies, cost =    "<<count[i] * c[i]<<"    [Maint not Needed]"<<endl;
			total_buy += count[i] * c[i];
		}
		else
		{
			cout<<"    Machine "<<i<<":\t"<<count[i]<<" copies, cost =    "<<count[i] * c[i]<<"    [Maint. Needed]"<<endl;
			total_buy += count[i] * c[i];
		}

		

	}
	cout<<"--- Total Buying Cost = "<<total_buy<<endl;
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
	
	cout<<endl<<"+++ Part1: Best Buying Option"<<endl;
	optimalbuy1(n,C,c,s,t,p);

	cout<<endl<<"+++ Part2: Best Buying Option"<<endl;
	optimalbuy2(n,C,c,s,t,r,p,q);
	
	return 0;
}
