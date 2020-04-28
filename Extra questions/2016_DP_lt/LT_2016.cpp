/* Swagatam Haldar */
#include <iostream>

using namespace std;

/* Classic Recursive Formulation */

int isSolvable(int *A, int *B, int n, int T)
{
	if(n == 1)
	{
		if (A[0] == T || B[0] == T)
			return 1;
		return 0;
	}

	int val1 = isSolvable(A+1, B+1, n-1, T-A[0]);
	int val2 = isSolvable(A+1, B+1, n-1, T-B[0]);

	return val1 || val2;
}

/* Dynamic Programming Formulation

T[i][j] = The sum j is realisable by arrays A[i...n-1] and B[i...n-1]
T[n-1][A[n-1]] = 1;
T[n-1][B[n-1]] = 1;
T[n-1][j] = 0; for all other j

T[i][j] = T[i+1][j-A[i]] or T[i+1][j-B[i]];

*/

// Note that ideally we would have 2^n possible arrangement
// of the array indices,however, the minimum and maximum sum
// that can be realiseddo not span the entire range, so we 
// bound to have multiple solutions/ ways to realise a given
// sum value by mutually exclusive indices from the 2 arrays. 

int** issolvable(int *a, int *b, int n, int t)
{
	int maxsum, minsum;
	maxsum = minsum = 0;
	for(int i=0; i<n; i++)
	{
		maxsum += max(a[i], b[i]);
		minsum += min(a[i], b[i]);
	}

	int size = maxsum - minsum + 1;
	cout<<"+++ maxsum = "<<maxsum<<" minsum = "<<minsum<<endl;

	int **T = new int*[n];
	for(int i=0; i<n; i++)
		T[i] = new int[size];

	for(int i=0; i<n; i++)
		for(int j=0; j<size; j++)
			T[i][j] = 0;


	int s = minsum;
	T[n-1][a[n-1] - s] = 1;
	T[n-1][b[n-1] - s] = 1;

	int val1 = 0, val2 = 0;
	for(int i=n-2; i>=0; i--)
	{
		int count = 0;
		int already = 0;
		int inside = 0;
		for(int j=minsum; j<=maxsum; j++)
		{
			if(T[i+1][j-s] == 1)
			{
				inside++;
				if(T[i][j+a[i]-s])
					already++;
				if(T[i][j+b[i]-s])
					already++;

				if(!T[i][j+a[i]-s])
				{
					T[i][j+a[i]-s] = 1;
					count++;
				}
				// cout<<"a makes i = "<<i<<" j = "<<j+a[i]<<endl;
				if(!T[i][j+b[i]-s])
				{
					T[i][j+b[i]-s] = 1;
					count++;
				}
				// cout<<"b makes i = "<<i<<" j = "<<j+b[i]<<endl;
				// count += 2;
			}


			// val1 = (j-a[i]-s >= 0 && j-a[i]-s < size) ? T[i+1][j-a[i]-s] : 0;
			// val2 = (j-b[i]-s >= 0 && j-b[i]-s < size) ? T[i+1][j-b[i]-s] : 0;
			// T[i][j - s] = val1 || val2;
			// if(val1)
			// 	cout<<"a->i = "<<i<<" j = "<<j<<endl;
			// if(val2)
			// 	cout<<"b->i = "<<i<<" j = "<<j<<endl;
			// if(val1 || val2)
			// 	count++;
			// if(val1 && val2)
			// 	cout<<"both for "<<"i = "<<i<<" j = "<<j<<endl;

			// if(T[i][j] == 1)
			// {
			// 	cout<<"i = "<<i<<" j = "<<j<<endl;
			// }
		}
		// cout<<"+++ For i = "<<i<<" Num count = "<<count<<" alr = "<<already<<endl;
		// cout<<"++++ inside = "<<inside<<endl;
	}

	// cout<<"ggg: "<<T[n-1][70]<<endl;

	return T;
}

void printsoln(int *a, int *b, int n, int t, int maxsum, int minsum, int **T)
{
	int cursum = t;
	int* I = new int[n];
	int s = minsum, flag;
	for(int i=1; i<n; i++)
	{
		for(int j=minsum; j<=maxsum; j++)
		{
			flag = 0;
			if(T[i][j-s] == 1)	
			{
				// cout<<"+++ i = "<<i<<"j = "<<j<<endl;
				// cout<<"a[i] = "<<a[i]<<" b[i] = "<<b[i]<<endl;
				if(j == cursum - a[i-1])
				{
					// cout<<"Setting I["<<i-1<<"] = "<<1<<"when j -cursum = "<<j-cursum<<endl;
					I[i-1] = 1;
					cursum -= a[i-1];
					flag = 1;
				}
				else if(j == cursum - b[i-1])
				{
					// cout<<"Setting I["<<i-1<<"] = "<<2<<"when j -cursum = "<<j-cursum<<endl;
					I[i-1] = 2;
					cursum -= b[i-1];
					flag = 1;
				}
				if(flag)
					break;
			}
		}

	}

	if(cursum == a[n-1])
		I[n-1] = 1;
	else
		I[n-1] = 2;


	int result = 0;
	int asum = 0, bsum = 0;
	cout<<"+++ Printing Index array: ";
	for(int i=0; i<n; i++)
	{
		result += (I[i] == 1) ? a[i] : b[i];
		asum += (I[i] == 1) ? a[i] : 0;
		bsum += (I[i] == 2) ? b[i] : 0;
		cout<<I[i]<<" ";
	}
	cout<<endl;
	cout<<"+++ Obtained sum = "<<result<<endl;
	cout<<"+++ A:";
	for(int i=0; i<n; i++)
	{
		if(I[i] == 1)
			cout<<a[i]<<"  ";
		else
			cout<<"    ";
	}
	cout<<endl;
	cout<<"+++ B:";
	for(int i=0; i<n; i++)
	{
		if(I[i] == 2)
			cout<<b[i]<<"  ";
		else
			cout<<"    ";
	}
	cout<<endl;

	cout<<"+++ sum1 = "<<asum<<" sum2 = "<<bsum<<endl;
}

int main()
{
	int n, t;
	int *a, *b;

	// cout<<"n = ";
	cin>>n;
	a = new int[n];
	b = new int[n];

	// cout<<"A = ";
	for(int i=0; i<n; i++)
		cin>>a[i];
	// cout<<"B = ";
	for(int i=0; i<n; i++)
		cin>>b[i];
	// cout<<"T = ";
	cin>>t;

	int maxsum, minsum;
	maxsum = minsum = 0;
	for(int i=0; i<n; i++)
	{
		maxsum += max(a[i], b[i]);
		minsum += min(a[i], b[i]);
	}

	int size = maxsum - minsum + 1;
	int s = minsum;

	if(isSolvable(a, b, n, t))
		cout<<"+++ It is possible!"<<endl;

	int **T = issolvable(a, b, n, t);
	if(T[0][t-s] == 1)
		cout<<"+++ Solution exists (DP)!"<<endl;
	else
		cout<<"+++ Solution does not exist (DP)!"<<endl;

	// for(int j=0; j<size; j++)
	// {
	// 	if(T[n-1][j] == 1)
	// 		cout<<"j = "<<j<<endl;
	// }

	if(T[0][t-s])
		printsoln(a, b, n, t, maxsum, minsum, T);

	return 0;

}