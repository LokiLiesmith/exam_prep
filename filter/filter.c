#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #define _GNU_SOURCE

#ifndef BUFFSIZE
# define BUFFSIZE 2
#endif

void ft_filter(char *input, char *pattern)
{
	int i = 0; 
	int j = 0;

	int pat_len = strlen(pattern); 
	while (input[i])
	{
		j = 0;
		while (input[i+j] && pattern[j] && input[i+j] == pattern[j])
			j++;
		if(j == pat_len)
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += pat_len;
		}
		else
		{
			write(1, &input[i], 1);
			i++;
		}
	}
}


int main(int ac, char **av)
{
	char 	temp[BUFFSIZE];
	ssize_t	read_ret;
	ssize_t read_total = 0;
	char *ret = NULL;
	char *buffer;

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	//build buffer

	while ((read_ret = read(0, temp, BUFFSIZE)) > 0)
	{
		buffer = realloc(ret, read_ret + read_total +1);
		if(!buffer)
			return (perror("Error"), free(ret), 1);
		ret = buffer;
		memmove(ret + read_total, temp, read_ret);
		read_total += read_ret;
		ret[read_total] = '\0';
	}
	if (read_ret < 0)
		return(free(ret), perror("Error"), 1);
	if (!ret)
		return(free(ret), 1);
	
	ft_filter(ret, av[1]);
	// printf("%s", ret);
	free(ret);
	return (0);
}
