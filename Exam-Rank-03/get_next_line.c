#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>


#define BUFFER_SIZER 1024


char get_char(int fd)
{
    static char buffer[BUFFER_SIZER];
    static int pos = 0;
    static int bytes_read = 0;

    if(pos >= bytes_read)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZER);
        pos = 0;
        if(bytes_read <= 0)
            return (0);
    }

    return buffer[pos++];

}

char *get_next_line(int fd)
{
    char *line = malloc(1000000);
    int i = 0;

    char character;

    if(fd < 0)
        return (NULL);
    
    while((character = get_char(fd)) != 0)
    {
        line[i] = character;
        i++;
        if(character == '\n')
            break ;
    }

    if(i==0)
    {
        free(line);
        return (NULL);
    }

    line[i] = '\0';
    return (line);
}

// char *get_next_line(int fd)
// {
//     char *line = malloc(1000000);
//     int i = 0;
//     char character;

//     if (!line || fd < 0)
//         return (NULL);

//     while ((character = get_char(fd)) != 0)
//     {
//         line[i++] = character;
//         if (character == '\n')
//             break;
//     }

//     if (i == 0)
//     {
//         free(line);
//         return (NULL);
//     }
//     line[i] = '\0';
//     return (line);
// }



int main(int argc, char **argv)
{
    char *line;
    int fd = 0;

    if(argc > 1)
        fd = open(argv[1], O_RDONLY);

    printf("fd is %d\n", fd);
    
    line = get_next_line(fd);

    while((line!= NULL))
    {
        printf("line |%s", line);
        free(line);
        line = get_next_line(fd);
    }

    return (0);


}