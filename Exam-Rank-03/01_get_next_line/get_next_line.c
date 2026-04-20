#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//stdio is not needed, just let him for test with main
#include <stdio.h>


#define BUFFER_SIZE 1024

char get_char(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos = 0;
	static int bytes_read = 0;

	if (pos >= bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		pos = 0;
		if (bytes_read <= 0)
			return (0);
	}
	return buffer[pos++];
}

char	*get_next_line(int fd)
{
	char *line = malloc(110000);
	char character;
	int i = 0;

	if (fd < 0)
		return (NULL);
	while ((character = get_char(fd)) != 0)
	{
		line[i] = character;
		i++;
		if (character == '\n')
			break ;
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

// Main is here only for testing, do not let him in exam
int		main(int argc, char **argv)
{
	int fd = 0;
	char *line;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line |%s", line);
		// free(line);
		line = get_next_line(fd);
	}

	return (0);
}