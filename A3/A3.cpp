//16EE10063, Swagatam Haldar, 28/1/20

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

using namespace std;

typedef struct _linenode
{
	int index;
	double m, c;
	_linenode()
	{
		index = 0;
		m = 0;
		c = 0;
	}
}line;

typedef struct _point
{
	int lineno;
	double x, y;
	_point()
	{
		lineno = -1;
		x = 0; y = 0;
	}
}point;

typedef struct _boundary
{
	int lineno;
	point begin, end;
}boundary;

void printlines(vector<line> &lines)
{
	int n = lines.size();
	line node;
	cout<<endl<<"Printing lines ..."<<endl;
	for(int i=0; i<n; i++)
	{
		node = lines[i];
		cout<<"Line\t"<<node.index<<": y =\t"<<node.m<<"x +\t"<<node.c<<endl;
	}
}

int smallest_slope_line(vector<line> &lines)
{
	double curslope = lines[0].m;
	int curmin = 0;
	for(int i=1; i<lines.size(); i++)
	{
		if(lines[i].m < curslope)
		{
			curslope = lines[i].m;
			curmin = i;
		}
	}
	return curmin;
}

point intersection_point(line &l1, line &l2)
{
	double m1, c1, m2, c2;
	m1 = l1.m; c1 = l1.c;
	m2 = l2.m; c2 = l2.c;
	
	point sol;
	sol.x = (c2 - c1) / (m1 - m2);
	sol.y = (m2*c1 - m1*c2) / (m2 - m1);
	return sol;
}

int give_appropriate_point(vector<point> &sol, point &Q)
{
	point cursol, curmin;
	int i;
	for(i=0; i<sol.size(); i++)
	{
		cursol = sol[i];
		if(cursol.x > Q.x)
			break;
	}
	
	curmin = cursol;
	int curminind = i;
	
	for(int j=0; j<sol.size(); j++)
	{
		if(j != i)
		{
			cursol = sol[j];
			if(cursol.x < curmin.x && cursol.x > Q.x)
			{
				curmin = cursol;
				curminind = j;
			}
		}
	}
	return curminind;
}

void print_boundary(vector<boundary> &contour)
{
	cout<<"Printing obtained visible region ..."<<endl;
	boundary temp;
	point p1, p2;
	for(int i=0; i<contour.size(); i++)
	{
		temp = contour[i];
		p1 = temp.begin;
		p2 = temp.end;
		cout<<"Line\t"<<temp.lineno<<": From ("<<p1.x<<","<<p1.y<<")"<<" to ("<<p2.x<<","<<p2.y<<")"<<endl;
	}
}

void method1(vector<line> &lines)
{
	const double minus_inf = -std::numeric_limits<double>::max(); //MINUS_INFINITY
	const double inf = std::numeric_limits<double>::max(); //PLUS_INFINITY
	point Q, Qplus;
	Qplus.x = inf; Qplus.y = inf;
	Q.x = minus_inf; Q.y = 0;
	int n = lines.size();
	vector<int> visited(n);
	
	int start = smallest_slope_line(lines);
	line K;
	visited[start] = 1;
	point cursol, curmin;
	int pidx, lidx;
	vector<boundary> contour; //stores the boundary line no. along with end points
	boundary temp;
	while(1)
	{
		//cout<<"start = "<<start<<endl;
		K = lines[start];
		vector<point> sol;
		for(int i=0; i<lines.size(); i++)
		{
			if(visited[i] == 0 && i != start)
			{
				cursol = intersection_point(K, lines[i]);
				cursol.lineno = i;
				if(cursol.x >= Q.x)
					sol.push_back(cursol);
			}
		}
		if(sol.size() == 0)
		{
			temp.lineno = start;
			temp.begin = Q;
			temp.end = Qplus;
			contour.push_back(temp);
			break;
		}
		pidx = give_appropriate_point(sol, Q);
		lidx = sol[pidx].lineno;
		visited[lidx] = 1;
		temp.lineno = start;
		temp.begin = Q;
		temp.end = sol[pidx];
		contour.push_back(temp);
		
		start = lidx;
		Q = sol[pidx];
	}
	print_boundary(contour);
}

