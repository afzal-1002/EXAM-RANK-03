#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	get_char(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	pos;
	static int	line;

	if (pos >= line)
	{
		line = read(fd, buffer, BUFFER_SIZE);
		pos = 0;
		if (line <= 0)
			return (-1);
	}
	return ((unsigned char)buffer[pos++]);
}

char	*line_copy(char *str, int len)
{
	int		i;
	char	*line;

	i = 0;
	if (len <= 0)
		return (NULL);
	line = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*get_nl(int fd)
{
	char	buffer[100000];
	int		c;
	int		i;

	i = 0;
	c = get_char(fd);
	if (c == -1)
		return (NULL);
	while (c != -1)
	{
		buffer[i] = (char)c;
		i++;
		if (c == '\n')
			break ;
		c = get_char(fd);
	}
	return (line_copy(buffer, i));
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("get_nl.c", O_RDONLY);
	if (fd == -1)
	{
		write(1, "ERROR", 5);
		return (0);
	}
	line = get_nl(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_nl(fd);
	}
	close(fd);
	return (0);
}
