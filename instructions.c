///////////////////////////////////////////////////////////////////////////////////
// PERMUTATIONS in n out depth used
void permutations(char *in, int n, char *out, int depth, char *used)
{
	if(depth == n)
	{
		puts(out);
		return ;
	}
	int i = 0;
	while(i < n)
	{
		if(!used[i])
		{
			used[i] = 1;								//MARK
			out[depth] = in[i];							//STORE
			permutations(in, n, out, depth + 1, used);	//
			used[i] = 0;								//ERASE
		}
		i++;
	}
}

void sort_str(char *s)
{
	int i = 0;;

	while (s[i] && s[i + 1])
	{
		if (s[i] > s[i + 1])
		{
			swap(&s[i], &s[i+1]);
			i = 0;
		}
		else
			i++;
	}
}
///////////////////////////////////////////////////////////////////////////////////
//N_QUEENS board col n, is safe board col row
int	is_safe(int *board, int col, int row) /// board[col] = row
{
	int prev = 0;
	
	while (prev < col)
	{
		int prow = board[prev];
		if (prow == row)
			return (0);
		if (prow - row == prev - col || prow - row == col - prev)
			return (0);
		prev ++;
	}
	return (1);
}

n_queens(int *board, int col, int n)
{
	if (col == n)
	{
		print_solutionp();
		return ;
	}
	int row = 0;
	while (row < n)
	{
		if(is_safe(board, col, row))
		{
			board[col] = row;
			n_queens(board, col + 1, n);
		}
		row++;
	}
}
///////////////////////////////////////////////////////////////////////////////////
///POWERSET arr
void powerset(int *arr, int n, int start, int *subset, int size, int target, int sum)
{
	if (sum == target)
	{
		print_subset(subset, size); //DO NOT RETURN
	}
	int i = start;/////SEGFAULT if you use start.
	while (i < n)
	{
		subset[size] = arr[i];											//pick a number from arr[i], place at the last spot in subset
		powerset(arr, n, i + 1, subset, size + 1, target, sum + arr[i]);//recurse
		i++;
	}
}