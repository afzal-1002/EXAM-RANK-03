#include <unistd.h>

int	is_balanced(char *s)
{
	int i = 0;
	int c = 0;

	while (s[i])
	{
		if (s[i] == '(')
			c++;
		else if (s[i] == ')')
			c--;
		if (c < 0)
			return (0);
		i++;
	}
	return (c == 0);
}

void	putstr(char *s)
{
	int i = 0;

	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

void	solve(char *s, int i, int l, int r)
{
	if (!s[i])
	{
		if (l == 0 && r == 0 && is_balanced(s))
			putstr(s);
		return;
	}

	if (s[i] == '(' && l > 0)
	{
		s[i] = ' ';
		solve(s, i + 1, l - 1, r);
		s[i] = '(';
	}

	if (s[i] == ')' && r > 0)
	{
		s[i] = ' ';
		solve(s, i + 1, l, r - 1);
		s[i] = ')';
	}

	solve(s, i + 1, l, r);
}

int	main(int ac, char **av)
{
	int i = 0, l = 0, r = 0;
	char *s;

	if (ac != 2)
		return (0);
	s = av[1];

	while (s[i])
	{
		if (s[i] == '(')
			l++;
		else if (s[i] == ')')
		{
			if (l > 0)
				l--;
			else
				r++;
		}
		i++;
	}

	solve(s, 0, l, r);
}