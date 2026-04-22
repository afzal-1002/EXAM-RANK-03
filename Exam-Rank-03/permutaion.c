#include <unistd.h>
#include <stdio.h>

#include <string.h>

void	print(char *str)
{
	int i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	permut(char *str, int start)
{
	if (str[start] == '\0')
	{
		print(str);
		return;
	}

	int i = start;
	while (str[i])
	{
		swap(&str[start], &str[i]);
		permut(str, start + 1);
		swap(&str[start], &str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
    char *str;

	if (argc == 2)
    {
        str = argv[1];

        int len = 0;

        while (str[len])
            len++;
        
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len -1 -i; j++)
            {

                if(str[j] > str[j+1])
                {
                    int temp = str[j];
                    str[j] = str[j +1];
                    str[j +1] = temp; 
                }
            }            
        }
    }

    printf("%s This \n", str);
    permut(str, 0);
    
    return (0);
        
}