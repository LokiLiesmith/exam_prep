#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	print_subset(int *subset, int size)
{
	int i;

	if (size == 0)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while (i < size)
	{
		printf("%d", subset[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

static void	backtrack(int *arr, int n, int index, int *subset, int size,
						int target, int sum)
{
	if (sum == target)
		print_subset(subset, size);
	if (index == n)
		return ;
	// choice 1: skip arr[index]
	backtrack(arr, n, index + 1, subset, size, target, sum);
	// choice 2: include arr[index]
	subset[size] = arr[index];
	backtrack(arr, n, index + 1, subset, size + 1, target, sum + arr[index]);
}

int	main(int ac, char **av)
{
	int target;
	int *arr;
	int *subset;
	int n; //nr elements in arr
	int i;

	if (ac < 2)
		return (0);
	target = atoi(av[1]);
	n = ac - 2;
	arr = malloc(sizeof(int) * n);
	if (!arr)
		return (1);
	i = 0;
	while (i < n)
	{
		arr[i] = atoi(av[i + 2]);
		i++;
	}
	subset = malloc(sizeof(int) * n);
	if (!subset)
		return (free(arr), 1);
	backtrack(arr, n, 0, subset, 0, target, 0);
	free(arr);
	free(subset);
	return (0);
}