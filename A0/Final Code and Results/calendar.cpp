/***********************
*                      *
*   07/01/2020, 22:08  *
*     Assignment 0     *
*   Algo Lab, SP2020   *
*    Swagatam Haldar   *
*                      *
***********************/
#include <iostream>
#include <vector>
#include <iomanip>

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
			// allnodes[i][j]->date = count++;
			allnodes[i][j]->date = 0;
		}
	}
	return allnodes;
}

/*void printallnodes(gridptr allnodes, int r, int c)
{
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			cout<<allnodes[i][j]->date<<"\t";
		}
		cout<<endl;
	}
}*/

mesh initcal()
{
	int r, c;
	r = 20;
	c = 21;
	gridptr all = give_grid(r,c);
	//printallnodes(all,r,c);
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
		if(year % 4 == 0 || year % 400 == 0)
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
	// cout<<"root val = "<<root->date<<endl;
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
			temp->date = dayc;
			if(dayc == days)
			{
				// cout<<"counter = "<<counter<<endl;
				return counter;
			}
			dayc++;
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

void print_month(mesh C, int month, int year)
{
	vector<string> names(12);
	names[0] = "January"; names[4] = "May"; names[8] = "September";
	names[1] = "February"; names[5] = "June"; names[9] = "October"; 
	names[2] = "March"; names[6] = "July"; names[10] = "November";
	names[3] = "April"; names[7] = "August"; names[11] = "December";

	cout<<"\t\t"<<names[month]<<" "<<year<<" Calendar"<<endl;
	int row, col;
	row = month / 3;
	row *= 5;
	col = month % 3;
	col *= 7;

	mesh root = C;
	while(row--)
		root = root->down;
	while(col--)
		root = root->right;
	cout<<"Su"<<"\t"<<"Mo"<<"\t"<<"Tu"<<"\t"<<"We"<<"\t"<<"Th"<<"\t"<<"Fr"<<"\t"<<"Sa"<<endl;

	mesh rootcopy = root;
	mesh temp = root;

	int weeks = 5;
	int val;
	while(weeks--)
	{
		for(int days = 1; days <= 7; days++)
		{
			val = temp->date;
			if(val == 0)
				cout<<""<<"\t";
			else
				cout<<val<<"\t";
			temp = temp->right;
		}
		temp = rootcopy->down;
		rootcopy = rootcopy->down;
		cout<<endl;
	}
	cout<<endl;
}

int main()
{
	// gridptr all = give_grid(4,5);
	// printallnodes(all,4,5);
	mesh C = initcal();
	// cout<<"Printing Calendar Raw: "<<endl;
	// print_calendar(C);
	int year = 2020;
	int start_day_of_jan = 3; // {0,1,2,3,4,5,6} For Sunday to Saturday.
	// int counter = storemonth(C,0,3,2020);
	int counter = storemonth(C,0,start_day_of_jan,year);
	for(int i=1; i<=11; i++)
	{
		counter = storemonth(C,i,(7-counter)%7,year);
		// cout<<"i = "<<i<<" done, "<<"main counter = "<<counter<<endl;
	}
	// print_calendar(C);
	// print_month(C,0,year);
	for(int i=0; i<12; i++)
		print_month(C,i,year);
	return 0;
}