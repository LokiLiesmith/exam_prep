#include <stdio.h>

static void compute_rem(const char *s, int *remL, int *remR)
{
	int i = 0, open = 0;
	*remL = 0; *remR = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0) open--;
			else (*remR)++;
		}
		i++;
	}
	*remL = open;
}

/*
** dfs(s, i, remL, remR, bal)
** - s:     the string (we modify in-place: replace removed char with ' ')
** - i:     current index
** - remL:  '(' still to remove (minimum)
** - remR:  ')' still to remove (minimum)
** - bal:   current balance of kept '(' minus kept ')'
**
** STYLE:  MARK (space) -> RECURSE -> ERASE (restore) / or KEEP and RECURSE.
*/
static void dfs(char *s, int i, int remL, int remR, int bal)
{
	char c;

	/* end: print only if perfectly balanced and nothing left to remove */
	if (!s[i])
	{
		if (remL == 0 && remR == 0 && bal == 0)
			puts(s);
		return;
	}

	c = s[i];

	if (c == '(')
	{
		/* REMOVE '(' if we must */
		if (remL > 0)
		{
			s[i] = ' ';                    /* MARK */
			dfs(s, i + 1, remL - 1, remR, bal);
			s[i] = '(';                    /* ERASE (restore) */
		}
		/* KEEP '(' always valid: increases balance */
		dfs(s, i + 1, remL, remR, bal + 1);
	}
	else if (c == ')')
	{
		/* REMOVE ')' if we must */
		if (remR > 0)
		{
			s[i] = ' ';                    /* MARK */
			dfs(s, i + 1, remL, remR - 1, bal);
			s[i] = ')';                    /* ERASE (restore) */
		}
		/* KEEP ')' only if there is a '(' to match */
		if (bal > 0)
			dfs(s, i + 1, remL, remR, bal - 1);
	}
	else
	{
		/* input is only parentheses per subject, but just in case */
		dfs(s, i + 1, remL, remR, bal);
	}
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1][0])
		return 0;

	/* We mutate av[1] in place: set removed chars to ' ' and restore on backtrack */
	int remL, remR;
	compute_rem(av[1], &remL, &remR);
	dfs(av[1], 0, remL, remR, 0);
	return 0;
}