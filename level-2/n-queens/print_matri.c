#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char matrix[4];

	// for (size_t i = 0; i < 4; i++)
	// {
	// 	for (size_t j = 0; j < 4; j++)
	// 	{
	// 		printf("*");
	// 	}
	// 	printf("\n");
	// }

	// printf("\n");

	int rows = 4;
	int cols = 4;
	int i = 0;
	int j = 0;

	char variation[4];

	while (i < rows)
	{
		if (i == 0 || i == rows - 1)
		{
			for (size_t k = 0; k < rows; k++)
			{
				write(1, "*", 1);
			}
		}
		else
		{
			for (size_t j = 0; j < cols; j++)
			{
				// if (j == 0 || j == cols - 1)
				// {
				// 	write(1, "*", 1);
				// }
				// else
				// {
				// 	write(1, " ", 1);
				// }

				if (i == j)
				{
					write(1, "*", 1);
				}
				else
				{
					write(1, " ", 1);
				}
			}
		}
		i++;
		write(1, "\n", 1);
	}
}