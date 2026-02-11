
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


char *get_next_line(int fd)
{

    char *str ;
    int i = 0;
    char character;
    int bytes_read;


    str = (char *)malloc((999) * sizeof(char));
    if (!str)
    {
        free(str);
        return NULL;
    }

    if (fd < 0)
    {
        free(str);
        return NULL;
    }
    

    while ((bytes_read = read(fd, &character, 1))>0)
    {
       str[i] = character;
       i++;
        if (character == '\n')
            break; 
    }

    if ( i == 0 || bytes_read < 0)
    {
        free(str);
        return NULL;
    }
    str[i] = '\0';
    return str;

}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
    {
        write(1, "Error opening file\n", 19);
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, strlen(line));
        free(line);
    }

    close(fd);
    return 0;
}