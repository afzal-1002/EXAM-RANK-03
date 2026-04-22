#include <unistd.h>
#include <stdlib.h>

int str_len(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    
    return (i);
}

int ft_check(char character, char *str)
{
    int i = 0;

    while (str[i])
    {
      if (str[i] == character)
        return (1);
    i++;    
    }

    return(0);

}


void ft_putchar(char *str)
{
    int i = 0;

    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    
}

void ft_inter(char *str1, char *str2)
{


    char *result = malloc(9999);

    int i = 0;
    int j = 0;
    if (str1 && str2)
    {
        while (str1[i])
        {
            if(ft_check(str1[i], str2) && (ft_check(str1[i], result))  == 0) 
            {
                result[j] = str1[i];
                j++;
            }

            i++;
        }
        
    }
    
    result[j] = '\0';
    ft_putchar(result);

}


int main(int argc, char **argv)
{

	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);

}