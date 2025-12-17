#include <stdio.h>
#include <string.h>

void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
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

int main(void)
{
	char b1[20];

	strcpy(b1, "bcdaefglkyzasd");

	printf("%s\n", b1);
	sort_str(b1);
	printf("%s\n", b1);
	return (0);
}