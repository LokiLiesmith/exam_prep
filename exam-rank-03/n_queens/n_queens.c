#include <stdio.h>
#include <stdlib.h>

void	print_solution(int *board, int n)
{
	int i = 0;
	while(i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int is_safe(int *board, int col, int row) //board col row is safe
{
	int prev = 0;

	while (prev < col)
	{
		int prow = board[prev];
		if (prow == row)
			return (0);
		if (prow - row == prev - col || prow - row == ((prev - col) * -1))
			return (0);
		prev ++;
	}
	return (1);
}

void	n_queens(int *board, int col, int n)
{
	if(col == n)
	{
		print_solution(board, n);
		return ;
	}
	int row = 0;
	while (row < n)
	{
		if(is_safe(board, col, row))
		{
			board[col] = row;				//make a choice
			n_queens(board, col + 1, n);	//backtrack
		}

		row++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int n = atoi(av[1]);
	int *board = malloc(sizeof(int) * n);
	n_queens(board, 0, n);
	free(board);
	return (0);
}