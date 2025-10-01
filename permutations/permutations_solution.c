#include <unistd.h>
#include <stdlib.h>

void    ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

void    print_solution(char *str)
{
    ft_putstr(str);
}

void    swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void    backtrack(char *str, int l, int r)
{
    int i;

    if (l == r) //finish condition
    {
        print_solution(str);
        return ;
    }
    i = l;
    while (i <= r)
    {
        swap(&str[l], &str[i]);        // make a choice
        backtrack(str, l + 1, r);      // recurse
        swap(&str[l], &str[i]);        // undo - swap back
        i++;
    }
}

void    solve_permutations(char *str)
{
    int len = 0;
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
