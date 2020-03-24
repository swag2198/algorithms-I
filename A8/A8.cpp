//Swagatam Haldar, 16EE10063, Assignment- 8

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _hnode
{
	int len;
	vector<int> a;

	_hnode()
	{
		len = 0;
	}
}hnode;

typedef struct _mheap
{
	int p; //node capacity
	int n; //current num of keys
	int N; //current num of nodes in use also gives index of last node in use
	hnode* array;
}mheap;

mheap initheap(int p_, int nmax)
{
	mheap Q;
	Q.p = p_;
	Q.n = 0;
	Q.N = 0;
	int Nmax = (nmax + p_ -1) / p_;
	Q.array = new hnode[Nmax];
	return Q;
}

int min_vec(vector<int> &v)
{
	int curmin = v[0];
	for(int i=1; i<v.size(); i++)
	{
		if(v[i] < curmin)
			curmin = v[i];
	}
	return curmin;
}

int max_vec(vector<int> &v)
{
	int curmax = v[0];
	for(int i=1; i<v.size(); i++)
	{
		if(v[i] > curmax)
			curmax = v[i];
	}
	return curmax;
}

void insert(mheap &H, int x)
{
	int curkeys, cur_nodes_in_use, q;

	curkeys = H.n;
	cur_nodes_in_use = H.N;

	// cout<<"cur nodes in use = "<<H.N<<endl;

	// cout<<"inserting "<<x<<endl;


	if(H.array[cur_nodes_in_use].len == H.p)
	{
		H.array[cur_nodes_in_use + 1].a.push_back(x);
		H.array[cur_nodes_in_use + 1].len++;
		q = cur_nodes_in_use + 1;
		H.N++;
	}
	else
	{
		H.array[cur_nodes_in_use].a.push_back(x);
		H.array[cur_nodes_in_use].len++;
		q = cur_nodes_in_use;
	}
	H.n++;
	// H.N++;

	vector<int> vq, vr;
	int minr, maxq, r;

	while(1)
	{
		// cout<<"curkeys = "<<H.n
		if(q == 0)
		{
			// cout<<"inserting "<<x<<"done at q == 0"<<endl;
			return;
		}
		r = (q - 1) / 2;

		
		vq = H.array[q].a;
		vr = H.array[r].a;

		minr = min_vec(vr);
		maxq = max_vec(vq);

		if(minr >= maxq)
		{
			// cout<<"inserting "<<x<<"done at q == 0"<<endl;
			return;
		}

		for(int i = 0; i < vr.size(); i++)
			vq.push_back(vr[i]);
		vr.clear();
		
		sort(vq.begin(), vq.end(), greater<int>());

		for(int i=0; i<H.p; i++)
			H.array[r].a[i] = vq[i];

		for(int i = H.p; i<vq.size(); i++)
			vr.push_back(vq[i]);

		H.array[q].a = vr;

		q = r;
	}
	// cout<<"inserting "<<x<<"done"<<endl;
}

void prnheap(mheap &H)
{
	int curkeys, cur_nodes_in_use;

	curkeys = H.n;
	cur_nodes_in_use = H.N;

	vector<int> vec;

	cout<<endl<<"+++ printing multi heap . . ."<<endl;
	for(int i=0; i <= cur_nodes_in_use; i++)
	{
		vec = H.array[i].a;
		cout<<"    [ ";
		for(int j=0; j<vec.size(); j++)
			cout<<vec[j]<<" ";
		cout<<"]"<<endl;
	}
}

void heapify(mheap &H, int i)
{
	int curkeys, cur_nodes_in_use;

	curkeys = H.n;
	cur_nodes_in_use = H.N;

	int lc, rc, qmin, ic, lmax, rmax;
	vector<int> vi, vc;

	while(1)
	{
		lc = 2*i + 1;
		rc = 2*i + 2;

		if(lc > H.N)
			return;

		qmin = min_vec(H.array[i].a);
		// cout<<"qmin = "<<qmin<<endl;
		lmax = max_vec(H.array[lc].a);
		if(rc <= H.N)
			rmax = max_vec(H.array[rc].a);
		else
			rmax = -1; //assuming heap nodes are positive

		// cout<<"lmax = "<<lmax<<" rmax = "<<rmax<<endl;

		if(qmin >= lmax && qmin >= rmax)
			return;

		ic = (qmin < lmax) ? lc : rc;

		// cout<<"ic = "<<ic<<endl;

		vi = H.array[i].a;
		vc = H.array[ic].a;

		for(int j=0; j<vc.size(); j++)
			vi.push_back(vc[j]);
		vc.clear();

		sort(vi.begin(), vi.end(), greater<int>());

		for(int j=0; j<H.p; j++)
			H.array[i].a[j] = vi[j];

		for(int j = H.p; j<vi.size(); j++)
			vc.push_back(vi[j]);

		H.array[ic].a = vc;

		// cout<<"after child swap"<<endl;
		// prnheap(H);

		i = ic;
	}
}

int findmax(mheap &H)
{
	return max_vec(H.array[0].a);
}

vector<int> remove_vec(vector<int> &a, int x)
{
	int k;
	for(int i=0; i<a.size(); i++)
	{
		if(a[i] == x)
		{
			k = i;
			break;
		}
	}

	vector<int> temp;
	for(int i=0; i<a.size(); i++)
	{
		if(i != k)
			temp.push_back(a[i]);
	}
	return temp;
}

void delmax(mheap &H)
{
	int curkeys, cur_nodes_in_use;

	curkeys = H.n;
	cur_nodes_in_use = H.N;

	int maxval = findmax(H);
	int maxind;
	for(int i=0; i < H.array[0].a.size(); i++)
	{
		if(maxval == H.array[0].a[i])
		{
			maxind = i;
			break;
		}
	}
	int last_node_index = H.N;

	if(H.N == 0)
	{
		H.array[0].a = remove_vec(H.array[0].a, maxval);
		H.n--;
		return;
	}

	if(H.array[H.N].len == 1)
	{
		H.array[0].a[maxind] = H.array[H.N].a[0];
		H.array[H.N].len--;
		H.array[H.N].a.clear();
		H.N--;
		H.n--;
	}
	else
	{
		H.array[0].a[maxind] = H.array[H.N].a[H.array[H.N].a.size()-1]; //swap with last elt of last vector
		H.array[H.N].len--;
		H.array[H.N].a = remove_vec(H.array[H.N].a, H.array[H.N].a[H.array[H.N].a.size()-1]);
		H.n--;
	}
	heapify(H,0);
}

int main()
{
	int p_, nmax;
	cin>>p_;
	cin>>nmax;
	int *A = new int[nmax];
	for(int i=0; i<nmax; i++)
		cin>>A[i];

	mheap H = initheap(p_,nmax);
	cout<<"heap initialised ... "<<endl;

	for(int i=0; i<nmax; i++)
		insert(H, A[i]);
	cout<<"+++ "<<nmax<<" Insertions made to the multiheap"<<endl;

	prnheap(H);

	int k = nmax - 1;
	int delcount = 0;

	while(H.n != 0)
	{
		// cout<<findmax(H)<<" ";
		A[k--] = findmax(H);
		delmax(H);
		delcount++;
		// cout<<"+++ after "<<delcount<<" deletions heap is . . ."<<endl;
		// prnheap(H);
		// cout<<endl;
	}

	cout<<endl<<"+++ "<<delcount<<" Deletions made to multiheap"<<endl<<endl;
	cout<<"+++ Input array sorted . . ."<<endl;
	for(int i=0; i<nmax; i++)
		cout<<A[i]<<" ";
	cout<<endl;


	return 0;
}