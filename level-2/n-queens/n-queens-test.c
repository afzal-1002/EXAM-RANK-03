#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int *board;
int board_size;

void print_solution()
{
	int i;

	for (i = 0; i < board_size; i++)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < board_size - 1)
		{
			fprintf(stdout, " ");
		}
	}
	fprintf(stdout, "\n");
}

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return n;
}

int is_safe(int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
		{
			return 0;
		}
		if (ft_abs(board[i] - row) == ft_abs(i - col))
		{
			return 0;
		}
	}

	return 1;
}

void solve(int col)
{
	if (col == board_size)
	{
		print_solution();
		return ;
	}
	else
	{
		for (int row = 0; row < board_size; row++)
		{
			if (is_safe(row, col))
			{
				board[col] = row;
				solve(col + 1);
			}
		}
	}
}

int main(int argc, char **argv)
{
	int n;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return 0;
	}
	n = atoi(argv[1]);
	if (n <= 3)
	{
		write(1, "\n", 1);
		return 	0;
	}
	board_size = n;
	board = malloc(sizeof(int) * board_size);
	if (!board)
	{
		return 0;
	}
	solve(0);
	free(board);
	return 0;
}