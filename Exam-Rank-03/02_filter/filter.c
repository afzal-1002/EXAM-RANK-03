#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int	main(int ac, char **av)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;
	size_t	i;
	size_t	j;
	size_t	p_len;
	char	*position;

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	p_len = strlen(av[1]);

	while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < (size_t)bytes)
		{
			position = memmem(buffer + i, bytes - i, av[1], p_len);

			if (position == buffer + i)
			{
				j = 0;
				while (j < p_len)
				{
					write(1, "*", 1);
					j++;
				}
				i += p_len;
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