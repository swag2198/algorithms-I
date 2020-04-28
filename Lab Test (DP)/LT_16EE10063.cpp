/* Swagatam Haldar
   16EE10063
   Algo Lab Test
   28/4/20
*/

#include <iostream>

using namespace std;

void print_sq(int **F, int m, int n, int s, int t, int k, int l)
{
	for(int i=0; i<m; i++)
	{
		cout<<"   ";
		for(int j=0; j<n; j++)
		{
			if(i >= s && i < s+k && j >= t && j < t+l)
			{
				// if(j >= t && j < t+l)
				// {
					if(F[i][j] == 0)
						cout<<" W ";
					else
						cout<<" B ";
				// }
			}
			else
				cout<<" . ";
		}
		cout<<endl<<endl;
	}
}

int ischessboard(int **F, int i, int j, int m1, int n1, int k, int l)
{
	if(i + k - 1 >= m1 || j + l - 1 >= n1)
		return 0;
	int corner_color = F[i][j];
	int required;
	required = corner_color;
	// cout<<"corner_color = "<<F[i][j]<<endl;

	for(int m=i; m<i+k; m++)
	{
		for(int n=j; n<j+l; n++)
		{
			// cout<<"m = "<<m<<" n = "<<n<<"cc = "<<required<<endl;
			if(F[m][n] != required)
				return 0;
			required = 1 - required;

			if(n == j+l-1)
			{
				if(l%2 == 0)
					required = 1 - required;
			}
		}
	}
	return 1;
}

void essquare(int **F, int m, int n)
{
	int L = min(m, n);

	int **lsquare = new int*[m];
	for(int i=0; i<m; i++)
		lsquare[i] = new int[n];

	int maxsq = -1;
	int maxi, maxj;
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			for(int l=L; l>=1; l--)
			{
				if(ischessboard(F, i, j, m, n, l, l))
				{
					lsquare[i][j] = l;
					if(lsquare[i][j] > maxsq)
					{
						maxsq = l;
						maxi = i;
						maxj = j;
					}
					break;
				}
			}
		}
	}

	// cout<<"maxsq = "<<maxsq<<endl;
	// cout<<"i = "<<maxi<<" j = "<<maxj<<endl;
	print_sq(F, m, n, maxi, maxj, maxsq, maxsq);
	cout<<"    Area = "<<maxsq*maxsq<<endl;

	for(int i=0; i<m; i++)
		delete[] lsquare[i];
	delete[] lsquare;
}

void esrectangle(int **F, int m, int n)
{
	int K, L;
	K = m;
	L = n;

	int **lrect = new int*[m];
	for(int i=0; i<m; i++)
		lrect[i] = new int[n];

	int maxsq = -1;
	int maxi, maxj, maxk;

	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			for(int k=1; k<=K; k++)
			{
				for(int l=1; l<=L; l++)
				{
					if(ischessboard(F,i,j,m,n,k,l))
					{
						lrect[i][j] = k*l;
						if(lrect[i][j] > maxsq)
						{
							maxsq = lrect[i][j];
							maxi = i;
							maxj = j;
							maxk = k;
						}
					}
				}
			}
		}
	}

	print_sq(F, m, n, maxi, maxj, maxk, maxsq/maxk);
	cout<<"    Area = "<<maxsq<<endl;

	for(int i=0; i<m; i++)
		delete[] lrect[i];
	delete[] lrect;
}

void dpsquare(int **F, int m, int n)
{
	int **T = new int*[m];
	for(int i=0; i<m; i++)
		T[i] = new int[n];

	for(int j=0; j<n; j++)
		T[m-1][j] = 1;
	for(int i=0; i<m; i++)
		T[i][n-1] = 1;

	int maxsq = 1, maxi=0, maxj=0;
	int l1, l2;
	for(int i=m-2; i>=0; i--)
	{
		for(int j=n-2; j>=0; j--)
		{
			if(F[i][j] == F[i+1][j] || F[i][j] == F[i][j+1])
				T[i][j] = 1;
			else
			{
				l1 = T[i+1][j];
				l2 = T[i][j+1];

				if(l1 > l2)
					T[i][j] = l2+1;
				else if(l1 < l2)
					T[i][j] = l1+1;
				else
				{
					if(F[i][j] == F[i+l1][j+l2])
						T[i][j] = l1+1;
					else
						T[i][j] = l1;
				}

				if(T[i][j] > maxsq)
				{
					maxsq = T[i][j];
					maxi = i;
					maxj = j;
				}
			}
		}
	}
	print_sq(F, m, n, maxi, maxj, maxsq, maxsq);
	cout<<"    Area = "<<maxsq*maxsq<<endl;
	for(int i=0; i<m; i++)
		delete[] T[i];
	delete[] T;
}

void dprectangle(int **F, int m, int n)
{
	int **K = new int*[m];
	for(int i=0; i<m; i++)
		K[i] = new int[n];

	int **L = new int*[m];
	for(int i=0; i<m; i++)
		L[i] = new int[n];

	int **T = new int*[m];
	for(int i=0; i<m; i++)
		T[i] = new int[n];

	K[m-1][n-1] = 1;
	L[m-1][n-1] = 1;
	T[m-1][n-1] = 1;

	for(int i=m-2; i>=0; i--)
	{
		if(F[i][n-1] != F[i+1][n-1])
			K[i][n-1] = 1 + K[i+1][n-1];
		else
			K[i][n-1] = 1;
		L[i][n-1] = 1;
		T[i][n-1] = K[i][n-1] * L[i][n-1];
	}

	for(int j=n-2; j>=0; j--)
	{
		if(F[m-1][j] != F[m-1][j+1])
			L[m-1][j] = 1 + L[m-1][j+1];
		else
			L[m-1][j] = 1;
		K[m-1][j] = 1;

		T[m-1][j] = K[m-1][j] * L[m-1][j];
	}

	int maxsq = -1, maxi, maxj;
	int k1, l1, k2, l2;

	for(int i=m-2; i>=0; i--)
	{
		for(int j=n-2; j>=0; j--)
		{
			if(F[i][j] == F[i+1][j] || F[i][j] == F[i][j+1])
			{
				K[i][j] = 1;
				L[i][j] = 1;
				T[i][j] = 1;
			}
			else
			{
				k1 = K[i+1][j];
				l1 = L[i+1][j];
				k2 = K[i][j+1];
				l2 = L[i][j+1];


			}
		}
	}


}

int main()
{
	int m, n;
	cin>>m; cin>>n;

	int **F = new int*[m];
	for(int i=0; i<m; i++)
		F[i] = new int[n];

	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin>>F[i][j];

	int N = max(m, n);

	// cout<<"ischessboard = "<<ischessboard(F,0,0,m,n,m)<<endl;
	cout<<endl<<"+++ Exhaustive search: Square"<<endl;
	essquare(F, m, n);

	cout<<endl<<"+++ Exhaustive search: Rectangle"<<endl;
	esrectangle(F, m, n);

	cout<<endl<<"+++ Dynamic Programming: Square"<<endl;
	dpsquare(F, m, n);

	cout<<endl<<"+++ Dynamic Programming: Rectangle"<<endl;
	dprectangle(F, m, n);

	for(int i=0; i<m; i++)
		delete[] F[i];
	delete[] F;

	return 0;
}