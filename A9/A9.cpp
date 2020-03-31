//Swagatam Haldar, 16EE10063, Assignment- 9
#include <iostream>
#include <vector>

using namespace std;

typedef struct _edge
{
	int vid;
	struct _edge *next;
	_edge()
	{
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
		size = 0;
		adjlist = NULL;
	}
}head;

typedef struct _graph
{
	int n;
	vector<char> colors;
	head *list;
}graph;


void addEdge(graph &G, int a, int b, int flag)
{
	int m, n;
	for(int i=0; i<G.n; i++)
	{
		if(G.list[i].vid == a)
			m = i;
		if(G.list[i].vid == b)
			n = i;
	}
	// if(G.n < 20)
	// 	cout<<"m = "<<m<<" n = "<<n<<endl;
	nbr p1 = G.list[m].adjlist;
	nbr p2 = G.list[n].adjlist;

	nbr edge1, edge2;
	edge1 = new edge;
	edge2 = new edge;
	edge1->vid = b; // a---b undirected edge
	edge2->vid = a; //b---a und. edge


	if(p1 == NULL)
	{
		G.list[m].adjlist = edge1;
	}
	else
	{
		while(p1->next != NULL)
			p1 = p1->next;
		p1->next = edge1;
	}
	G.list[m].size++;

	if(flag == 2) //add both edges
	{
		if(p2 == NULL)
		{
			G.list[n].adjlist = edge2;
		}
		else
		{
			while(p2->next != NULL)
				p2 = p2->next;
			p2->next = edge2;
		}
		G.list[n].size++;
	}
}

graph readgraph()
{
	int n1; cin>>n1;

	vector<char> cols(n1);
	for(int i=0; i<n1; i++)
		cin>>cols[i];

	graph G;
	G.n = n1;
	G.colors = cols;
	G.list = new head[n1];

	for(int i=0; i<n1; i++)
	{
		G.list[i].vid = i;
		G.list[i].size = 0;
		G.list[i].adjlist = NULL;
	}

	int u, v;
	while(1)
	{
		cin>>u;
		if(u == -1)
			break;
		cin>>v;
		addEdge(G, u, v, 2);
	}

	return G;
}

void print_graph(graph G)
{
	int k; nbr p;
	cout<<"+++ Printing Graph in AdjList Format: "<<endl;
	for(int i=0; i<G.n; i++)
	{
		cout<<"    ["<<G.colors[i]<<"]   ";
		cout<<G.list[i].vid<<"->\t";
		k = G.list[i].size;
		p = G.list[i].adjlist;
		while(p)
		{
			cout<<p->vid<<", ";
			p = p->next;
		}
		cout<<endl;
	}
}

graph getcolgraph(graph &G, char col)
{
	graph Gs;
	int count = 0;
	vector<int> indices;
	for(int i=0; i<G.n; i++)
	{
		if(G.colors[i] == col)
		{
			indices.push_back(G.list[i].vid);
			count++;
		}
	}
	// // cout<<"indices ready"<<endl;
	// for(int i=0; i<count; i++)
	// 	cout<<indices[i]<<",";
	// cout<<endl;

	Gs.n = count;
	vector<char> colorss(Gs.n, col);
	Gs.colors = colorss;
	Gs.list = new head[Gs.n];

	for(int i=0; i<Gs.n; i++)
	{
		Gs.list[i].vid = indices[i];
		Gs.list[i].size = 0;
		Gs.list[i].adjlist = NULL;
	}
	// cout<<"Gs init"<<endl;
	// for(int i=0; i<Gs.n; i++)
	// {
	// 	// cout<<"i = "<<i<<", Gs.list[i].vid = "<<Gs.list[i].vid<<endl;
	// }

	nbr p;
	int u, v;
	for(int i=0; i<indices.size(); i++)
	{
		u = indices[i];
		p = G.list[u].adjlist;
		// u = G.list[i].vid;
		while(p)
		{
			v = p->vid;
			if(G.colors[v] == col)
			{
				// cout<<"adding edge "<<u<<"---"<<v<<endl;
				addEdge(Gs, u, v, 1);
			}
			p = p->next;
		}
	}
	return Gs;
}

int locate(int *v, int n, int b)
{
	int k;
	for(int i=0; i<n; i++)
	{
		if(v[i] == b)
			return i;
	}
}

