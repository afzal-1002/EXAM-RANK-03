#include "./get_next_line.h"

char *ft_calloc(size_t n_membr, size_t var_size)
{
	char *ptr;
	char *str;

	ptr = malloc(n_membr * var_size);
	if (!ptr)
	{
		return NULL;
	}
	str = ptr;
	int i = 0;
	while (i < (int)n_membr)
	{
		str[i] = '\0';
		i++;
	}
	return str;
}

char *ft_strchr(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
		{
			return &str[i];
		}
		i++;
	}
	if (c == '\0')
		return &str[i];
	return NULL;
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return i;
}

char *ft_strjoin(char *str1, char *str2)
{
	char *result;

	int strlen1 = ft_strlen(str1);
	int strlen2 = ft_strlen(str2);
	result = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!result)
	{
		return NULL;
	}

	int i = 0;
	while (str1[i])
	{
		result[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i])
	{
		result[i + strlen1] = str2[i];
		i++;
	}

	result[strlen1 + strlen2] = '\0';
	return result;
}

char *ft_read(int fd, char *line, int *bytes_read)
{
	char *buffer;
	char *temp;

	if (!line)
	{
		line = ft_calloc(1, sizeof(char));
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	*bytes_read = 1;
	while (!ft_strchr(line, '\n') && *bytes_read != 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			free(buffer);
			free(line);
			return NULL;
		}
		buffer[*bytes_read] = '\0';
		temp = line;
		line = ft_strjoin(temp, buffer);
		free(temp);
	}
	free(buffer);
	return line;
}

char *ft_next_line(char *line)
{
	char *next_line;
	int i = 0;
	if (!line[i])
		return NULL;
	while (line[i] && line[i] != '\n')
	{
		i++;
	}

	next_line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while(line[i] && line[i] != '\n')
	{
		next_line[i] = line[i];
		i++;
	}

	if (line[i] == '\n')
	{
		next_line[i] = '\n';
	}
	return (next_line);
}

char *ft_rest_line(char *line)
{
	char *rest_line;
	int i = 0;
	while (line[i] && line[i] != '\n')
	{
		i++;
	}
	if (!line[i])
	{
		free(line);
		return NULL;
	}
	rest_line = ft_calloc(ft_strlen(line) - i + 1, sizeof(char));
	if (!rest_line)
	{
		return NULL;
	}
	i++;
	int j = 0;
	while (line[i])
	{
		rest_line[j] = line[i];
		i++;
		j++;
	}
	free(line);
	return rest_line;
}

char    *get_next_line(int fd)
{
	static char *line;
	int bytes_read;
	char *next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return NULL;
	}

	line = ft_read(fd, line, &bytes_read);
	if (!line)
	{
		return NULL;
	}
	next_line = ft_next_line(line);
	line = ft_rest_line(line);

	if (next_line == NULL && bytes_read == 0)
	{
		free(line);
		return NULL;
	}

	return (next_line);
}

int main()
{
	int fd = open("./text.txt", O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}

	while (1)
	{
		char *content = get_next_line(fd);
		if (!content)
			break;
		printf("content %s\n", content);
		free(content);
	}
	return 0;
}