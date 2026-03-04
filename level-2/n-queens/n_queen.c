#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	abs_val(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	place(int *board, int col, int row)
{
	int	prev_col;

	prev_col = 0;
	while (prev_col < col)
	{
		if (board[prev_col] == row)
			return (0);
		if (abs_val(board[prev_col] - row) == abs_val(prev_col - col))
			return (0);
		prev_col++;
	}
	return (1);
}

void	print_solution(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("%d", board[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	nqueens(int *board, int col, int n)
{
	int	row;

	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (place(board, col, row))
		{
			board[col] = row;
			nqueens(board, col + 1, n);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	int n;
	int *board;

	if (argc != 2)
		return (1);

	n = atoi(argv[1]);
	if (n <= 0)
		return (1);

	board = malloc(sizeof(int) * n);
	if (!board)
		return (1);

	nqueens(board, 0, n);

	free(board);
	return (0);
}