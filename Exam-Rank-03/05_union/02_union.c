#include <unistd.h>
#include <stdlib.h>


int ft_checker(char c, char *str)
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


void ft_putstr(const char *s) {

    int i = 0;

    if (!s)
        return;
    
    while (s[i]) {
        write(1, &s[i], 1);
        i++;
    }
}

void ft_union(char *str1, char *str2)
{
    char *result;
    int i = 0, j = 0;

    int str1_len = 0, str2_len = 0;

    if (!str1 || !str2)
    {
        write(1, "Error: Null string input\n", 25);
        return;
    }

    while (str1 && str1[str1_len])
        str1_len++;
    while (str2 && str2[str2_len])
        str2_len++;

    result = (char *)malloc((str1_len + str2_len + 1) * sizeof(char));
    if (!result)
        return;

    while (str1[i])
    {
        if (!ft_checker(str1[i], result))
            result[j++] = str1[i];
        i++;
    }

    i = 0;
    while (str2[i])
    {
        if (!ft_checker(str2[i], result))
            result[j++] = str2[i];
        i++;
    }

    result[j] = '\0';
    ft_putstr(result);
    free(result);
}