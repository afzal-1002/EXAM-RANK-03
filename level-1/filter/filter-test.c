#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void ft_filter(char *buffer, char *target)
{
	int i, j, k;

	int str_len = strlen(target);

	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (target[j] && (buffer[i + j] == target[j]))
		{
			j++;
		}
		if (j == str_len)
		{
			k = 0;
			while (k < str_len)
			{
                write(1, "*", 1);
				k++;
			}
			i += str_len;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	int	bytes_read;
	char temp[BUFFER_SIZE];
	char *buffer;
	char *result = NULL;
	int total_read = 0;

	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	while ((bytes_read = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes_read + 1);
		if (!buffer)
		{
			perror("Error");
			free(result);
			return 1;
		}
		result = buffer;

		memmove(result + total_read, temp, bytes_read);
		total_read += bytes_read;
		result[total_read] = '\0';
	}

	if (bytes_read < 0)
	{
		perror("Error");
		free(result);
		return 1;
	}

	if (!result)
		return 1;

	ft_filter(result, argv[1]);
	free(result);
	return (0);
}