void DFS(graph &G, int uind, int *P, int *v, int *visited, int *color)
{
	visited[uind] = 1;
	// cout<<v[uind]<<" marked visited"<<endl;
	color[uind] = 1;

	nbr p = G.list[uind].adjlist;
	int a, b, bind;
	a = v[uind]; //original vid in G
	while(p)
	{
		b = p->vid;
		// cout<<"b = "<<b<<endl;
		bind = locate(v, G.n, b);
		if(visited[bind] == 0)
		{
			P[bind] = uind;
			// cout<<"P["<<v[bind]<<"] = ["<<v[uind]<<"]"<<endl;
			DFS(G, bind, P, v, visited, color);
		}
		else if(P[uind] != bind) //not a direct child of its parent
		{
			if(color[bind] == 1) //back edge
			{
				// cout<<"In call of "<<v[uind]<<" to "<<v[bind]<<endl;
				vector<int> v1;
				vector<char> cc;
				int temp = uind;

				v1.push_back(v[temp]);
				cc.push_back(G.colors[temp]);
				// cout<<"g coloy = "<<G.colors[temp]<<endl;

				
				while(1)
				{
					temp = P[temp];
					// cout<<"dfef"<<v[temp]<<endl;
					v1.push_back(v[temp]);
					cc.push_back(G.colors[temp]);
					if(temp == bind)
						break;
				}

				//Print detected cycle
				cout<<"    ("<<v1[0]<<",";
				for(int i=1; i<v1.size(); i++)
					cout<<v1[i]<<",";
				cout<<"), Color: ( "<<cc[0]<<",";
				for(int i=1; i<cc.size(); i++)
					cout<<cc[i]<<",";
				cout<<")"<<endl;
			}
		}
		p = p->next;
	}
	color[uind] = 2; //uind gets out of DFS recursion stack
}

int* multiDFS(graph &G)
{
	int *P = new int[G.n]; //Parents for DFS Forest (indexed)
	int *color = new int[G.n]; //State of a node (indexed)
	int *visited = new int[G.n]; //indexed visited array
	int *v = new int[G.n]; //v[i] = vertex id of index i in G

	for(int i=0; i<G.n; i++)
	{
		P[i] = -1;
		color[i] = 0; //0-unvisited, 1-in stack, 2-out of stack
		visited[i] = 0;
		v[i] = G.list[i].vid;
	}

	for(int i=0; i<G.n; i++)
	{
		if(visited[i] == 0)
		{
			DFS(G, i, P, v, visited, color);
		}
	}

	return P;
}

graph getrbgraph(graph &G, graph &GR, graph &GB, int *PR, int *PB)
{
	graph GRB;
	GRB.n = G.n;
	GRB.colors = G.colors;
	GRB.list = new head[G.n];

	for(int i=0; i<G.n; i++)
	{
		GRB.list[i].vid = i;
		GRB.list[i].size = 0;
		GRB.list[i].adjlist = NULL;
	}

	int a, b;

	// for(int i=0; i<GR.n; i++)
	// {
	// 	cout<<"i = "<<i<<" PR[i] = "<<PR[i]<<" a = "<<GR.list[i].vid<<" b = "<<GR.list[PR[i]].vid<<endl;
	// }
	// for(int i=0; i<GB.n; i++)
	// {
	// 	cout<<"i = "<<i<<" PB[i] = "<<PB[i]<<" a = "<<GB.list[i].vid<<" b = "<<GB.list[PR[i]].vid<<endl;
	// }

	for(int i=0; i<GR.n; i++)
	{
		b = PR[i];
		if(b != -1)
		{
			a = GR.list[i].vid;
			b = GR.list[PR[i]].vid;

			// cout<<"Adding edge "<<a<<"---"<<b<<endl;

			addEdge(GRB, a, b, 2);
		}
	}

	for(int i=0; i<GB.n; i++)
	{
		b = PB[i];
		if(b != -1)
		{
			a = GB.list[i].vid;
			b = GB.list[PB[i]].vid;
			// cout<<"Adding edge "<<a<<"---"<<b<<endl;
			addEdge(GRB, a, b, 2);
		}
	}

	// cout<<endl;

	nbr p;
	for(int i=0; i<G.n; i++)
	{
		p = G.list[i].adjlist;
		a = G.list[i].vid;
		while(p)
		{
			b = p->vid;
			if(G.colors[a] != G.colors[b])
			{
				// cout<<"Adding edge "<<a<<"---"<<b<<endl;
				addEdge(GRB, a, b, 1);
			}
			p = p->next;
		}
	}

	return GRB;
}

int main()
{
	graph G = readgraph();
	cout<<endl<<"+++ Original graph (G)"<<endl;
	print_graph(G);

	graph GR = getcolgraph(G, 'r');
	graph GB = getcolgraph(G, 'b');
	cout<<endl<<"+++ Red subgraph (GR)"<<endl;
	print_graph(GR);
	cout<<endl<<"+++ Blue subgraph (GB)"<<endl;
	print_graph(GB);


	cout<<endl<<"+++ Red cycles"<<endl;
	int *PR = multiDFS(GR);

	cout<<endl<<"+++ Blue cycles"<<endl;
	int *PB = multiDFS(GB);

	graph GRB = getrbgraph(G, GR, GB, PR, PB);
	cout<<endl<<"+++ Non monochromatic graph (GRB)"<<endl;
	print_graph(GRB);

	cout<<endl<<"+++ Multi-color cycles"<<endl;
	int *PRB = multiDFS(GRB);

	return 0;
}