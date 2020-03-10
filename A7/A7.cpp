//Swagatam Haldar, 16EE10063, Assignment- 7
#include <iostream>
#include <vector>

using namespace std;

int fact(int n); 
  
int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 
  
// Returns factorial of n 
int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
}

int countseq(vector<int> &A, int n)
{
	if(n <= 2)
		return 1;
	vector<int> AL;
	vector<int> AR;
	int root = A[0];
	for(int i=1; i<n; i++)
	{
		if(A[i] < root)
			AL.push_back(A[i]);
		else
			AR.push_back(A[i]);
	}
	int l,r;
	l = AL.size();
	r = AR.size();
	return countseq(AL, l) * countseq(AR, r) * nCr(n-1, l);
}

void findallhelper(vector<vector<int> > &seq, vector<int> &AL, vector<int> &AR, int n, vector<int> B)
{
	if(B.size() == n-1)
	{
		//for(int i=0; i<n-1; i++)
			//cout<<B[i]<<" ";
		//cout<<endl;
		int c0, c1;
		for(int i=0; i<n-1; i++)
		{
			if(B[i] == 0)
				c0++;
			else
				c1++;
		}
		if(c0 == AL.size()-1)
		{
			vector<int> vec(n);
			vec[0] = AL[0];
			int li = 1, ri = 0;
			for(int i=0; i<n-1; i++)
			{
				if(B[i] == 0)
					vec[i+1] = AL[li++];
				else
					vec[i+1] = AR[ri++];
			}
			for(int i=0; i<n; i++)
				cout<<vec[i]<<" ";
			cout<<endl;
			//cout<<"pushed vec bef"<<endl;
			seq.push_back(vec);
			//cout<<"pushed vec"<<endl;
		}
		return;
	}
	B.push_back(0);
	findallhelper(seq, AL, AR, n, B);
	B[B.size()-1] = 1;
	findallhelper(seq, AL, AR, n, B);
}

vector<vector<int> > findallseq(vector<int> A, int n)
{
	if(n <= 2)
	{
		vector<vector<int> > seq;
		seq.push_back(A);
		return seq;
	}
	vector<vector<int> > seql;
	vector<vector<int> > seqr;
	vector<int> AL;
	vector<int> AR;
	for(int i=1; i<n; i++)
	{
		if(A[i] < A[0])
			AL.push_back(A[i]);
		else
			AR.push_back(A[i]);
	}
	int n1 = AL.size();
	int n2 = AR.size();
	seql = findallseq(AL, n1);
	seqr = findallseq(AR, n2);
	
	int l, r;
	l = AL.size();
	r = AR.size();
	vector<vector<int> > seq;
	
	vector<int> B;
	for(int i=0; i<seql.size(); i++)
	{
		for(int j=0; j<seqr.size(); j++)
		{
			vector<int> al = seql[i];
			al.insert(al.begin(), A[0]);
			vector<int> ar = seqr[j];
			vector<int> B;
			findallhelper(seq, al, ar, n, B);
		}
	}
	return seq;
}

void printvec(vector<int> &vec)
{
	for(int i=0; i<vec.size(); i++)
		cout<<vec[i]<<" ";
	cout<<endl;
}

typedef struct _node
{
	int key;
	struct _node *left;
	struct _node *right;
	
	_node()
	{
		key = 0;
		left = NULL;
		right = NULL;
	}
}node;

typedef node* tree;

tree BSTins(tree T, int x)
{
	if(T == NULL)
	{
		T = new node;
		T->key = x;
		return T;
	}
	else if(T->key > x)
		T->left = BSTins(T->left, x);
	else
		T-> right = BSTins(T->right, x);
	return T;
}

tree BSTcons(vector<int> &A, int n)
{
	tree T = NULL;
	for(int i=0; i<n; i++)
	{
		T = BSTins(T, A[i]);
	}
	return T;
}

void preorder(tree &T)
{
	if(T == NULL)
		return;
	cout<<T->key<<" ";
	preorder(T->left);
	preorder(T->right);
}

void inorder(tree &T)
{
	if(T == NULL)
		return;
	inorder(T->left);
	cout<<T->key<<" ";
	inorder(T->right);
}

void BSTprn(tree &T)
{
	cout<<"--- Preorder :"<<endl;
	preorder(T);
	cout<<endl<<"--- Inorder :"<<endl;
	inorder(T);
	cout<<endl<<endl;
}

int BSTsame(tree &T1, tree &T2)
{
	if(T1 == NULL && T2 == NULL)
		return 1;
	if((T1 == NULL && T2 != NULL) || (T1 != NULL && T2 == NULL))
		return 0;
	if(T1->key != T2->key)
		return 0;
	return BSTsame(T1->left, T2->left) * BSTsame(T1->right, T2->right);
}

void BSTfree(tree T)
{
	if(T == NULL)
		return;
	BSTfree(T->left);
	BSTfree(T->right);
	delete T;
}

void checkall(tree T, vector<vector<int> > &seq)
{
	int count = 0;
	for(int i=0; i<seq.size(); i++)
	{
		tree Tn = BSTcons(seq[i], seq[i].size());
		if(BSTsame(T, Tn))
		{
			//cout<<"     Sequence "<<i+1<<" trees match!"<<endl;
			count++;
		}
		BSTfree(Tn);
	}
	cout<<"count = "<<count<<endl;
	if(count == seq.size())
		cout<<"    All trees match! Yay!"<<endl;
}

int main()
{
	int n;
	cin>>n;
	vector<int> A(n);
	for(int i=0; i<n; i++)
		cin>>A[i];
	int c = countseq(A,n);
	cout<<"+++ Sequence count"<<endl;
	cout<<"    Total num. of sequences = "<<c<<endl<<endl;
	
	vector<int> B;
	int l=0, r=0;
	vector<int> AL;
	vector<int> AR;
	for(int i=0; i<n; i++)
	{
		if(A[i] <= A[0])
			AL.push_back(A[i]);
		else
			AR.push_back(A[i]);
	}
	l = AL.size();
	r = AR.size();
	vector<vector<int> > seq = findallseq(A,n);
	cout<<"+++ All sequences"<<endl;
	for(int i=seq.size()-1; i>=0; i--)
	{
		cout<<"Sequence "<<seq.size()-i<<"\t:";
		printvec(seq[i]);
	}
	cout<<"+++ generated seqs = "<<seq.size()<<endl<<endl;
	
	tree T = BSTcons(A, n);
	cout<<"+++ BST constructed from input array"<<endl;
	BSTprn(T);
	cout<<endl;
	
	cout<<"+++ Checking all sequences "<<endl;
	checkall(T, seq);
	BSTfree(T);
	
	return 0;
}
