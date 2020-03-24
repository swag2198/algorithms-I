//Swagatam Haldar, Assignment- 6, 16EE10063

#include <iostream>

using namespace std;

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

tree readtree(int n)
{
	if(n <= 0)
		return NULL;
	int val, n1, n2;
	cin>>val>>n1>>n2;
	
	tree T = new node;
	T->key = val;
	if(n == 1)
	{
		T->left = NULL;
		T->right = NULL;
		return T;
	}

	T->left = readtree(n1);
	T->right = readtree(n2);
	return T;
}

void preorder(tree T)
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

void prntree(tree &T)
{
	cout<<"--- Preorder listing"<<endl;
	preorder(T);
	cout<<endl<<"--- Inorder listing"<<endl;
	inorder(T);
	cout<<endl<<endl;
}

void swapchild(tree &T)
{
	tree temp = T->left;
	T->left = T->right;
	T->right = temp;
}

tree lrotate(tree &T)
{
	tree temp;
	temp = T->right;
	T->right = temp->left;
	temp->left = T;
	return temp;
}

tree rrotate(tree &T)
{
	tree temp;
	temp = T->left;
	T->left = temp->right;
	temp->right = T;
	//cout<<"rot success"<<endl;
	return temp;
}



void makeskew(tree &T)
{
	if(T == NULL || (T->left == NULL && T->right == NULL))
		return;
	if(T->left == NULL)
		makeskew(T->right);
	//tree pre = prev;
	while(T->left != NULL)
	{
		T = rrotate(T);
		/*if(prev != NULL)
		{
			prev->right = T;
			prev = T;
		}*/
		//prev->right = T;
		//prev = T;
	}
	makeskew(T->right);
}

void makeskew2(tree &T, tree &prev)
{
	if(T == NULL)
		return;
	if(T->left == NULL)
	{
		makeskew2(T->right, T);
		return; //This return statement was not there in the erroneous version!
	}
	//tree pre = prev;
	while(T->left != NULL)
	{
		//cout<<"Rotating at root = "<<T->key<<endl;
		T = rrotate(T);
	}
	if(prev != NULL)
	{
		prev->right = T;
	}
	makeskew2(T->right, T);
}


void bsort(tree &T, int &n)
{
	tree root = T, prev;
	for(int i=0; i<n-1; i++)
	{
		root = T;
		for(int j=0; j<n-i-1; j++)
		{
			// cout<<"i = "<<i<<" j = "<<j<<endl;
			// cout<<"inside second loop"<<endl;
			// cout<<"processing rootval begin = "<<root->key<<endl;
			if(root->key > root->right->key)
			{
				// cout<<"swapping "<<root->key<<" and "<<root->right->key<<endl;
				swapchild(root);
				//cout<<"root = "<<root->key<<endl;
				root = rrotate(root);
				//cout<<"root = "<<root->key<<endl;
				
				if(j == 0)
				{
					T = root;
					prev = root;
				}
				else
				{
					prev->right = root;
					prev = root;
				}
				root = root->right;
				//cout<<"root = "<<root->key<<endl;
				swapchild(root);
				//cout<<"root = "<<root->key<<endl;
				//if(root->right != NULL)
					//cout<<"root right = "<<root->right->key<<endl;
				//if(j == 0)
					//T = root;
			}
			else
			{
				prev = root;
				root = root->right;
			}
			//root = root->right;
			// if(root == NULL)
			// 	cout<<"heya"<<endl;
			// cout<<"cur tree root = "<<T->key<<endl;
			// cout<<"processing rootval = "<<root->key<<endl;
			
			// if(i == 6)
			// {
			// 	cout<<"after j = "<<j<<" tree becomes"<<endl;
			// 	if(j == 0 || j==1)
			// 		prntree(T);
			// }
		}
		// cout<<"after i = "<<i<<" tree becomes"<<endl;
		// if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i ==5)
		// 	prntree(T);
	}
}

int check_right_skew(tree &T)
{
	if(T == NULL)
		return 1;
	if(T->left != NULL)
		return 0;
	tree temp;
	temp = T->right;
	while(temp != NULL)
	{
		if(temp->left != NULL)
			return 0;
		temp = temp->right;
	}
	return 1;
}

void rebalance(tree &T)
{
	if(T == NULL || T->right == NULL || T->right->right == NULL)
		return;
	tree start, mid;
	start = T;
	mid = T;
	while(start != NULL)
	{
		if(start->right != NULL)
		{
			start = start->right->right;
			mid = mid->right;
		}
		else
		{
			start = start->right;
			mid = mid;
		}
	}
	tree root = T;
	//cout<<"mid key = "<<mid->key<<endl;
	while(T != mid)
	{
		T = lrotate(T);
	}
	
	cout<<"mid key = "<<mid->key<<endl;
	
	tree lt = T->left;
	tree rt = T->right;
	tree prev = NULL;
	
	makeskew2(lt,prev);
	T->left = lt;
	
	prntree(lt);
	prntree(rt);
	
	rebalance(T->left);
	rebalance(T->right);
	// T->left = lt;
	// T->right = rt;
}

int main()
{
	int n;
	cout<<"n = "; cin>>n;
	tree T = readtree(n);
	cout<<"+++ Initial tree"<<endl;
	prntree(T);
	
	
	cout<<"+++ Tree made skew"<<endl;
	tree pre = NULL;
	//makeskew(T);
	makeskew2(T,pre);
	prntree(T);

	if(check_right_skew(T))
		cout<<"Tree is properly right skewed"<<endl;
	prntree(T);
	
	cout<<"+++ Tree after sorting"<<endl;
	bsort(T,n);
	prntree(T);
	
	cout<<"+++ Tree after rebalancing"<<endl;
	rebalance(T);
	prntree(T);
}

