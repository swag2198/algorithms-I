//Swagatam Haldar 16EE10063, Assignment- 10
#include <iostream>
#include <cstdlib>
#include <climits>
#include <iomanip>

#define INF 1e9

using namespace std;

typedef struct _graph
{
	int n;
	char **air;
	int **cost;
}graph;

graph readgraph()
{
	int n1; cin>>n1;
	graph G;
	G.n = n1;

	G.air = new char*[n1];
	G.cost = new int*[n1];

	for(int i=0; i<n1; i++)
	{
		G.air[i] = new char[n1];
		G.cost[i] = new int[n1];
	}

	for(int i=0; i<n1; i++)
	{
		for(int j=0; j<n1; j++)
		{
			if(i == j)
			{
				G.air[i][j] = 's';
				G.cost[i][j] = 0;
			}
			else
			{
				G.air[i][j] = '-';
				G.cost[i][j] = INF;
			}
		}
	}


	int i, j, cij;
	char aij;
	while(1)
	{
		cin>>i;
		if(i == -1)
			break;
		cin>>j>>cij>>aij;

		G.air[i][j] = aij;
		G.cost[i][j] = cij;
	}

	return G;
}

void prngraph(graph &G)
{
	int n = G.n;
	for(int i=0; i<n; i++)
	{
		cout<<"    "<<i<<" ->  ";
		for(int j=0; j<n; j++)
		{
			if(G.air[i][j] != '-' && G.air[i][j] != 's')
			{
				cout<<j<<" ("<<G.cost[i][j]<<", "<<G.air[i][j]<<")\t";
			}
		}
		cout<<endl;
	}
}

graph getAIgraph(graph &G)
{
	graph H;
	H.n = G.n;
	int n = H.n;
	H.air = new char*[n];
	H.cost = new int*[n];

	for(int i=0; i<n; i++)
	{
		H.air[i] = new char[n];
		H.cost[i] = new int[n];
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(i == j)
			{
				H.air[i][j] = 's';
				H.cost[i][j] = 0;
			}
			else
			{
				if(G.air[i][j] == '-' || G.air[i][j] == 'n')
				{
					H.air[i][j] = '-';
					H.cost[i][j] = INF;
				}
				else
				{
					H.air[i][j] = 'a';
					H.cost[i][j] = G.cost[i][j];
				}	
			}
		}
	}
	return H;
}

int** initmat(int n)
{
	int **matrix = new int*[n];
	for(int i=0; i<n; i++)
		matrix[i] = new int[n];

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void initialiseD(int **D, int **cost, int n)
{
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			D[i][j] = cost[i][j];
}


int** APSP(graph &G)
{
	int n = G.n;
	int **D = initmat(n);

	initialiseD(D, G.cost, n);

	int d1, d2;

	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				d1 = D[i][j];
				d2 = D[i][k] + D[k][j];
				D[i][j] = min(d1, d2);
			}
		}
	}

	for(int i=0; i<n; i++)
	{
		cout<<"    "<<i<<" ->   ";
		for(int j=0; j<n; j++)
		{
			if(D[i][j] != INF)
				cout<<setw(6)<<D[i][j]<<" ";
			else
				cout<<setw(6)<<"------ ";
		}
		cout<<endl;
	}
	return D;
}

int** APSPone(graph &G, int **C1)
{
	int n = G.n;
	int **D = initmat(n);
	initialiseD(D, C1, n);
	int curcost;
	int curmin = INF;

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(C1[i][j] == INF)
			{
				// cout<<"+++ inside i = "<<i<<"j = "<<j<<endl;
				curcost = C1[i][j];
				curmin = C1[i][j];
				for(int k=0; k<n; k++)
				{
					for(int l=0; l<n; l++)
					{
						if(G.air[k][l] == 'n')
						{
							// cout<<"    k = "<<k<<"l = "<<l<<" can up"<<endl;
							if(C1[i][k] + G.cost[k][l] + C1[l][j] < curcost)
							{
								// cout<<"i = "<<i<<"j = "<<j<<" updated"<<endl;
								curcost = C1[i][k] + G.cost[k][l] + C1[l][j];
								curmin = min(curmin, curcost);
							}
						}
					}
				}
				D[i][j] = curmin;
			}
		}
	}

	for(int i=0; i<n; i++)
	{
		cout<<"    "<<i<<" ->   ";
		for(int j=0; j<n; j++)
		{
			if(D[i][j] != INF)
				cout<<setw(6)<<D[i][j]<<" ";
			else
				cout<<setw(6)<<"------ ";
		}
		cout<<endl;
	}
	return D;
}

int** APSPany(graph &G, int **C1)
{
	int n = G.n;
	int **D = initmat(n);
	initialiseD(D, G.cost, n);

	int d1, d2;

	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				// if
				d1 = D[i][j];
				d2 = D[i][k] + D[k][j];
				D[i][j] = min(d1, d2);
			}
		}
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(C1[i][j] == INF)

				C1[i][j] = D[i][j];
		}
	}

	for(int i=0; i<n; i++)
	{
		cout<<"    "<<i<<" ->   ";
		for(int j=0; j<n; j++)
		{
			if(C1[i][j] != INF)
				cout<<setw(6)<<C1[i][j]<<" ";
			else
				cout<<setw(6)<<"------ ";
		}
		cout<<endl;
	}
	return C1;
}

int main()
{
	graph G = readgraph();
	cout<<"+++ Original graph"<<endl;
	prngraph(G);

	graph H = getAIgraph(G);
	cout<<endl<<"+++ AI subgraph"<<endl;
	prngraph(H);

	cout<<endl<<"+++ Cheapest AI prices"<<endl;
	int** C1 = APSP(H);

	cout<<endl<<"+++ Cheapest prices with at most one non-AI leg"<<endl;
	int** C2 = APSPone(G, C1);

	cout<<endl<<"+++ Cheapest prices with any number of non-AI legs"<<endl;
	int** C3 = APSPany(G, C1);



	return 0;
}