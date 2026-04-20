#include <unistd.h>
#include <stdlib.h>

void	print_board(int board[], int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			if (board[i] == j)
				write(1, "Q ", 2);
			else
				write(1, ". ", 2);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	is_safe(int board[], int row, int col)
{
	int	i;

	i = 0;
	while (i < row)
	{
		if (board[i] == col)
			return (0);
		if (abs(board[i] - col) == abs(i - row))
			return (0);
		i++;
	}
	return (1);
}

void	solve(int board[], int row, int n)
{
	int	col;

	if (row == n)
	{
		print_board(board, n);
		return ;
	}
	col = 0;
	while (col < n)
	{
		if (is_safe(board, row, col))
		{
			board[row] = col;
			solve(board, row + 1, n);
		}
		col++;
	}
}

int	main(void)
{
	int	board[10];
	int	n;

	n = 4;
	solve(board, 0, n);
	return (0);
}