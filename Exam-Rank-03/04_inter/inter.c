#include <unistd.h>


void	ft_putstr(char *str)
{
	int		i = 0;

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_check(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
void	ft_inter(char *s1, char *s2)
{
	char	buffer[999];
	int		i = 0;
	int 	j = 0;

	if (s1 && s2)
	{
		while (s1[i])
		{
			//if s1 char is in s2 and if s1 char is not in buffer
			// if (ft_check(*s1, s2) && ft_check(*s1, buffer) == 0)
			if (ft_check(s1[i], s2) && ft_check(s1[i], buffer) == 0)
				buffer[j++] = s1[i];
			i++;
		}
	}
	buffer[i] = '\0';
	ft_putstr(buffer);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}