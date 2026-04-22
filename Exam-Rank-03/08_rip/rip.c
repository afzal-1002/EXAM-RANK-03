#include <unistd.h>

int	is_balanced(char *str)
{
	int i = 0;
	int c = 0;

	while (str[i])
	{
		if (str[i] == '(')
			c++;
		else if (str[i] == ')')
			c--;
		if (c < 0)
			return (0);
		i++;
	}
	return (c == 0);
}

void	putstr(char *str)
{
	int i = 0;

	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

void	solve(char *str, int i, int l, int r)
{
	if (!str[i])
	{
		if (l == 0 && r == 0 && is_balanced(str))
			putstr(str);
		return;
	}

	if (str[i] == '(' && l > 0)
	{
		str[i] = ' ';
		solve(str, i + 1, l - 1, r);
		str[i] = '(';
	}

	if (str[i] == ')' && r > 0)
	{
		str[i] = ' ';
		solve(str, i + 1, l, r - 1);
		str[i] = ')';
	}

	solve(str, i + 1, l, r);
}

int	main(int ac, char **av)
{
	int i = 0, l = 0, r = 0;
	char *str;

	if (ac != 2)
		return (0);
	str = av[1];

	while (str[i])
	{
		if (str[i] == '(')
			l++;
		else if (str[i] == ')')
		{
			if (l > 0)
				l--;
			else
				r++;
		}
		i++;
	}

	solve(str, 0, l, r);
}