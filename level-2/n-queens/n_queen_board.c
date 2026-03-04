#include <stdio.h>
#include <stdlib.h>

int	isSafe(char **board, int row, int col, int n)
{
	int i, j;
	for (i = 0; i < col; i++)
		if (board[row][i] == 'Q')
			return (0);
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j] == 'Q')
			return (0);
	for (i = row, j = col; j >= 0 && i < n; i++, j--)
		if (board[i][j] == 'Q')
			return (0);
	return (1);
}

void	printBoard(char **board, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%c ", board[i][j]);
		printf("\n");
	}
	printf("\n");
}

void	NQueen(char **board, int col, int n)
{
	int	row;

	if (col == n)
	{
		printBoard(board, n);
		return ;
	}
	for (row = 0; row < n; row++)
	{
		if (isSafe(board, row, col, n))
		{
			board[row][col] = 'Q';
			NQueen(board, col + 1, n);
			board[row][col] = '-';
		}
	}
}

int	main(void)
{
	int n = 8;
	int i, j;

	char **board = malloc(n * sizeof(char *));
	for (i = 0; i < n; i++)
		board[i] = malloc(n * sizeof(char));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			board[i][j] = '-';

	NQueen(board, 0, n);

	for (i = 0; i < n; i++)
		free(board[i]);
	free(board);

	return (0);
}