#include "gnl.h"

//FIXED was running off, added s[i] && check
char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
//FIXED was skipping last char, made it copy forward, not back
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;

	while (i < n)
	{
		((unsigned char*)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = *s1 ? ft_strlen(*s1) : 0;//NULL string is len 0;
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if(!dest || !src)
		return (NULL);
	if (dest > src)
	{
		while (n--)
		((unsigned char *)dest)[n] = ((unsigned char *)src)[n]; 
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

char	*get_next_line(int fd)
{
	// printf("GNL: START\n");
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;
	char	*tmp;
	ssize_t	read_ret;

	while (1)
	{
		tmp = ft_strchr(b, '\n');
		if (tmp) //newline case
		{
			// printf("NEWLINE CASE\n");
			// printf("BUFFER: \"%s\"\n", b);
			if ((!str_append_mem(&ret, b, tmp - b + 1)))
			{
				free(ret);
				return(NULL);
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); //shift 
			return (ret);
		}
		//no newline case
		if (*b)
		{
			// printf("NO NEWLINE CASE\n");
			// printf("BUFFER: \"%s\"\n", b);
			if (!str_append_str(&ret, b))
			{
				free(ret);
				return (NULL);
			}
			b[0] = '\0';
		}

		//refill buffer
		read_ret = read(fd, b, BUFFER_SIZE);
		if(read_ret < 0)
		{
			free(ret);
			return (NULL);
		}
		if (read_ret == 0)
		{
			return (ret);
		}
		b[read_ret] = '\0';
	}
}

// char	*get_next_line(int fd)
// {
// 	static char	b[BUFFER_SIZE + 1] = "";
// 	char	*ret = NULL;

// 	char	*tmp = ft_strchr(b, '\n');
// 	while (!tmp)
// 	{
// 		if (!str_append_str(&ret, b))
// 			return (NULL);
// 		int	read_ret = read(fd, b, BUFFER_SIZE);
// 		if (read_ret == -1)
// 			return (NULL);
// 		b[read_ret] = 0;
// 	}
// 	if (!str_append_mem(&ret, b, tmp - b + 1))
// 	{
// 		free(ret);
// 		return (NULL);
// 	}
// 	return (ret);
// }

// include <fcntl.h>
int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	char *line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}


// int main(int ac, char **av)
// {
// 	int fd;
// 	if (ac != 2 || av[1][0] == '\0')
// 		fd = 0;
// 	else
// 		fd = open(av[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	char *line = NULL;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	if (fd != 0)
// 		close(fd);
// 	return (0);
// }