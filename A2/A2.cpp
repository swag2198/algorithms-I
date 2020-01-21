//16EE10063, Swagatam Haldar, Assignment 2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct _node
{
	int n1;
	string expr;
}node; //this structure is used to store string with its no. of 1s for sorting

//sign = 0 for addition and 1 for multiplication

int checkbrackets(string str)
{
	int flag = 0;
	int bopen = 0;
	for(int i=0; i<str.length(); i++)
	{
		if(str[i] == '(')
		{
			if(bopen == 0)
				bopen = 1;
		}
		if(str[i] == ')')
		{
			bopen = 0;
		}
		if(str[i] == '+')
		{
			if(bopen == 0)
			{
				flag = 1;
				return flag;
			}
			else
				flag = 0;
		}
	}
	return 0;
}

void merge_and_push(vector<string> &l1, vector<string> &l2, vector<string> &list, int sign)
{
	int n1, n2;
	string s1, s2, str;
	n1 = l1.size();
	n2 = l2.size();
	int flag;
	for(int k = 0; k < n1; k++)
	{
		s1 = l1[k];
		for(int l = 0; l < n2; l++)
		{
			s2 = l2[l];
			
			if(sign == 0)
			{
				str = s1 + "+" + s2;
				flag = 0;
				for(int i=0; i<list.size(); i++)
				{
					if(list[i] == str)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
					list.push_back(str);
			}
			else
			{
				//str = "("+s1+")"+"x"+"("+s2+")";
				int f1, f2;
				f1 = checkbrackets(s1);
				f2 = checkbrackets(s2);
				if(f1 && f2)
					str = "("+s1+")"+"x"+"("+s2+")";
				else if(f1 == 1 && f2 == 0)
					str = "("+s1+")"+"x" +s2;
				else if(f1 == 0 && f2 == 1)
					str = s1+"x" +"("+s2+")";
				else
					str = s1+"x" +s2;
				flag = 0;
				for(int i=0; i<list.size(); i++)
				{
					if(list[i] == str)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
					list.push_back(str);
			}
		}
	}
}

vector<string> findallexpr(int n)
{
	vector<string> list;
	int n1, n2;
	string s1, s2, str;
	vector<string> l1, l2;
	if(n == 1)
	{
		str = "1";
		list.push_back(str);
		return list;
	}
	for(int i = 1; i <= n-1; i++)
	{
		for(int j = i; j <= n-1; j++)
		{
			if(i+j == n)
			{
				l1 = findallexpr(i);
				l2 = findallexpr(j);
				merge_and_push(l1, l2, list,0);
			}
			if(i * j == n && (i != 1 || j != 1))
			{
				//cout<<"i = "<<i<<"j = "<<j<<endl;
				l1 = findallexpr(i);
				l2 = findallexpr(j);
				merge_and_push(l1, l2, list,1);
			}
		}
	}
	return list;
}

void printallexpr(vector<string> &list)
{
	cout<<"Printing all the expressions ..."<<endl;
	for(int i=0; i<list.size(); i++)
		cout<<i+1<<": "<<list[i]<<endl;
	cout<<endl;
}

void printallexprsorted(vector<node> &list)
{
	cout<<"Printing all the expressions in sorted order..."<<endl;
	for(int i=0; i<list.size(); i++)
		cout<<i+1<<": "<<list[i].expr<<endl;
	cout<<endl;
}

int count_ones(string str)
{
	int c = 0;
	for(int i=0; i<str.length(); i++)
		if(str[i] == '1')
			c++;
	return c;
}

int swap(vector<node> &A, int i, int j)
{
	node temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int partition(vector<node> &A, int start, int end)
{
	int i, j, k;
	i = start;
	j = start;
	k = end;
	while(j <= k)
	{
		if(A[j].n1 == A[i].n1)
			j++;
		else if(A[j].n1 < A[i].n1)
		{
			swap(A,i,j);
			j++;
			i++;
		}
		else
		{
			swap(A,j,k);
			k--;
		}
	}
	return i;
}

void quicksort(vector<node> &A, int start, int end)
{
	if(start >= end)
		return;
	int p = partition(A,start,end);
	quicksort(A,start,p-1);
	quicksort(A,p+1,end);
}

void print_vector(vector<node> &A)
{
	cout<<"Printing numones vector ..."<<endl;
	for(int i=0; i<A.size(); i++)
		cout<<A[i].n1<<",";
	cout<<endl<<endl;
}

int main()
{
	int n, c;
	cout<<"n = "; cin>>n;
	vector<string> list;
	list = findallexpr(n);
	
	printallexpr(list);
	
	vector<node> A(list.size());
	for(int i=0; i<list.size(); i++)
	{
		c = count_ones(list[i]);
		A[i].n1 = c;
		A[i].expr = list[i];
	}
	print_vector(A);
	//print_vector(index);
	quicksort(A,0,A.size()-1);
	cout<<"After sorting indices ..."<<endl;
	print_vector(A);
	printallexprsorted(A);
	cout<<"..."<<A.size()<<" expressions"<<endl;
	
	return 0;
}
