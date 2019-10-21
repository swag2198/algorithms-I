/***********************
*                      *
*   21/10/19, 00:49    *
* Dijkstra's Algorithm *
*     Author: SH       *
*                      *
***********************/

#include <iostream>
#define INFMAX 100000000
// #include <cmath>

using namespace std;

//IMPLEMENTATION OF GRAPH IN ADJACENCY LIST FORMAT
typedef struct _edge
{
	int vid;
	double ewt;
	struct _edge *next;
	_edge()
	{
		next = NULL;
	}
	_edge(int _vid, double _ewt)
	{
		vid = _vid;
		ewt = _ewt;
		next = NULL;
	}
}edge;
typedef edge* nbr;
typedef struct _head
{
	int vid;
	int size;
	nbr adjlist;
	_head()
	{
		// vid = 1000;
		size = 0;
		adjlist = NULL;
	}
	_head(int _vid)
	{
		vid = _vid;
		size = 0;
		adjlist = NULL;
	}
}head;
typedef head* graph;

void addEdge(graph G, int a, int b, double ewt)
{
	nbr p = G[a].adjlist;
	nbr newedge = new edge(b+1,ewt); //BE VERY CAREFUL ABOUT THIS!
	if(p == NULL)
	{
		G[a].adjlist = newedge;
	}
	else
	{
		while(p->next != NULL)
			p = p->next;
		p->next = newedge;
	}
	G[a].size++;
}
void print_graph(graph G, int n)
{
	int k; nbr p;
	cout<<"Printing Graph in AdjList Format: "<<endl;
	for(int i=0; i<n; i++)
	{
		cout<<"Vertex no = "<<G[i].vid<<" No. of nbrs = "<<G[i].size<<" List-> ";
		k = G[i].size;
		p = G[i].adjlist;
		while(p)
		{
			cout<<p->vid<<", ";
			p = p->next;
		}
		cout<<endl<<endl;
	}
}

//IMPLEMENTATION OF MIN-PRIORITY QUEUE WITH CHANGE_PRIORITY FACILITY AND LOCATOR ARRAY
typedef struct _hnode
{
	int vid;
	double wt;
}hnode;
typedef hnode* heap;

void initheap(graph G, int n, int u, int *L, int *P, heap Q) //DOES THE WORK FOR PUSHING THE NODES IN THE BEGINNING OF DIJKSTRA, u IS 0-BASED
{
	int pos = 0;
	for(int i=0; i<n; i++)
	{
		if(i == u)
		{
			L[i] = -1;
			P[i] = -1;
		}
		else
		{
			Q[pos].wt = INFMAX;
			Q[pos].vid = i+1; //HERE ALSO ONE BASED INDEXING IS USED
			L[i] = pos;
			P[i] = u;
			pos++;
		}
	}
	nbr temp = G[u].adjlist;
	while(temp)
	{
		pos = temp->vid - 1;
		Q[L[pos]].wt = temp->ewt;
		temp = temp->next;
	}
}
void heapify(heap Q, int n1, int i, int *L)
{
	int l,r,mn;
	int u,v;
	hnode temp;
	while(1)
	{
		l = 2*i+1; r = 2*i+2;
		if(l >= n1)
			break;
		mn = ((r>=n1)||(Q[l].wt <= Q[r].wt)) ? l : r;
		if(Q[i].wt <= Q[mn].wt)
			break;
		// cout<<"Here1"<<endl;
		u = Q[i].vid-1;
		v = Q[mn].vid-1;
		L[u] = mn;
		L[v] = i;
		temp = Q[i];
		Q[i] = Q[mn];
		Q[mn] = temp;
		// cout<<"Here2"<<endl;
		// L[u] = mn;
		// L[v] = i;
		i = mn;
		// cout<<"Here3"<<endl;
	}
}
void makeheap(heap Q, int n1, int *L)
{
	for(int i = n1/2 - 1; i>=0; i--)
		heapify(Q,n1,i,L);
}
void deletemin(heap Q, int &n1, int *L)
{
	int u,v;
	u = Q[0].vid-1;
	v = Q[n1-1].vid-1;
	L[u] = -1;
	L[v] = 0;
	Q[0].vid = Q[n1-1].vid;
	Q[0].wt = Q[n1-1].wt;
	n1--;
	heapify(Q,n1,0,L);
}
void decreasePriority(heap Q, int n1, int *L, int j, double newval) //NOTE THAT IT IS A MIN-PRIORITY QUEUE, HENCE WE HAVE TO BUBBLE UP THE DECREASED KEY
{
	int i = L[j]; //POSITION OF VERTEX j(0-BASED) WHOSE PRIORITY IS TO BE CHANGED
	Q[i].wt = newval;
	int p, u, v;
	hnode temp;
	while(1)
	{
		if(i == 0)
			break;
		p = (i-1)/2;
		if(Q[p].wt <= Q[i].wt)
			break;
		u = Q[p].vid-1;
		v = Q[i].vid-1;
		temp = Q[p]; //NOTE THAT YOU HAVE TO SWAP ENTIRE STRUCTURES! ONLY SWAPPING vid OR wt WON'T MEET THE PURPOSE!
		Q[p] = Q[i];
		Q[i] = temp;

		L[u] = i;
		L[v] = p;
		i = p;
	}
}

