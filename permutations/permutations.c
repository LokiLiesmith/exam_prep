#include <unistd.h>
#include <stdlib.h>

void    ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

void    swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void    sort_str(char *s)
{
    int i = 0;
    int j;

    while (s[i])
    {
        j = i + 1;
        while (s[j])
        {
            if (s[i] > s[j])
                swap(&s[i], &s[j]);
            j++;
        }
        i++;
    }
}

void    print_solution(char *str)
{
    ft_putstr(str);
}

void    backtrack(char *str, int l, int r)
{
    int i;

    if (l == r)
    {
        print_solution(str);
        return ;
    }
    i = l;
    while (i <= r)
    {
        swap(&str[l], &str[i]);        // choose
        backtrack(str, l + 1, r);      // recurse
        swap(&str[l], &str[i]);        // undo
        i++;
    }
}

void    solve_permutations(char *str)
{
    int len = 0;

	sort_str(str); // <-- sort before backtracking
	while (str[len])
    	len++;
	backtrack(str, 0, len - 1);
}

int main(int ac, char **av)
{
    if (ac == 2)
        solve_permutations(av[1]);
    return (0);
}
