#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	*get_set_from_input(int elements_num, char **argv)
{
	int	*set;
	int	i;

	set = malloc(elements_num * sizeof(int));
	if (!set)
		return (NULL);
	i = 0;
	while (i < elements_num)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	return (set);
}

int	*create_bin_rep(int elements_num)
{
	int	*bin_rep;
	int	i;

	bin_rep = malloc(elements_num * sizeof(int));
	if (!bin_rep)
		return (NULL);
	i = 0;
	while (i < elements_num)
	{
		bin_rep[i] = 0;
		i++;
	}
	return (bin_rep);
}

int	is_end_of_bin_rep(int *bin_rep, int elements_num)
{
	int	i;

	i = 0;
	while (i < elements_num)
	{
		if (bin_rep[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_sum(int target, int *set, int elements_num, int *bin_rep)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < elements_num)
	{
		if (bin_rep[i] == 1)
			sum += set[i];
		i++;
	}
	if (sum == target)
		return (1);
	return (0);
}

void	print_combination(int *set, int *bin_rep, int elements_num)
{
	int	i;
	int	first_num;

	i = 0;
	first_num = 1;
	while (i < elements_num)
	{
		if (bin_rep[i] == 1)
		{
			if (first_num)
			{
				printf("%d", set[i]);
				first_num = 0;
			}
			else
				printf(" %d", set[i]);
		}
		i++;
	}
	printf("\n");
}

void	add_bin_rep(int	*bin_rep, int elements_num)
{
	int	i;

	i = 0;
	while (i < elements_num)
	{
		if (bin_rep[i] == 0)
		{
			bin_rep[i] = 1;
			return ;
		}
		else 
		{
			bin_rep[i] = 0;
			i++;
		}
	}
}

int	find_all_combinations(int target, int *set, int elements_num)
{
	int	*bin_rep;

	bin_rep = create_bin_rep(elements_num);
	if (!bin_rep)
		return (0);
	while (!is_end_of_bin_rep(bin_rep, elements_num))
	{
		if (check_sum(target, set, elements_num, bin_rep))
			print_combination(set, bin_rep, elements_num);
		add_bin_rep(bin_rep, elements_num);
	}
	if (check_sum(target, set, elements_num, bin_rep))
		print_combination(set, bin_rep, elements_num);
	free(bin_rep);
	return (1);
}

int	main(int argc, char **argv)
{
	int	target;
	int	elements_num;
	int	*set;

	if (argc == 1)
		return (1);
	if (argc == 2)
	{
		if (atoi(argv[1]) == 0)
			printf("\n");
		return (0);
	}
	target = atoi(argv[1]);
	elements_num = argc - 2;
	set = get_set_from_input(elements_num, argv);
	if (!set)
		return (1);
	if (!find_all_combinations(target, set, elements_num))
		return (1);
	free(set);
	return (0);
}