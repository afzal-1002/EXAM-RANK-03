#include <unistd.h>

int	get_length(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_string(char *str)
{
	int	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

void	generate(char *str, char *result, int *used, int pos, int len)
{
	if (pos == len)
	{
		result[pos] = '\0';
		print_string(result);
		return ;
	}

	for (int i = 0; i < len; i++)
	{
		if (used[i])
			continue ;

		used[i] = 1;
		result[pos] = str[i];

		generate(str, result, used, pos + 1, len);

		used[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	int	len;
	char	result[100];
	int	    used[100] = {0};

	if (argc != 2)
		return (1);

	len = get_length(argv[1]);
	generate(argv[1], result, used, 0, len);

	return (0);
}