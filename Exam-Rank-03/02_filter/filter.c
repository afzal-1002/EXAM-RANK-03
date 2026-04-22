#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

// int strlen(const char *s)
// {
// 	int i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

int	main(int ac, char **av)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;
	char	*position;
	size_t	i;
	size_t	j;
	size_t	pattern_len;
	

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	pattern_len = strlen(av[1]);

	while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < (size_t)bytes)
		{
			position = memmem(buffer + i, bytes - i, av[1], pattern_len);

			if (position == buffer + i)
			{
				j = 0;
				while (j < pattern_len)
				{
					write(1, "*", 1);
					j++;
				}
				i += pattern_len;
			}
			else
			{
				write(1, &buffer[i], 1);
				i++;
			}
		}
	}
	return (0);
}