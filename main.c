#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <assert.h>
#include <stdbool.h>




void print_row(Box *head)
{
	if (head == NULL)
	{
		printf("She's dead Jim.\n");
		return;
	}
	unsigned count = 0;
	while (head !=NULL)
	{
		// The badness
		if (head->value == 0) {
			printf("  ");
		} else {
			printf("%i ",head->value);
		}
		head = head->right;
		if (count == 2 || count == 5) {
			printf("| ");
		}
		++count;
	}
	printf("\n");
	return;
}

void print_column(Box *head)
{
	if (head == NULL)
	{
		printf("She's dead Jim.\n");
		return;
	}
	while (head !=NULL)
	{
		printf("%i\n",head->value);
		head = head->down;
	}
	printf("\n");
	return;
}

void print_grid(Box *head)
{
	for (int i=0;i<9;i++)
		{
			print_row(head);
			head = head->down;
			if (i == 2) {
				printf("--------------|------\n");
			} else if (i == 5) {
				printf("------|--------------\n");
			}
		}
}

int main(void)
{
	Box *head = grid_construct();
	Box *temp = head;
	int count = 0;
	char ans = 'u';
	printf("Do you wish to input a puzzle? Y/N\n");
	scanf("%c",&ans);
	if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n')
			printf("Sorry that is not a valid response, please enter Y for yes or N for no:\n");
	while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n')
	{
		scanf("%c",&ans);
	}
	char str[100];
	char *puzzle = str;
	if (ans == 'y' || ans =='Y')
	{
		printf("Enter the pathway of the puzzle you wish to solve:\n");
		scanf("%s",puzzle);
		printf("%s",puzzle);
	}
	else
	{
		puzzle = "C:\\Users\\Megan\\Dropbox\\C\\Sudoku\\puzzle.txt";
	}
	FILE *f = fopen(puzzle,"r");
	for (int i=1;i<10;i++)
	{
		for (int j=1;j<10;j++)
		{
			int y = 0;
			fscanf(f,"%d",&y);
			if (y>9)
				return -1;
			if (y)
				add_preset(y,j+i*10,head);
		}
	}
	solve(head,&count,head);
	print_grid(head);
	printf("\n%i\n",count);
	destroy_grid(temp);
	ans = 'u';
	printf("Are you finished with the solutions? Type y to quit.\n");
	while (ans!='y'&&ans!='Y')
	{
		scanf("%c", &ans);
	}
	return 0;
}
