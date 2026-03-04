#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	abs_value(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	is_safe(int result[], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (result[i] == col)
			return (0);
		if (abs_value(result[i] - col) == abs_value(i - row))
			return (0);
	}
	return (1);
}

void	print_queen(int result[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", result[i]);
	printf("\n");
}

void	NQueen(int result[], int row, int size)
{
	if (row == size)
	{
		print_queen(result, size);
		return ;
	}
	for (int col = 0; col < size; col++)
	{
		if (is_safe(result, row, col))
		{
			result[row] = col;
			NQueen(result, row + 1, size);
		}
	}
}

int	main(int argc, char **argv)
{
	int	size;
	int	*result;

	if (argc != 2)
		return (0);
	size = atoi(argv[1]);
	result = malloc(sizeof(int) * size);
	NQueen(result, 0, size);
	free(result);
}
