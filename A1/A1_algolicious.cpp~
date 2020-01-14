/*
	Assignment- 1- Part 2
	   Swagatam Haldar
		  16EE10063
	       14/1/20
*/

#include <iostream>

using namespace std;

int linsearch(int a[], int n, int val)
{
	for(int i=0; i<n; i++)
		if(a[i] == val)
			return i;
}

int method0(int A[], int n)
{
	int a, b, c, i, j, k;
	for(a = 1; a <= n; a++)
	{
		for(b = a+1; b <= n; b++)
		{
			for(c = b+1; c <= n; c++)
			{
				i = linsearch(A,n,c);
				j = linsearch(A,n,a);
				k = linsearch(A,n,b);
				if(i<j && j<k)
					return 0;
			}
		}
	}
	return 1;
}

int method1(int A[], int n)
{
	int a, b, c;
	for(int i=0; i<n; i++)
	{
		for(int j=i+1; j<n; j++)
		{
			for(int k=j+1; k<n; k++)
			{
				c = A[i]; a = A[j]; b = A[k];
				if(a < b && b < c)
					return 0;
			}
		}
	}
	return 1;
}

int method2(int A[], int n)
{
	int c, curc;
	for(int i=0; i<n; i++)
	{
		c = A[i];
		curc = c;
		for(int j=i+1; j<n; j++)
		{
			if(A[j] < c)
			{
				if(A[j] < curc)
					curc = A[j];
				else
					return 0;
			}
			
		}
	}
	return 1;
}

int method3(int A[], int n)
{
	int curmax, i;
	curmax = A[0];
	i = 1;
	/*while(i < n)
	{
		if(A[i] < curmax)
			i++;
		else
		{
			 
		}
	}*/
	return -1;
}



int main()
{
	//int n;
	//cout<<" n = "; cin>>n;
	//int *A = new int[n];
	int a[] = {3, 5, 8, 7, 6, 12, 14, 16, 15, 18, 21, 25, 24, 23, 22, 20, 19, 17, 13, 11, 10, 9, 4, 2, 1};
	//int n = 25;
	int b[] = {8, 19, 9, 4, 25, 5, 7, 2, 6, 10, 11, 12, 13, 14, 15, 16, 17, 21, 18, 3, 20, 23, 24, 22, 1};
	int c[] = {3,4,5,2,6,7,9,8,1,10};
	int d[] = {3,4,5,1,6,7,9,8,2,10};
	/*cout<<"Method 0: "<<endl;
	cout<<method0(a,25)<<","<<method0(b,25)<<","<<method0(c,10)<<","<<method0(d,10)<<endl;
	cout<<"Method 1: "<<endl;
	cout<<method1(a,25)<<","<<method1(b,25)<<","<<method1(c,10)<<","<<method1(d,10)<<endl;
	cout<<"Method 2: "<<endl;
	cout<<method2(a,25)<<","<<method2(b,25)<<","<<method2(c,10)<<","<<method2(d,10)<<endl;
	cout<<"Method 3: "<<endl;
	cout<<method3(a,25)<<","<<method3(b,25)<<","<<method3(c,10)<<","<<method3(d,10)<<endl;*/
	
	int n;
	cout<<"n = "; cin>>n;
	int *A = new int[n];
	int size = n;
	int j=0;
	cout<<"Give elements(space separated integers) = ";
	while(j<n)
	{
		cin>>A[j++];
	}
	cout<<" Your sequence : "<<endl;
	for(int i=0; i<n; i++)
		cout<<A[i]<<" ";
	cout<<endl;
	cout<<"Method 0: ";
	if(method0(A,n))
		cout<<"Algolicious"<<endl;
	else
		cout<<"Unalgolicious"<<endl;
		
	cout<<"Method 1: ";
	if(method1(A,n))
		cout<<"Algolicious"<<endl;
	else
		cout<<"Unalgolicious"<<endl;
		
	cout<<"Method 2: ";
	if(method2(A,n))
		cout<<"Algolicious"<<endl;
	else
		cout<<"Unalgolicious"<<endl;
	
	cout<<"Method 3: ";
	if(method3(A,n) == 1)
		cout<<"Algolicious"<<endl;
	else if(method3(A,n) == 0)
		cout<<"Unalgolicious"<<endl;
	else
		cout<<"Could not Implement! :("<<endl;
	return 0;
}
