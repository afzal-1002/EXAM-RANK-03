#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char	*my_search(char *buffer, int size, char *pattern, int start)
{
	int	i;
	int	j;
	int	len;

	i = start;
	len = strlen(pattern);
	while (i <= size - len)
	{
		j = 0;
		while (j < len && buffer[i + j] == pattern[j])
			j++;
		if (j == len)
			return (&buffer[i]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	char	buffer[100000];
	ssize_t	byte;
	size_t	len;
	char	*patttern;
	char	*pos;
	int		j;
	int		i;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	patttern = argv[1];
	len = strlen(patttern);
	while ((byte = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < byte)
		{
			pos = memmem(buffer + i, byte - i, patttern, len);
			pos = my_search(buffer, byte, patttern, i);
			if (!pos)
			{
				write(1, buffer + i, byte - i);
				break ;
			}
			write(1, buffer + i, pos - (buffer + i));
			j = 0;
			while (j < len)
			{
				write(1, "*", 1);
				j++;
			}
			i = (pos + len) - buffer;
		}
	}
}
