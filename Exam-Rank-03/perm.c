#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024


void print(char *str)
{
    int i =0;
    while (str[i])
        write(1, &str[i++], 1);
     write(1, "\n", 1);
}

void swap(char *a, char  *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;

}

void solve(char *str, int start)
{
    if (str[start] ==  '\0')
    {
        print(str);
        return;
    }

    int i = start;

    while (str[i])
    {
        swap(&str[start], &str[i]);
        solve(str, start + 1);
        swap(&str[start], &str[i]);
        i++;
    }
    
    
}


int main(int argc, char **argv)
{


    if(argc != 2)
        return (0);

    char *str = argv[1];
    solve(str, 0);
    return(0);

}




