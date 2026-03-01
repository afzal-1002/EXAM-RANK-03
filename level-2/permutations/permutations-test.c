#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

void ft_swap(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char *order_string(char *str)
{
	int len = ft_strlen(str);
	int swapped = 1;

	while (swapped)
	{
		swapped = 0;
		int i = 0;
		while (i < len - 1)
		{
			if (str[i] > str[i + 1])
			{
				ft_swap(&str[i], &str[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
	return str;
}

int ft_strchr(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

void generate_permutations(char *str, char *result, int pos)
{
	int str_len = ft_strlen(str);
	if (pos == str_len)
	{
		write(1, result, str_len);
		write(1, "\n", 1);
		return;
	}

	int i = 0;
	while (i < str_len)
	{
		if (!ft_strchr(result, str[i]))
		{
			result[pos] = str[i];
			generate_permutations(str, result, pos + 1);
			result[pos] = '\0';
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	char *result;

	if (argc != 2)
	{
		return 1;
	}

	if ((ft_strlen(argv[1]) == 0) || (argv[1][0] == ' ' && !argv[1][1]))
	{
		return 0;
	}

	result = calloc(ft_strlen(argv[1]) + 1, 1);
	if (!result)
	{
		return 1;
	}
	char *source = order_string(argv[1]);
	printf("tu string %s\n", source);
	generate_permutations(source, result, 0);

	free(result);
	return 0;
}