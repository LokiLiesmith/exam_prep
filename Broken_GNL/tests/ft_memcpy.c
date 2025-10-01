#include "../gnl.h"


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

int main(void)
{
	char *src = "HelloWorld";
	char s1[20];
	char s2[20];

	memcpy(s1, src, 5);
	s1[5] = '\0';
	ft_memcpy(s2, src, 5);
	s2[5] = '\0';
	printf("%s\n", s1);
	printf("%s\n", s2);
	return (0);
}