void printheap(heap Q, int n) //HEAP SIZE TO BE PASSED = n-1
{
	for(int i=0; i<n; i++)
		cout<<Q[i].vid<<"->"<<Q[i].wt<<"\t";
	cout<<endl;
}
void printlocator(int *L, int n) //HEAP SIZE TO BE PASSED = n-1
{
	for(int i=0; i<n; i++)
		cout<<L[i]<<"\t";
	cout<<endl;
}

void relaxscan(graph G, int curv, heap Q, int n1, int *L, int *P, double *D)
{
	int v = curv, w;
	double cost;
	nbr temp = G[curv].adjlist;
	while(temp)
	{
		w = temp->vid - 1;
		cost = temp->ewt;
		if(D[v] + cost < D[w])
		{
			D[w] = D[v] + cost;
			P[w] = v;
			decreasePriority(Q,n1,L,w,D[w]);
		}
		temp = temp->next;
	}
}

void Dijkstra(graph G, int n, int s, double *D, int *P)
{
	heap Q = new hnode[n-1];
	int n1 = n-1;
	int *L = new int[n];
	initheap(G,n,s,L,P,Q);
	makeheap(Q,n1,L);
	for(int i=0; i<n; i++)
	{
		if(i == s)
			D[i] = 0;
		else
			D[i] = Q[L[i]].wt;
	}
	int curv;
	while(n1)
	{
		curv = Q[0].vid-1;
		deletemin(Q,n1,L);
		relaxscan(G,curv,Q,n1,L,P,D);

	}
	delete[] L;
	delete[] Q;
}
int main()
{
	int n, m, a, b, k, u;
	nbr p;
	double wt;
	cout<<"n = "; cin>>n; cout<<"m = "; cin>>m;
	cout<<"n: "<<n<<", m: "<<m<<endl;
	graph G = new head[n];
	for(int i=0; i<n; i++)
		G[i].vid = i+1;
	cout<<"Give directed edges i.e., 1->2: "<<endl;
	for(int i=0; i<m; i++)
	{
		cin>>a>>b>>wt;
		a = a-1; b = b-1; //USER ENTERS IN 1-BASED INDEXED NODE VALUES
		addEdge(G,a,b,wt);
	}
	print_graph(G,n);
	// cout<<G[5].vid<<endl; //PRINT THE VALUE IN THE EMPTY INITIALISER!
	// cout<<sizeof(graph)<<endl;
	cout<<"u = "; cin>>u; //INPUT u (source i.e, s in the function Dijkstra) in 1-BASED INDEXING
	u--;
	int *P = new int[n];
	double *D = new double[n];
	Dijkstra(G,n,u,D,P);
	cout<<"Shortest distances are as follows from start = "<<u+1<<endl;
	for(int i=0; i<n; i++)
		cout<<u+1<<"->"<<i+1<<" : "<<D[i]<<endl;
	cout<<"Parents in shortest path tree: "<<endl;
	for(int i=0; i<n; i++)
		cout<<i+1<<"->"<<P[i]+1<<endl;
	// int *L = new int[n];
	// heap Q = new hnode[n-1];
	// int n1 = n-1; //HEAP SIZE
	// initheap(G,n,u,L,P,Q);
	// // printheap(Q,n1);
	// makeheap(Q,n1,L);

	// cout<<"After making heap: "<<endl;
	// printheap(Q,n1);
	// printlocator(L,n);
	// cout<<"Do a change priority"<<endl;
	// decreasePriority(Q,n1,L,5,0);
	// printheap(Q,n1);
	// printlocator(L,n);
	// cout<<"Do a Deletemin"<<endl;
	// deletemin(Q,n1,L);
	// printheap(Q,n1);
	// printlocator(L,n);
	return 0;
}

