#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes;
	char *pattern;
	size_t pat_len;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	pattern = argv[1];
	pat_len = strlen(pattern);

	while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		char *start = buffer;
		char *end = buffer + bytes;
		char *pos;

		while ((pos = memmem(start, end - start, pattern, pat_len)))
		{
			write(1, start, pos - start);

			for (size_t i = 0; i < pat_len; i++)
				write(1, "*", 1);

			start = pos + pat_len;
		}

		write(1, start, end - start);
	}

	if (bytes < 0)
	{
		perror("Error");
		return (1);
	}

	return (0);
}