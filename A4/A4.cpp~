//Swagatam Haldar, 16EE10063, Assignment- 4, 4/2/2020

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int greedy1(int n)
{
	int count = 0;
	cout<<"Start: "<<n<<endl;
	while(n != 1)
	{
		if(n % 2 == 0)
		{
			n = n / 2;
			cout<<"Divide: "<<n<<endl;
			count++;
		}
		else
		{
			n--;
			cout<<"Decrement: "<<n<<endl;
			count++;
		}
	}
	return count;
}

int powersof2(int n)
{
	int count = 0;
	while(n % 2 == 0)
	{
		n = n/2;
		count++;
	}
	return count;
}

int greedy2(int n)
{
	int count = 0, lo, hi;
	double lofac, hifac;
	cout<<"Start: "<<n<<endl;
	while(n != 1)
	{
		if(n % 2 == 0)
		{
			n = n / 2;
			cout<<"Divide: "<<n<<endl;
			count++;
		}
		else if(n != 3)
		{
			lo = n-1;
			hi = n+1;
			lofac = powersof2(lo);
			hifac = powersof2(hi);
			//cout<<"n = "<<n<<" lofac = "<<lofac<<" hifac = "<<hifac<<endl;
			if(lofac >= hifac)
			{
				n--;
				cout<<"Decrement: "<<n<<endl;
				count++;
			}
			else
			{
				n++;
				cout<<"Increment: "<<n<<endl;
				count++;
			}
		}
		else
		{
			n--;
			cout<<"Decrement: "<<n<<endl;
			count++;
		}
	}
	return count;
}

int find(vector<int> &a, int key)
{
	int flag = -1;
	for(int i=0; i<a.size(); i++)
	{
		if(a[i] == key)
			return 1;
	}
	return -1;
}

int greedy3(int n, int k, int *A)
{
	int count = 0, val, valk;
	double facs, maxfacs;
	vector<int> a;
	a.push_back(n);
	cout<<"Start: "<<n<<endl;
	while(n != 1)
	{
		if(n % 2 == 0)
		{
			n = n / 2;
			cout<<"Divide: "<<n<<endl;
			a.push_back(n);
			count++;
		}
		else
		{
			maxfacs = -1;
			val = 100000000;
			for(int i=0; i<k; i++)
			{
				int x = n + A[i];
				if(n + A[i] > 0 && find(a,n+A[i]) == -1)
				{
					facs = powersof2(n + A[i]);
					//cout<<"Facs = "<<facs<<endl;
					if(facs > maxfacs)
					{
						//cout<<"maxcs = "<<maxfacs<<endl;
						maxfacs = facs;
						val = n + A[i];
						valk = i;
					}
					else if(facs == maxfacs)
					{
						if(n + A[i] < val)
						{
							val = n + A[i];
							valk = i;
						}
					}
					//cout<<"val = "<<val<<endl;
				}
			}
			n = val;
			a.push_back(n);
			cout<<"Increment "<<A[valk]<<": "<<n<<endl;
			count++;
		}
	}
	return count;
}

int B(int n, int k, int *A, int adds, int maxadds, vector<int> &T)
{
	if(T[n] != 0)
		return T[n];
	if(adds >= maxadds)
	{
		T[n] = 1000000;
		return T[n];
	}
	double p, pf;
	p = log2(n);
	pf = floor(p);
	if(p == pf)
	{
		T[n] = p;
		return T[n];
	}
	//cout<<"n = "<<n<<endl;
	vector<int> b;
	if(n % 2 == 0)
		b.push_back(B(n/2,k,A,adds,maxadds, T));
	for(int i=0; i<k; i++)
		b.push_back(B(n+A[i], k, A, adds+1, maxadds, T));
		
	int min = b[0];
	for(int i=1; i<b.size(); i++)
	{
		if(b[i] < min)
		{
			min = b[i];
			int mini = i;
		}
	}
	if(n == 1596)
	{
		//cout<<"i = "<<i<<endl;
	}
	T[n] = 1 + min;
	return T[n];
}

int optimal(int n, int k, int *A)
{
	int count = 0;
	cout<<"Start: "<<n<<endl;
	int minsteps, mini, cursteps, curn;
	double maxadds = ceil(log2(n));
	double p, pf;
	vector<int> T(n+1000);
	return B(n, k, A, 0, maxadds, T);
	
	/*vector<int> B;
	for(int i=2; i<m; i++)
	{
		if(i % 2 == 0)
	}
	
	while(n != 1)
	{
		minsteps = 1000000;
		p = log2(n);
		pf = floor(p);
		else
		{
			if(n % 2 == 0)
			{
				for(int i=0; i<k; i++)
				{
					curn = n + A[i];
					p = log2(curn);
					pf = floor(p);
					m = ceil(log2(n));
					cursteps = 1;
					if(p == pf)
					{
						cursteps += p;
						if(cursteps < minsteps)
						{
							minsteps = cursteps;
							
						}
					}
					while(m--)
					{
						curn += A[i];
						cur
					}
				}
			}	
			
		}
		
		for(int i=0; i<k; i++)
		{
			if(A[i] >= 2 && A[i] <= m)
			{ 
				curn = n + A[i];
				cursteps = 1;
				while(curn < m)
				{
					curn += A[i];
					cursteps++;
				}
				if(cursteps < minsteps)
				{
					minsteps = cursteps;
					mini = i;
				}
			}
		}
	}*/
	
}

int main()
{
	int n, k, *A;
	cout<<"n = "; cin>>n;
	cout<<endl<<"+++ Greedy 1"<<endl;
	cout<<"Number of Steps = "<<greedy1(n)<<endl;
	
	cout<<endl<<"+++ Greedy 2"<<endl;
	cout<<"Number of Steps = "<<greedy2(n)<<endl;
	
	cout<<"k = "; cin>>k;
	cout<<"Give "<<k<<" small nums = ";
	A = new int[k];
	for(int i=0; i<k; i++)
		cin>>A[i];
	/*for(int i=0; i<k; i++)
		cout<<A[i]<<",";
	cout<<endl;*/
	
	cout<<endl<<"+++ Greedy 3"<<endl;
	cout<<"Number of Steps = "<<greedy3(n, k, A)<<endl;
	
	cout<<endl<<"+++ Optimal"<<endl;
	cout<<"Number of Steps = "<<optimal(n, k, A)<<endl;
	
	return 0;
}