// //SAMPLE INPUT/OUTPUT ON TERMINAL
// //GRAPH IS ASSUMED TO HAVE NODES 1 TO N (AS ENTERED BY USER)
// //INTERNALLY I PROCESS IT AS 0 TO N-1
// 1.
// n = 9
// m = 28
// n: 9, m: 28
// Give directed edges i.e., 1->2: 
// 1 2 4
// 2 1 4
// 1 8 8
// 8 1 8
// 2 3 8
// 3 2 8
// 2 8 11
// 8 2 11
// 3 4 7
// 4 3 7
// 3 9 2
// 9 3 2
// 3 6 4
// 6 3 4
// 4 5 9
// 5 4 9
// 4 6 14
// 6 4 14
// 5 6 10
// 6 5 10
// 6 7 2
// 7 6 2
// 7 8 1
// 8 7 1
// 7 9 6
// 9 7 6
// 8 9 7
// 9 8 7
// Printing Graph in AdjList Format: 
// Vertex no = 1 No. of nbrs = 2 List-> 2, 8, 

// Vertex no = 2 No. of nbrs = 3 List-> 1, 3, 8, 

// Vertex no = 3 No. of nbrs = 4 List-> 2, 4, 9, 6, 

// Vertex no = 4 No. of nbrs = 3 List-> 3, 5, 6, 

// Vertex no = 5 No. of nbrs = 2 List-> 4, 6, 

// Vertex no = 6 No. of nbrs = 4 List-> 3, 4, 5, 7, 

// Vertex no = 7 No. of nbrs = 3 List-> 6, 8, 9, 

// Vertex no = 8 No. of nbrs = 4 List-> 1, 2, 7, 9, 

// Vertex no = 9 No. of nbrs = 3 List-> 3, 7, 8, 

// u = 1
// Shortest distances are as follows from start = 1
// 1->1 : 0
// 1->2 : 4
// 1->3 : 12
// 1->4 : 19
// 1->5 : 21
// 1->6 : 11
// 1->7 : 9
// 1->8 : 8
// 1->9 : 14
// Parents in shortest path tree: 
// 1->0
// 2->1
// 3->2
// 4->3
// 5->6
// 6->7
// 7->8
// 8->1
// 9->3

// 2.
// n = 6
// m = 10
// n: 6, m: 10
// Give directed edges i.e., 1->2: 
// 1 2 3           
// 1 3 9
// 1 6 6
// 2 4 2
// 2 6 2
// 3 5 4
// 4 5 1
// 6 3 2
// 6 5 5
// 6 4 3
// Printing Graph in AdjList Format: 
// Vertex no = 1 No. of nbrs = 3 List-> 2, 3, 6, 

// Vertex no = 2 No. of nbrs = 2 List-> 4, 6, 

// Vertex no = 3 No. of nbrs = 1 List-> 5, 

// Vertex no = 4 No. of nbrs = 1 List-> 5, 

// Vertex no = 5 No. of nbrs = 0 List-> 

// Vertex no = 6 No. of nbrs = 3 List-> 3, 5, 4, 

// u = 1
// Shortest distances are as follows from start = 1
// 1->1 : 0
// 1->2 : 3
// 1->3 : 7
// 1->4 : 5
// 1->5 : 6
// 1->6 : 5
// Parents in shortest path tree: 
// 1->0
// 2->1
// 3->6
// 4->2
// 5->4
// 6->2

