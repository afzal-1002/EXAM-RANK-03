#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 1024



int main(int argc, char **argv)
{

    char buffer[BUFFER_SIZE];
    ssize_t bytes;
    char *position;
    size_t i;
    size_t j;
    size_t patt_len;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    patt_len = strlen(argv[1]);

    while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        i = 0;
        while (i < (size_t) bytes)
        {
            position =  memmem (buffer + i, bytes - i, argv[1], patt_len);

            if(position == buffer + i)
            {
                j = 0;
                while (j < patt_len)
                {
                    write(1, "*", 1);
                    j++;
                }
                
                i += patt_len;
                 
            }else{

                write(1, &buffer[i], 1);
                i++;
            }
        }
        
    }

    return(0);
}