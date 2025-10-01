#include "../gnl.h"

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

int main(void)
{
	char *str = NULL;

	str_append_mem(&str, "append1", ft_strlen("append1"));
	str_append_mem(&str, "append1", ft_strlen("append1"));
	str_append_mem(&str, "append1", ft_strlen("append1"));
	printf("%s\n", str);

	free(str);
	return (0);
}