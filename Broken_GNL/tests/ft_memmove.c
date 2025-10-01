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

int main(void)
{
	char buf1[50], buf2[50];
	strcpy(buf1, "HelloWorld");
	strcpy(buf2, "HelloWorld");
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);
	
	ft_memmove(buf1, buf1 + 5, 5);
	memmove(buf2, buf2 + 5, 5);
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	strcpy(buf1, "HelloWorld");
	strcpy(buf2, "HelloWorld");
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	ft_memmove(buf1 + 5, buf1, 5);
	memmove(buf2 + 5, buf2, 5);
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	strcpy(buf1, "HelloWorld");
	strcpy(buf2, "HelloWorld");
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	ft_memmove(buf1 + 2, buf1, 5);
	memmove(buf2 + 2, buf2, 5);
	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);


	return (0);
}