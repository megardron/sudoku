#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "sudoku.h"

//Makes a single little box in the sudoku.
Box *box_construct(int value, Box *left,Box *right,Box *up,Box *down)
{
    Box *p = malloc(sizeof(Box));
    assert (p);
    p->value = value;
    p->left = left;
	p->right = right;
	p->up = up;
	p->down = down;
    return p;
}

//Constructs the entire thing of boxes.
Box *grid_construct(void)
{
	Box *head = box_construct(0,NULL,NULL,NULL,NULL);
	for (int i=0;i<8;i++)
	{
		head=box_construct(0,NULL,head,NULL,NULL);
		head->right->left=head;
	}
	Box *temp = head;
	for (int i=0;i<8;i++)
	{
		head=box_construct(0,NULL,NULL,NULL,head);
		head->down->up=head;
	}
	for (int i=0;i<8;i++)
	{
		temp = temp->up;
		for (int j=0;j<8;j++)
		{
			temp->right=box_construct(0,temp,NULL,NULL,temp->down->right);
			temp= temp->right;
			temp->down->up=temp;
		}
		while (temp->left!=NULL)
		{
			temp = temp->left;
		}
	}
	return head;
}
//Destroys the grid, freeing the memory etc.
void destroy_grid(Box *head)
{
	Box *temp;
	while (head!=NULL)
	{
		temp = head;
		head = head->down;
		while (temp->right != NULL)
		{
			temp = temp->right;
			free (temp->left);
			temp->left=NULL;
		}
		free(temp);
		temp = NULL;
	}
}


//Used to set up the specific problem you're solving.
void add_preset(int n,int pos,Box *head)
{
	int y = pos-(pos/10*10);
	int x = pos/10;
	Box *temp = head;
	for (int i=1;i<x;i++)
	{
		temp = temp->down;
	}
	for (int i=1;i<y;i++)
	{
		temp = temp->right;
	}
	temp->value=n;
	return;
}


//Returns true if the number is in the row. Returns false if it is not.
_Bool is_row(int n,Box *head)
{
	
	while (head->left != NULL)	
	{
		head = head->left;
	}
	while (head!=NULL)
	{
		if (head->value==n)
		{
			return true;
		}
		head=head->right;
	}
	return false;
}

//Returns true if the number is in the column, false if it is not.
_Bool is_column(int n,Box *head)
{
	while (head->up != NULL)	
	{
		head = head->up;
	}
	while (head!=NULL)
	{
		if (head->value==n)
		{
			return true;
		}
		head=head->down;
	}
	return false;
}


//Tells you where the box is relative the smaller box it's in.
int box_pos(Box *head)
{
	Box *temp = head;
	int count = 0;
	while (temp!=NULL)
	{
		count++;
		temp = temp->left;
	}
	while (count>3)
	{
		count = count-3;
	}
	temp = head;
	while (temp!=NULL)
	{
		count = count+10;
		temp = temp->up;
	}
	while (count>33)
	{
		count = count-30;
	}
	return count;
}


//Determines if the number is already in the box
_Bool is_box(int n,Box *head,int pos)
{
	Box *temp = head;
	if (pos<15)
	{
		if (pos==12)
		{
			temp = temp->left;
		}
		if (pos==13)
		{
			temp = temp->left->left;
		}
	}
	else if (pos<25)
	{
		temp = temp->up;
		if (pos==22)
		{
			temp = temp->left;
		}
		if (pos==23)
		{
			temp = temp->left->left;
		}
	}
	else
	{
		temp = temp->up->up;
		if (pos==32)
		{
			temp = temp->left;
		}
		if (pos==33)
		{
			temp = temp->left->left;
		}
	}
	Box *home = temp;
	for (int i=0;i<3;i++)
	{
		
		for (int j=0;j<3;j++)
		{
			if (temp->value==n)
			{
				return true;
			}
			temp = temp->right;
		}
		home = home->down;
		temp = home;
	}
	return false;
}

//Absorbs previously defined functions into one true/false statement, functionally useless but yeah...
_Bool is_valid(int n,Box *head)
{
	if (is_row(n,head)||is_column(n,head)||is_box(n,head,box_pos(head)))
		return false;
	return true;
}

//Tells you if you've reached the end of the row.
_Bool is_end_row(Box *head)
{
	return head->right==NULL;
}

_Bool is_end_column(Box *head)
{
	return head->down==NULL;
}


void solve(Box *head,int *count, Box *top)
{
	assert(head);
	//print_grid(top);
	//printf("\n\n");
	if (is_end_column(head) && is_end_row(head))
	{
		if (!head->value)
		{
			for (int i=1;i<10;i++)
			{
				if (is_valid(i,head))
				{
					head->value=i;
					print_grid(top);
					printf("\n\n");
					//printf("\n%i\n",*count);
					*count+=1;
				}
			}
			head->value=0;
			return;
		}
		print_grid(top);
		printf("\n\n");
		//printf("\n%i\n",*count);
		*count+=1;
		return;
	}
	else if (!is_end_row(head))
	{
		if (!head->value)
		{
			for (int i=1;i<10;i++)
			{
				if(is_valid(i,head))
				{
					head->value = i;
					solve(head->right,count,top);
					//printf("Sigh...\n");
					//print_grid(top);
				}
				//printf("i");
			}
			//print_grid(top);
			//printf("She's dead Jim.\n");
			head->value=0;
			return;
		}
		solve(head->right,count,top);
		return;
	}
	else
	{
		if (!head->value)
		{
			for(int i=1;i<10;i++)
			{
				if (is_valid(i,head))
				{
					head->value = i;
					Box *temp = head;
					while (temp->left!=NULL)
					{
						temp = temp->left;
					}
					solve(temp->down,count,top);
					//printf("fuck the police\n");
				}
			}
			//printf("Hella.\n");
			head->value=0;
			return;
		}
		Box *temp = head;
		while (temp->left!=NULL)
		{
			temp = temp->left;
		}
		solve(temp->down,count,top);
		//printf("NOPE\n");
		return;
	}
}



