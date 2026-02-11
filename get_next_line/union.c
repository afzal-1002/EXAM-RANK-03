#include <unistd.h>
#include <stdlib.h>


int ft_checker(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(const char *s) {
    if (!s)
    {
        return;
    }
    
    while (*s) {
        ft_putchar(*s);
        s++;
    }
}

void ft_union(char *str1, char *str2)
{
    char *result;
    int i = 0, j = 0;

    if (!str1 || !str2)
    {
        write(1, "Error: Null string input\n", 25);
        return;
    }

    result = (char *)malloc((999) * sizeof(char));
    if (!result)
        return;

    while (str1[i])
    {
        if (!ft_checker(result, str1[i]))
        {
            result[j++] = str1[i];
        }
        i++;
    }

    i = 0;
    while (str2[i])
    {
        if (!ft_checker(result, str2[i]))
        {
            result[j++] = str2[i];
        }
        i++;
    }

    result[j] = '\0';
    ft_putstr(result);
    free(result);
}