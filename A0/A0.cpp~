/*	Algorithms Laboratory Assignment 0 *
*       Swagatam Haldar, 16EE10063     *
*         5:02 pm, 07/01/2020          *
*/
#include <iostream>

using namespace std;

typedef struct _node
{
	int date;
	struct _node *right;
	struct _node *down;
	
	_node()
	{
		date = 0;
		right = NULL;
		down = NULL;
	}
}node;

typedef node* mesh;
typedef mesh* grid;
typedef grid* gridptr;

gridptr give_grid(int r, int c)
{
	gridptr allnodes = new grid[r];
	for(int i=0; i<r; i++)
		allnodes[i] = new mesh[c];
	int count = 1;
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			allnodes[i][j] = new node;
			allnodes[i][j]->date = count++;
		}
	}
	return allnodes;
}

void printallnodes(gridptr allnodes, int r, int c)
{
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout<<allnodes[i][j]->date<<"\t";
		}
		cout<<endl;
	}
}

mesh initcal()
{
	int r, c;
	r = 20;
	c = 21;
	gridptr all = give_grid(r,c);
	//printallnodes(all,4,4);
	//mesh C = all[0][0];
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			if(i == r-1 && j == c-1)
			{
			}
			else if(i != r-1 && j == c-1)
			{
				all[i][j]->down = all[i+1][j];
				all[i][j]->right = NULL;
			}
			else if(i == r-1 && j != c-1)
			{
				all[i][j]->right = all[i][j+1];
				all[i][j]->down = NULL;
			}
			else
			{
				all[i][j]->right = all[i][j+1];
				all[i][j]->down = all[i+1][j];
			}
		}
	}
	return all[0][0];
}

void print_calendar(mesh C)
{
	if(C == NULL)
		return;
	mesh h = C;
	while(h != NULL)
	{
		cout<<h->date<<"\t";
		h = h->right;
	}
	cout<<endl;
	print_calendar(C->down);
}

int storemonth(mesh C, int month, int start, int year)
{
	int days;
	if(month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
	days = 31;
	else if(month == 1)
	{
		if(year % 4 == 0 || year % 100 ==0)
			days = 29;
		else
			days = 28;
	}
	else
		days = 30;
	int x = month/3;
	int y = month%3;
	x *= 5;
	y *= 7;
	//y += start;
	mesh root = C;
	while(x--)
		root = root->down;
	while(y--)
		root = root->right;
	mesh temp = root;
	cout<<"root val = "<<root->date<<endl;
	int counter = 7;
	while(start--)
	{
		temp->date = 0;
		temp = temp->right;
		counter--;
	}
	int dayc = 1;
	int row = 1;
	mesh rootcopy = root;
	while(1)
	{
		
		while(counter--)
		{
			temp->date = dayc++;
			if(dayc == days)
			{
				cout<<"counter = "<<counter<<endl;
				return counter;
			}
			temp = temp->right;
		}
		counter = 7;
		row++;
		if(row > 5)
			temp = root;
		else
		{
			temp = rootcopy->down;
			rootcopy = rootcopy->down;
		}
	}
	return 0;
}

int main()
{
	//gridptr all = give_grid(4,5);
	//printallnodes(all,4,5);
	mesh C = initcal();
	cout<<"Printing Calendar Raw: "<<endl;
	print_calendar(C);
	int counter = storemonth(C,0,3,2020);
	for(int i=1; i<=11; i++)
	{
		counter = storemonth(C,i,7-counter+1,2020);
		cout<<"main counter = "<<counter<<endl;
	}
	print_calendar(C);
	return 0;
}




/*void print_node(mesh head)
{
	cout<<"val = "<<head->date<<endl;
}

void printij(int i, int j)
{
	cout<<"i = "<<i<<" j = "<<j<<endl;
}

mesh create_mesh(mesh head, int i, int j, int r, int c)
{
	if(head != NULL)
		return head;
	if(i == r-1 && j == c-1)
	{
		printij(i,j);
		return NULL;
	}
	head = new node;
	printij(i,j);
	print_node(head);
	if(i == r-1 && j != c-1)
	{
		head->down = NULL;
		head->right = create_mesh(head->right,i, j+1, r, c);
		return head;
	}
	else if(j == c-1 && i != r-1)
	{
		head->right = NULL;
		head->down = create_mesh(head->down, i+1, j, r, c);
		return head;
	}
	else
	{
		head->right = create_mesh(head->right, i, j+1, r, c);
		head->down = create_mesh(head->down, i+1, j, r, c);
		return head;
	}
}

mesh initcal()
{
	mesh C;
	mesh visited
	C = create_mesh(C,0,0,3,3);
	//print_node(C);
	return C;
}

int main()
{
	mesh C = initcal();
	print_node(C);
	return 0;
}*/
