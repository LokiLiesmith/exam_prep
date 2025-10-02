#include <stdio.h>
#include <stdlib.h>

void	print_solution(int *subset, int size)
{
	int i = 0;
	if (size == 0)
	{
		printf("\n");
		return ;
	}
	while (i < size)
	{
		// if (i) printf(" ");
		printf("%d", subset[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}


void	powerset(int *arr, int n, int start, int *subset, int size, int target, int sum)
{
	if (target == sum)
	{
		print_solution(subset, size);
		// return ;
	}
	int i = start;
	while(i < n)
	{
		subset[size] = arr[i];
		powerset(arr, n, i + 1, subset, size + 1, target, sum + arr[i]);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	int target = atoi(av[1]);
	int n = ac - 2;
	int *arr = malloc(sizeof(int) * n);
	int *subset = malloc(sizeof(int) * n);

	int i = 0;
	while (i < n)
	{
		arr[i] = atoi(av[i + 2]);
		i++;
	}
	powerset(arr, n, 0, subset, 0, target, 0);
	free(subset);
	free(arr);
	return (0);
}