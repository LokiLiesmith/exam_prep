#include "../gnl.h"

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


int main(void)
{
	printf("ft_strchr: %p\n", ft_strchr("test\n", '\n'));
	printf("strchr: %p\n", strchr("test\n", '\n'));

	printf("ft_strchr: %p\n", ft_strchr("test", '\n'));
	printf("strchr: %p\n", strchr("test", '\n'));	
	
	return (0);
}