#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char matrix[4];

	int rows = 10;
	int cols = 10;

	int i = 0;
	while (i < rows)
	{
		if (i == 0 || i == rows - 1)
		{
			for (size_t k = 0; k < rows; k++)
			{
				write(1, "0", 1);
			}
		}
		else
		{
			int j = 0;
			while (j < cols)
			{
				// write(1, "*", 1);
				if (i == j)
				{
					write(1, "0", 1);
				}
				else
				{
					write(1, "*", 1);
				}

				j++;
				/* code */
			}
		}

		i++;
		printf("\n");
	}
}