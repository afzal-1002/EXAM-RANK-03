/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:07:53 by jziola            #+#    #+#             */
/*   Updated: 2025/12/28 19:31:26 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*str;
	size_t	i;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	str = (char *)ptr;
	i = 0;
	while (i < count)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	value;
	char	*str;

	i = 0;
	value = (char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == value)
			return (&str[i]);
		i++;
	}
	if (value == '\0')
		return (&str[i]);
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[i + s1_len] = s2[i];
		i++;
	}
	str[s1_len + s2_len] = '\0';
	return (str);
}
*/