/* Swagatam Haldar */
#include <iostream>

using namespace std;

/* Dynamic Programming Formulation

P[i][j] = A[0...i] can realise the value j
P[0][A[0]] = 1;
P[i][j] = P[i-1][j-A[i]] || P[i-1][j+A[i]]

*/

int** realizable(int* A, int n, int t, int &s)
{
	int sum = 0;
	for(int i=0; i<n; i++)
		sum += A[i];
	s = -sum; /* Minimum possible realisable value = offset index*/

	int **T = new int*[n];
	for(int i=0; i<n; i++)
		T[i] = new int[2*sum + 1];

	for(int i=0; i<n; i++)
		for(int j=-sum; j<=sum; j++)
			T[i][j-s] = 0;

	T[0][A[0]-s] = 1;
	T[0][-A[0]-s] = 1;

	for(int i=1; i<n; i++)
	{
		for(int j=-sum; j<=sum; j++)
		{
			if(T[i-1][j-s] == 1)
			{
				T[i][j+A[i]-s] = 1;
				T[i][j-A[i]-s] = 1;
			}
		}
	}

	return T;
}

void printsol(int *A, char *signs, int n)
{
	// cout<<"    Solution: ";
	int sum = 0;
	for(int i=0; i<n; i++)
	{
		cout<<signs[i]<<A[i];
		if(signs[i] == '+')
			sum += A[i];
		else
			sum -= A[i];
	}
	cout<<endl;
	cout<<"    Realised sum = "<<sum<<endl;
}

void showone(int *A, int n, int t, int **T, int &s)
{
	int cursum = t, flag;
	char *signs = new char[n];

	for(int i=n-2; i>=0; i--)
	{
		for(int j=s; j<=-s; j++)
		{
			flag = 0;
			if(T[i][j-s] == 1)
			{
				if(j == cursum - A[i+1])
				{
					signs[i+1] = '+';
					cursum -= A[i+1];
					flag = 1;
				}
				else if(j == cursum + A[i+1])
				{
					signs[i+1] = '-';
					cursum += A[i+1];
					flag = 1;

				}
			}
			if(flag)
				break;
		}
	}

	if(cursum == -A[0])
		signs[0] = '-';
	else
		signs[0] = '+';

	cout<<"    Solution: ";
	printsol(A, signs, n);
}

/*
DFS function performs a traversal on the DP Table to generate all
possible solutions. DFS(T, i, j) 
*/

void DFS(int** T, int* A, int n, int s, int i, int j, char* signs, int &count)
{
	// if(j < 0 || j >= 2*(-s)+1)
	// 	return;
	/*
	Note that here i = row of the DP Table but j = actual sum value
	and not the column number where the realisability of this sum is
	stored. So putting the careless return statement is wrong!

	Also note that no visited array is required in the DFS traversal
	because our main aim is not to cover all nodes in the implicit
	graph! We simply want to enumerate all possible paths from a source
	node to a target node, even if some portion of the path is common
	(already visited by some other path) to both paths.

	It is also interesting to observe that the implicit graph is a
	directed acyclic graph.

	It is also very pleasing to visualise the running time of the code
	in terms of the graph. We know avg no. of nodes in a path = n. Maximum
	no. of edges that can be in a path = s [in the extreme case, we 
	have to move along diagonal to the top!]. If the no. of solutions
	is = r, then we are in total traversing a distance of (s+r).
	*/
	if(i == 0)
	{
		if(j == A[0])
		{	
			count++;
			signs[0] = '+';
			cout<<"    Solution "<<count<<": ";
			printsol(A, signs, n);
		}
		if(j == -A[0])
		{
			count++;
			signs[0] = '-';
			cout<<"    Solution "<<count<<": ";
			printsol(A, signs, n);
		}
		return;
	}

	if(j-A[i]-s >= 0 && j-A[i]-s < 2*(-s) + 1) //bound check
	{
		if(T[i-1][j-A[i]-s] == 1) //neighbor check
		{
			signs[i] = '+';
			DFS(T, A, n, s, i-1, j-A[i], signs, count);
		}
	}
	
	if(j+A[i]-s >= 0 && j+A[i]-s < 2*(-s) + 1)
	{
		if(T[i-1][j+A[i]-s] == 1)
		{
			signs[i] = '-';
			DFS(T, A, n, s, i-1, j+A[i], signs, count);
		}
	}
	return;
}

void showall(int *A, int n, int t, int **T, int &s)
{
	int count = 0;
	char *signs = new char[n];

	/* Start the DFS from the answer node at the bottom of the
	table that is (n-1, t) and move up. Carefully check neighbor
	checks and bound checks inside the DFS function to ensure
	correct running of code */
	DFS(T, A, n, s, n-1, t, signs, count);
}

int main()
{
	int n, t, s;
	cin>>n;
	int *A = new int[n];
	for(int i=0; i<n; i++)
		cin>>A[i];
	cin>>t;

	int** T = realizable(A, n, t, s);
	cout<<"+++ Part 1: Realizability check"<<endl;
	if(T[n-1][t-s])
		cout<<"    The value "<<t<<" is realizable!"<<endl;
	else
		cout<<"    The value "<<t<<" is not realizable!"<<endl;

	if(T[n-1][t-s])
	{
		cout<<endl<<"+++ Part 2: One solution"<<endl;
		showone(A, n, t, T, s);

		cout<<endl<<"+++ Part 3: All solutions"<<endl;
		showall(A, n, t, T, s);
	}
	return 0;
}