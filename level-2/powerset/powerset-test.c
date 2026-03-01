#include <stdio.h>
#include <stdlib.h>

int check_args(int argc, char **argv)
{
	int i = 1;

	while (i < argc)
	{
		int j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
		{
			j++;
		}

		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return 0;
			}
			j++;
		}
		i++;
	}

	return 1;
}

void print_solution(int *subset, int subset_size)
{
	int i = 0;
	if (subset_size == 0)
	{
		printf("\n");
		return;
	}
	while (i < subset_size)
	{
		if (i == subset_size - 1)
		{
			printf("%d", subset[i]);
		}
		else
		{
			printf("%d ", subset[i]);
		}
		i++;
	}
	printf("\n");
}

void backtrack(int *set, int *subset, int index, int current_sum, int subset_size, int set_size, int *found, int target)
{
	if (index == set_size)
	{
		if (current_sum == target)
		{
			*found = 1;
			print_solution(subset, subset_size);
		}
		return;
	}

	backtrack(set, subset, index + 1, current_sum, subset_size, set_size, found, target);
	subset[subset_size] = set[index];
	backtrack(set, subset, index + 1, current_sum + set[index], subset_size + 1, set_size, found, target);
}

int main(int argc, char **argv)
{
	if (argc == 1 || (argc >= 2 && (argv[1][0] == '0' && argv[1][1] == '\0')))
	{
		printf("\n");
		return 0;
	}

	if (!check_args(argc, argv))
	{
		printf("\n");
		return 1;
	}
 
	int set_size = argc - 2;
	int target = atoi(argv[1]);

	int found = 0;

	int *set = malloc(set_size * sizeof(int));
	int *subset = malloc(set_size * sizeof(int));

	if (!set || !subset)
	{
		free(set);
		free(subset);
		return 1;
	}

	int i = 2;
	int j = 0;
	while (i < argc)
	{
		set[j] = atoi(argv[i]);
		i++;
		j++;
	}

	backtrack(set, subset, 0, 0, 0, set_size, &found, target);

	if (!found)
	{
		printf("\n");
		return 1;
	}

	free(subset);
	free(set);
	return 0;
}