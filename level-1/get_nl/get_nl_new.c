#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int	get_char(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	byte;
	static int	pos;

	if (pos >= byte)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		pos = 0;
		if (byte <= 0)
			return (-1);
	}
	return ((unsigned char)buffer[pos++]);
}

char	*copy_line(char *buffer, int size)
{
	int		i;
	char	*line;

	line = malloc(size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = buffer[i];
		i++;
	}
	line[size] = '\0';
	return (line);
}

char	*get_nl(int fd)
{
	char buffer[100000];
	int c;
	int i;

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
	return (copy_line(buffer, i));
}