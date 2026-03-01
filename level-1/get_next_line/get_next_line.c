/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:07:46 by jziola            #+#    #+#             */
/*   Updated: 2025/12/28 16:48:27 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
// /*#include <stdio.h>
// #include <fcntl.h>
// */
// char	*ft_read(int fd, char *line, int *bytes_read)
// {
// 	char	*buffer;
// 	char	*temp;

// 	if (!line)
// 		line = ft_calloc(1, sizeof(char));
// 	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	*bytes_read = 1;
// 	while (!ft_strchr(line, '\n') && *bytes_read != 0)
// 	{
// 		*bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (*bytes_read < 0)
// 		{
// 			free(buffer);
// 			free(line);
// 			return (NULL);
// 		}
// 		buffer[*bytes_read] = '\0';
// 		temp = line;
// 		line = ft_strjoin(temp, buffer);
// 		free(temp);
// 	}
// 	free(buffer);
// 	return (line);
// }

// char	*ft_next_line(char *line)
// {
// 	int		i;
// 	char	*next_line;	

// 	i = 0;
// 	if (!line[i])
// 		return (NULL);
// 	while (line[i] && line[i] != '\n')
// 		i++;
// 	next_line = ft_calloc(i + 2, sizeof(char));
// 	i = 0;
// 	while (line[i] && line[i] != '\n')
// 	{
// 		next_line[i] = line[i];
// 		i++;
// 	}
// 	if (line[i] == '\n')
// 		next_line[i] = '\n';
// 	return (next_line);
// }

// char	*ft_rest_line(char *line)
// {
// 	int		i;
// 	int		j;
// 	char	*rest_line;

// 	i = 0;
// 	j = 0;
// 	while (line[i] && line[i] != '\n')
// 		i++;
// 	if (!line[i])
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	rest_line = ft_calloc(ft_strlen(line) - i + 1, sizeof(char));
// 	if (!rest_line)
// 		return (NULL);
// 	i++;
// 	while (line[i])
// 	{
// 		rest_line[j] = line[i];
// 		j++;
// 		i++;
// 	}
// 	free(line);
// 	return (rest_line);
// }

// char	*get_next_line(int fd)
// {
// 	int			bytes_read;
// 	static char	*line;
// 	char		*next_line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	line = ft_read(fd, line, &bytes_read);
// 	if (!line)
// 		return (NULL);
// 	next_line = ft_next_line(line);
// 	line = ft_rest_line(line);
// 	if (next_line == NULL && bytes_read == 0)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	return (next_line);
// }

// /*int	main()
// {
// 	int fd = open("./test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		char *content = get_next_line(fd);
// 		if (!content)
// 			break;
// 		printf("content: %s\n", content);
// 	}
// 	return (0);
// }
// */
