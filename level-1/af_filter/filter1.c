#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE];
	ssize_t byte;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	char *pattern = argv[1];
	size_t len = strlen(pattern);

	while ((byte = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		int i = 0;

		while (i < byte)
		{
			char *pos = memmem(buffer + i, byte - i, pattern, len);

			if (!pos)
			{
				write(1, buffer + i, byte - i);
				break ;
			}

			int match_pos = pos - buffer;

			write(1, buffer + i, match_pos - i);

			for (size_t j = 0; j < len; j++)
				write(1, "*", 1);

			i = match_pos + len;
		}
	}

	if (byte < 0)
	{
		perror("Error");
		return (1);
	}
	return (0);
}