// Assignement name : n_queens

// Expected files : *.c *.h

// Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc,
// stdout, stderr

// -------------------------------------------------------------------------

// Write a program that will print all the solutions to the n queens problem
// for a n given as argument.
// We will not test with negative values.
// The order of the solutions is not important.

// You will display the solutions under the following format :
// <p1> <p2> <p3> ...

// where pn are the line index of the queen in each colum starting from 0.

// For example this should work :
// $> ./n_queens 2 | cat -e

// $> ./n_queens 4 | cat -e
// 1 3 0 2$
// 2 0 3 1$

// $> ./n_queens 7 | cat -e
// 0 2 4 6 1 3 5$
// 0 3 6 2 5 1 4$
// etc...

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	put_number(int n)
{
	char	c;

	if (n >= 10)
		put_number(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	print_queen(int pos[], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_number(pos[i]);
		if (i + 1 < size)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	is_safe(int pos[], int col, int row)
{
	int	q;

	q = 0;
	while (q < col)
	{
		if (pos[q] == row)
			return (0);
		if (ft_abs(pos[q] - row) == ft_abs(q - col))
			return (0);
		q++;
	}
	return (1);
}

void	solve(int pos[], int col, int size)
{
	int	row;

	if (col == size)
	{
		print_queen(pos, size);
		return ;
	}
	row = 0;
	while (row < size)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			solve(pos, col + 1, size);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	int *pos;

	if (argc != 2)
		return (1);

	int size = atoi(argv[1]);
	if (size <= 0)
		return (0);
	pos = (int *)malloc(sizeof(int) * size);
	if (!pos)
		return (1);
	solve(pos, 0, size);
	return (0);
}