void merge(vector<line> &lines, int start, int mid, int end)
{
	if(start >= end)
		return;
	int n1, n2; //sizes of the two auxiliary merging arrays
	n1 = mid - start + 1;
	n2 = end - mid;
	int i, j, k;
	
	vector<line> L(n1);
	vector<line> R(n2);
	
	for(i=0; i<n1; i++)
		L[i] = lines[start+i];
	for(i=0; i<n2; i++)
		R[i] = lines[mid+1+i];
		
	i = 0;
	j = 0;
	k = start;
	
	while(i < n1 && j < n2)
	{
		if(L[i].m <= R[j].m)
		{
			lines[k] = L[i];
			i++;
		}
		else
		{
			lines[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1)
	{
		lines[k] = L[i];
		i++;
		k++;
	}
	while(j < n2)
	{
		lines[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(vector<line> &lines, int start, int end)
{
	if(start >= end)
		return;
	int mid = start + (end - start) / 2;
	mergesort(lines, start, mid);
	mergesort(lines, mid+1, end);
	
	merge(lines, start, mid, end);
}

typedef struct _stacknode
{
	line ln;
	boundary b1;
}stnode;

void method2(vector<line> &lines)
{
	const double minus_inf = -std::numeric_limits<double>::max(); //MINUS_INFINITY
	const double inf = std::numeric_limits<double>::max(); //PLUS_INFINITY
	point Q, Qplus;
	Qplus.x = inf; Qplus.y = 0;
	Q.x = minus_inf; Q.y = 0;
	stnode top, temp;
	
	line K = lines[0], curline, curseg;
	stack<stnode> S;
	
	temp.ln = K;
	temp.b1.lineno = K.index;
	//cout<<"bfd = "<<temp.b1.lineno<<endl;
	temp.b1.begin= Q;
	temp.b1.end = Q;
	
	S.push(temp);
	
	
	line l1, l2;
	point cursol, curQ;
	
	for(int i=1; i<lines.size(); i++)
	{
		curline = lines[i];
		//cout<<"curline num = "<<curline.index<<endl;
		top = S.top();
		curQ = top.b1.begin;
		
		l1 = curline;
		l2 = top.ln;
		cursol = intersection_point(l1, l2);
		cout<<"curq.x = "<<curQ.x<<endl;
		cout<<"x, y = "<<cursol.x<<","<<cursol.y<<endl;
		while(cursol.x < curQ.x && !S.empty())
		{
			S.pop();
			//cout<<"Hi1"<<endl;
			top = S.top();
			//cout<<"Hi2"<<endl;
			curQ = top.b1.end;
			//cout<<"Hi3"<<endl;
			l2 = top.ln;
			//cout<<"Hi4"<<endl;
			cursol = intersection_point(l1, l2);
			//cout<<"x, y = "<<cursol.x<<","<<cursol.y<<endl;
		}
		
		S.pop();
		top.b1.end = cursol;
		S.push(top);
		
		temp.ln = curline;
		temp.b1.lineno = curline.index;
		temp.b1.begin = cursol;
		temp.b1.end = Qplus;
		S.push(temp);
	}
	
	vector<boundary> contour(S.size());
	for(int i=0; i<S.size(); i++)
	{
		top = S.top();
		S.pop();
		contour[S.size()-1-i] = top.b1;
	}
	print_boundary(contour);
}

int main()
{
	int n;
	cout<<"n = "; cin>>n;
	vector<line> lines;
	double slope, intr;
	cout<<"Give m & c for "<<n<<" lines ..."<<endl;
	for(int i=0; i<n; i++)
	{
		cin>>slope>>intr;
		line node;
		node.index = i; node.m = slope; node.c = intr;
		lines.push_back(node);
	}
	printlines(lines);
	cout<<endl<<"+++Method 1"<<endl;
	method1(lines);
	
	cout<<endl<<"Sorting lines ..."<<endl;
	mergesort(lines, 0, lines.size()-1);
	
	printlines(lines);
	
	cout<<endl<<"+++Method 2"<<endl;
	method2(lines);
	
	
	return 0;
}
