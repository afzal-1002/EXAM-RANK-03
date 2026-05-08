#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_str(char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

void	permute(char *str, char *buffer, int *used, int size, int depth)
{
	int	i;

	if (depth == size)
	{
		buffer[depth] = '\0';
		print_str(buffer);
		return ;
	}
	i = 0;
	while (i < size)
	{
		if (!used[i])
		{
			used[i] = 1;
			buffer[depth] = str[i];
			permute(str, buffer, used, size, depth + 1);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	char	*buffer;
	int		*used;
	int		size;

	if (argc != 2)
		return (1);
	str = argv[1];
	size = 0;
	while (str[size])
		size++;
	buffer = malloc(sizeof(char) * (size + 1));
	used = calloc(size, sizeof(int));
	if (!buffer || !used)
		return (0);
	sort_str(str, size);
	permute(str, buffer, used, size, 0);
	free(buffer);
	free(used);
	return (0);
}
