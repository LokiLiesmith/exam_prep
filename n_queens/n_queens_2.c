#include <stdio.h>
#include <stdlib.h>


void print_solution(int *board, int n)
{
	int i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int is_safe(int *board, int col, int row)
{
	int prev = 0;
	
	while (prev < col)
	{
		int prow = board[prev];
		if (prow == row) //same row check
			return (0);
		if (prow - row == prev - col || prow - row == -1 * (prev - col))	//diagonal check diff == diff y, means they are on a diagonal,
																			//  *-1 for the opposite side, you dont need to check up because
																			// youre going from top to bottom anyway
			return (0);
		prev++;
	}
	return (1);
}

void backtrack(int *board, int col, int n)
{
	int row;
	
	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if(is_safe(board, col, row))
		{
			board[col] = row;				//make a choice - place the first queen into the array
			backtrack(board, col + 1, n);	//backtrack		- runs the same shit but for the next square until col = n
		}
		row++;
	}
}

void solve_n_queens(int n)
{
	int *board;
	board = calloc(n, sizeof(int));//create a board, its an int array
	if(!board)
		return;
	backtrack(board, 0, n);
	free(board);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		solve_n_queens(atoi(av[1]));
	return (0);
}